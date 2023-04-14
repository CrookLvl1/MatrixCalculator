#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

namespace fnc {
	//Функция возвращает true, если строка является числом, иначе false, также заменяет '.' в строке на ',';
	bool isAllDigitsF(std::string& str) {
		bool floatValue = false;
		int i = 0;
		if (str[0] == '-') i++;
		if (str.find('.') != -1) str.replace(str.find('.'), 1, ",");
		for (i; i < str.length(); i++) {
			if (!std::isdigit(str[i])) {
				if (!floatValue && str[i] == ',') floatValue = true;
				else return false;
			}
		}
		return true;
	}

	//Функция возвращает true, если все символы строки являются целым числом, иначе false;
	bool isAllDigits(std::string str) {
		int i = 0;
		if (str[0] == '-') i++;
		for (i; i < str.length(); i++) if (!(std::isdigit(str[i]))) return false;
		return true;
	}

	//Функция убирает пробелы из строки, а также обрезает float значения до digits цифр после запятой;
	std::string trimNRound(std::string str, int digits = 3) {
		int index = str.find(' ');
		while (index != -1) {
			str.replace(index, 1, "");
			index = str.find(' ');
		}
		index = str.find(',');
		if (index != -1) {
			if (digits == 0 || std::stoi(str.substr(index + 1)) == 0) return str.substr(0, index);
			return str.substr(0, index + digits + 1);
		}
		return str;
	}

	//Функция проверяет длину нового элемента и, если она больше 
	void checkLineLength(int& lineLength, double element) {
		std::string str = trimNRound(std::to_string(element));
		if (str.length() > lineLength) lineLength = str.length();
	}


	//Шаблон для получения строки, содержащей значение int или double;
	std::string getNumberStringTemplate(std::string coutProp, std::string type = "float") {
		std::string line;
		if (type == "int") {
			do {
				std::cout << coutProp;
				std::getline(std::cin, line);
			} while (!isAllDigits(line) || line.length() == 0);
		}
		else do {
			std::cout << coutProp;
			std::getline(std::cin, line);
		} while (!isAllDigitsF(line) || line.length() == 0);

		return line;
	}
	
	//Добавляет в начало строки str пробелы до тех пор, пока длина строки не будет равна length;
	std::string enchanceStr(std::string str, int length) {
		while (str.length() < length) str.insert(0, " ");
		return str;
	}

	//Генерация матрицы и её случайное заполнение по ссылке;
	void genRandMatrix(std::vector<std::vector<double>>& arr,int rows, int columns, int& lineLength, int seed = std::rand(), int left = 0, int right = 0) {
		std::vector<double> tempArr;
		std::srand(seed);
		for (int i = 0; i < rows; i++) {
			tempArr = {};
			for (int j = 0; j < columns; j++) {
				int num = left - right == 0 ? std::rand() : left + (std::rand() % (right - left + 1));

				int length = trimNRound(std::to_string(num)).length();
				if (length > lineLength) lineLength = length;
				
				tempArr.push_back(num);
			}
			arr.push_back(tempArr);
		}
	}
	
	//Генерация матрицы и её ручное заполнение;
	void genUserMatrix(std::vector<std::vector<double>>& arr, int rows, int columns, int& lineLength) {
		std::cout << ">>>> Заполните матрицу" << std::endl;
		std::vector<double> tempArr;
		for (int i = 0; i < rows; i++) {
			tempArr = {};
			for (int j = 0; j < columns; j++) {
				std::string str = trimNRound(getNumberStringTemplate("matrix[" + std::to_string(i) + "][" + std::to_string(j) + "] = ", "float"));
				if (str.length() > lineLength) lineLength = str.length();

				tempArr.push_back(std::stod(str));
			}
			arr.push_back(tempArr);
		}
		std::cout << ">>>> Матрица создана и заполнена успешно" << std::endl;
	}
	
	//Возвращает алгебраическое дополнение с позиции i, j;
	std::vector<std::vector<double>> getAlgAdd(std::vector<std::vector<double>>& arr, int i, int j)  {
		int size = arr.size();
		std::vector<std::vector<double>> resultArr = {};

		std::vector<double> tempArr;
		for (int row = 0; row < size; row++) {
			if (row == i) continue;

			tempArr = {};
			for (int column = 0; column < size; column++) {
				if (column == j) continue;
				tempArr.push_back(arr[row][column]);
			}
			resultArr.push_back(tempArr);
		}
		return resultArr;
	}
	
	//Рекурсивная функция, вычисляет определитель двумерного массива arr
	double calcDet(std::vector<std::vector<double>> arr) {
		int size = arr.size();
		if (size == 1) return arr[0][0];
		else if (size == 2) return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];

		double det = 0;
		int i = 0;
		for (int j = 0; j < size; j++) {
			if ((i + j) % 2 == 1) arr[i][j] = -arr[i][j];
			det += arr[i][j] * calcDet(fnc::getAlgAdd(arr, i, j));
		}

		return det;
	}

	//Функция возвращает транспозированный двумерный массив arr;
	std::vector<std::vector<double>> transPos(std::vector<std::vector<double>>& arr, int rows, int columns) {
		std::vector<std::vector<double>> resultArr = {};
		std::vector<double> tempArr;
		for (int j = 0; j < columns; j++) {
			tempArr = {};
			for (int i = 0; i < rows; i++) {
				tempArr.push_back(arr[i][j]);
			}
			resultArr.push_back(tempArr);
		}

		return resultArr;
	}
	
	//Вывести массив строк
	void coutArr(std::vector<std::string> arr) {
		for (int i = 0; i < arr.size(); i++) {
			std::cout << arr[i] << std::endl;
		}
	}
	
	//Возвращает true, если пользователь решает завершить работу 
	bool exit() {
		string input;
		fnc::coutArr({ "1. Вернуться в начало", "2. Завершить работу" });
		if (std::stoi(getNumberStringTemplate("Выберите действие: ", "int")) == 1) return false;
		return true;
	}
	
	//Присваивает переменной rewrite значение true, если пользователь хочет заменить исходную матрицу, иначе false
	void checkBase(bool& rewrite) {
		fnc::coutArr({ " >>> Что сделать с полученной матрицей? ", "1. Записать значение в первую (исходную) матрицу", "2. Добавить матрицу в конец списка" });
		rewrite = std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int")) == 1 ? true : false;
	}
	


}