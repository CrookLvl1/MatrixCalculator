#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <Windows.h>
using namespace std;

//Функции из файла mainFunctions.h
#include "mainFunctions.h"
//Класс матрицы из файла Matrix.h
#include "Matrix.h"
using namespace fnc;

//Функция возвращает айди матрицы если она находится в массиве, если нет, то возвращает -1
int indexOfId(int id, std::vector<Matrix>& arr) {
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i].id == id) {
			return i;
		}
	}
	return -1;
}


int main() {
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");
	std::vector<Matrix> arr = {};
	bool exit = false,
		log = false;

	while (!exit) {
		fnc::coutArr({ " >>>>>>> Matrix Calculator v1.00", "1. Создать матрицу", "2. Совершить операцию", "3. Вывести матрицу в консоль", "4. Показать список матриц", "5. Удалить матрицу", "6. Настройки", "7. Выйти из программы"});

		int action = std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int"));
		switch (action) {
		case (1): {
			//Получение строк и столбцов
			int rows = std::stoi(fnc::getNumberStringTemplate("Введите количество строк матрицы: ", "int")),
				columns = std::stoi(fnc::getNumberStringTemplate("Введите количество столбцов матрицы: ", "int"));

			bool done = false;
			int action;
			//Получение способа создания массива
			while (!done) {
				fnc::coutArr({ " >>> Тип генерации массива", "1. Генерация массива с случайными числами без ограничений", "2. Генерация массива с ограничениями", "3. Ручное заполнение массива" });
				action = std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int"));
				if (action != 1 && action != 2 && action != 3) {
					done = false;
					std::cout << "Не существует такой операции" << std::endl;
				}
				done = true;
			}

			switch (action) {
			case 1:
			{
				Matrix matrix(rows, columns, true, false);
				arr.push_back(matrix);
				if (log) Matrix::showMatrix(matrix);

				break;
			}

			case 2:
			{
				int seed = std::stoi(fnc::getNumberStringTemplate("Введите семя генерации: ", "int")),
					left = std::stoi(fnc::getNumberStringTemplate("Введите левую границу: ", "int")),
					right = std::stoi(fnc::getNumberStringTemplate("Введите правую границу: ", "int"));

				Matrix matrix(rows, columns, true, true, seed, left, right);
				arr.push_back(matrix);
				if (log) Matrix::showMatrix(matrix);

				break;
			}
			case 3:
			{
				Matrix matrix(rows, columns, false, false);
				arr.push_back(matrix);
				if (log) Matrix::showMatrix(matrix);

				break;
			}
			}
			break;
		}
		case (2): {
			if (arr.size() < 1) {
				std::cout << "В списке нет ни одной матрицы" << std::endl;
				break;
			}
			fnc::coutArr({ " >>> Список операций: ", "1. Сложить матрицы", "2. Умножить матрицу на число", "3. Найти определитель матрицы", "4. Умножить матрицу на матрицу", "5. Найти обратную матрицу", "6. Транспонировать матрицу", "7. Назад"});
			int operation = std::stoi(fnc::getNumberStringTemplate("Выберите операцию: ", "int"));
			switch (operation) {
			case 1: {
				if (arr.size() < 2) {
					std::cout << "В списке недостаточное количество матриц";
					exit = fnc::exit();
					break;
				}
				int id1 = std::stoi(fnc::getNumberStringTemplate("Введите id первой матрицы: ", "int")),
					id2 = std::stoi(fnc::getNumberStringTemplate("Введите id второй матрицы: ", "int"));

				int index1 = indexOfId(id1, arr);
				if (index1 == -1) {
					std::cout << "Матрицы с id = " << id1 << " нет в списке" << std::endl;
					break;
				}

				int index2 = indexOfId(id2, arr);
				if (index2 == -1) {
					std::cout << "Матрицы с id = " << id2 << " нет в списке" << std::endl;
					break;
				}


				Matrix matrixA = arr[index1],
					matrixB = arr[index2];
				if (matrixA.getRows() != matrixB.getRows() || matrixA.getCols() != matrixB.getCols()) {
					std::cout << "Строки или столбцы матриц не совпадают: Сложение невозможно" << std::endl;
					exit = fnc::exit();
					break;
				}

				bool rewrite;
				fnc::checkBase(rewrite);

				Matrix result = Matrix::addition(matrixA, matrixB);

				if (rewrite) arr[index1] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 2: {
				int id = std::stoi(fnc::getNumberStringTemplate("Введите 'id' матрицы: ", "int"));

				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "Матрицы с id = " << id << " нет в списке" << std::endl;
					break;
				}

				bool rewrite;
				fnc::checkBase(rewrite);

				Matrix result = Matrix::multOnNumber(arr[index], std::stod(fnc::getNumberStringTemplate("Введите число: ", "float")));

				if (rewrite) arr[index] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 3: {
				int id = std::stoi(fnc::getNumberStringTemplate("Введите id матрицы: ", "int"));

				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "Матрицы с id = " << id << " нет в списке" << std::endl;
					break;
				}

				if (arr[index].getCols() != arr[index].getRows()) {
					std::cout << "Количество строк и столбцов не совпадает: Найти определитель невозможно" << std::endl;
					exit = fnc::exit();
					break;
				}

				std::cout << "Определитель = " << Matrix::calcDet(arr[index]) << std::endl;

				break;
			}
			case 4: {
				if (arr.size() < 2) {
					std::cout << "В списке недостаточное количество матриц";
					exit = fnc::exit();
					break;
				}

				int id1 = std::stoi(fnc::getNumberStringTemplate("Введите id первой матрицы: ", "int")),
					id2 = std::stoi(fnc::getNumberStringTemplate("Введите id второй матрицы: ", "int"));

				int index1 = indexOfId(id1, arr);
				if (index1 == -1) {
					std::cout << "Матрицы с id = " << id1 << " нет в списке" << std::endl;
					break;
				}

				int index2 = indexOfId(id2, arr);
				if (index2 == -1) {
					std::cout << "Матрицы с id = " << id2 << " нет в списке" << std::endl;
					break;
				}


				Matrix matrixA = arr[index1],
					matrixB = arr[index2];
				if (matrixA.getCols() != matrixB.getRows()) {
					std::cout << "" << std::endl;

					exit = fnc::exit();
					break;
				}

				bool rewrite;
				fnc::checkBase(rewrite);

				Matrix result = Matrix::multiply(matrixA, matrixB);

				if (rewrite) arr[index1] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 5: {
				int id = std::stoi(fnc::getNumberStringTemplate("Введите id матрицы: ", "int"));

				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "Матрицы с id = " << id << " нет в списке" << std::endl;
					break;
				}

				Matrix matrixA = arr[index];
				if (matrixA.getRows() != matrixA.getCols()) {
					std::cout << "Количество строк и столбцов не совпадает" << std::endl;
					exit = fnc::exit();
					break;
				}
				if (Matrix::calcDet(matrixA) == 0) {
					std::cout << "Определитель равен нулю, найти обратную матрицу невозможно... ";
					break;
				}
				bool rewrite;
				fnc::checkBase(rewrite);

				Matrix result = Matrix::calcInversed(matrixA);

				if (rewrite) arr[index] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 6: {
				int id = std::stoi(fnc::getNumberStringTemplate("Введите id матрицы: ", "int"));

				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "Матрицы с id = " << id << " нет в списке" << std::endl;
					break;
				}

				Matrix matrixA = arr[index];

				bool rewrite;
				fnc::checkBase(rewrite);

				Matrix result = Matrix::getTranspMatrix(matrixA);

				if (rewrite) arr[index] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;

			}
			case 7: {
				break;
			}
			}
			break;
		}
		case (3): {
			int id = std::stoi(fnc::getNumberStringTemplate("Введите id матрицы: ", "int"));

			int index = indexOfId(id, arr);
			if (index == -1) {
				std::cout << "Матрицы с id = " << id << " нет в списке" << std::endl;
				break;
			}

			Matrix::showMatrix(arr[index]);
			break;
		}
		case (4): {
			if (arr.size() <= 0) std::cout << "Список пуст..." << std::endl;
			else for (int i = 0; i < arr.size(); i++) Matrix::showBasicInfo(arr[i]);
			break;
		}
		case (5): {
			if (arr.size() <= 0) {
				std::cout << "Список матриц пуст... " << std::endl;
				break;
			}
			fnc::coutArr({ "1. Удалить по id", "2. Удалить последнюю в списке", "3. Удалить все", "4. Назад"});
			switch (std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int"))) {
			case(1): {
				int id = std::stoi(fnc::getNumberStringTemplate("Введите id: "));
				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "Матрицы с id = " << id << " нет в списке" << std::endl;
					break;
				}
				
				arr.erase(arr.begin() + index);
				break;
			}
			case(2): {
				arr.erase(arr.begin() + arr.size() - 1);
				break;
			}
			case(3): {
				fnc::coutArr({"Вы уверены? ", "1. Да", "2. Нет" });
				if (std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int")) != 1) break;

				arr.clear();
				break;
			}
			case(4):
				break;
			}
			break;
		}
		case (6): {
			fnc::coutArr({ "1. Вывод матрицы в консоль (сейчас = " + (std::string(log ? "true)" : "false)")), "2. Назад" });
			switch (std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int"))) {
			case 1: {
				fnc::coutArr({ "Выводить матрицу в консоль после операций? ", "1. Да", "2. Нет" });
				log = (std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int"))) == 1 ? true : false;
				break;
			}
			case 2: {
				break;
			}
			}
			break;
		}
		case (7): {
			exit = true;
			break;
		}
	
		default:
			std::cout << "Такой команды не существует" << std::endl;
			break;
		}
		std::cout << std::endl;
	}

	return 0;
}