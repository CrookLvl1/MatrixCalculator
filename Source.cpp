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

int main() {
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");

	
	Matrix m(2, 2, true, true, 10);
	std::vector<Matrix> arr = {m};
	bool exit = false;
	
	while (!exit) {
		fnc::coutArr({ " >>>>>>> Matrix Calculator v1.00", "1. Создать матрицу", "2. Совершить операцию", "3. Показать список матриц", "4. Удалить матрицу",  "5. Выйти из программы"});

		switch (std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int"))) {
		case (1): {
			//Получение строк и столбцов
			int rows = std::stoi(fnc:: getNumberStringTemplate("Введите количество строк матрицы: ", "int")),
				columns = std::stoi(fnc::getNumberStringTemplate("Введите количество столбцов матрицы: ", "int"));

			bool done = false;
			int action;
			//Получение способа создания массива
			while (!done) {
				coutArr({ " >>> Тип генерации массива", "1. Генерация массива с случайными числами без ограничений", "2. Генерация массива с ограничениями", "3. Ручное заполнение массива"});
				action = std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int"));
				if (action != 1 && action != 2 && action != 3) {
					done = false;
					std::cout << "Не существует такой операции" << std::endl;
				}
				done = true;
			}

			coutArr({ " >>> Вывод матрицы в консоль: ", "1. Вывести матрицу в консоль после создания", "2. Не выводить матрицу" });
			bool log = std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int")) == 1 ? true : false;


			switch (action) {
			case 1:
			{
				Matrix matrix(rows, columns, true, false);
				arr.push_back(matrix);
				if (log) Matrix::showMatrix(matrix);

				exit = fnc::exit();
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

				exit = fnc::exit();
				break;
			}
			case 3:
			{
				Matrix matrix(rows, columns, false, false);
				arr.push_back(matrix);	
				if (log) Matrix::showMatrix(matrix);

				exit = fnc::exit();
				break;
			}
			case 4: {
				break;
			}
			default: {
				std::cout << "Такой команды не существует" << std::endl;
			}
			}
			break;
		}
		case (2): {
			if (arr.size() < 1) {
				std::cout << "В списке нет ни одной матрицы" << std::endl;
				break;
			}
			fnc::coutArr({ " >>> Список операций: ", "1. Сложить матрицы", "2. Умножить матрицу на число", "3. Найти определитель матрицы", "4. Умножить матрицу на матрицу", "5. Найти обратную матрицу", "6. Отмена"});
			int operation = std::stoi(fnc::getNumberStringTemplate("Выберите операцию: ", "int"));
			switch (operation) {
			case 1: {
				if (arr.size() < 2) {
					std::cout << "В списке недостаточное количество матриц" << std::endl;;
					exit = fnc::exit();
					break;
				}
				int id1 = std::stoi(fnc::getNumberStringTemplate("Введите 'id' первой матрицы: ", "int")),
					id2 = std::stoi(fnc::getNumberStringTemplate("Введите 'id' второй матрицы: ", "int"));

				if (!fnc::checkId(id1, arr.size()) || !fnc::checkId(id2, arr.size())) break;

				Matrix matrixA = arr[id1],
					matrixB = arr[id2];
				if (matrixA.getRows() != matrixB.getRows() || matrixA.getCols() != matrixB.getCols()) {
					std::cout << "Строки или столбцы матриц не совпадают: Сложение невозможно" << std::endl;
					exit = fnc::exit();
					break;
				}
				
				bool log, rewrite;
				fnc::checkBase(log, rewrite);

				Matrix result = Matrix::addition(matrixA, matrixB);
				
				if (rewrite) arr[id1] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 2: {
				int id = std::stoi(fnc::getNumberStringTemplate("Введите 'id' матрицы: ", "int"));
				if (!fnc::checkId(id, arr.size())) break;

				bool log, rewrite;
				fnc::checkBase(log, rewrite);

				Matrix result = Matrix::multOnNumber(arr[id], std::stod(fnc::getNumberStringTemplate("Введите число: ", "float")));

				if (rewrite) arr[id] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 3: {
				int id = std::stoi(fnc::getNumberStringTemplate("Введите id матрицы: ", "int"));

				if (!fnc::checkId(id, arr.size())) break;

				if (arr[id].getCols() != arr[id].getRows()) {
					std::cout << "Количество строк и столбцов не совпадает: Найти определитель невозможно" << std::endl;
					exit = fnc::exit();
					break;
				}

				std::cout << "Определитель = " << Matrix::calcDet(arr[id]) << std::endl;

				break;
			}
			case 4: {
				if (arr.size() < 2) {
					std::cout << "В списке недостаточное количество матриц" << std::endl;;
					exit = fnc::exit();
					break;
				}
				int id1 = std::stoi(fnc::getNumberStringTemplate("Введите 'id' первой матрицы: ", "int")),
					id2 = std::stoi(fnc::getNumberStringTemplate("Введите 'id' второй матрицы: ", "int"));

				if (!fnc::checkId(id1, arr.size()) || !fnc::checkId(id2, arr.size())) break;

				Matrix matrixA = arr[id1],
					matrixB = arr[id2];
				if (matrixA.getCols() != matrixB.getRows()) {
					std::cout << "" << std::endl;

					exit = fnc::exit();
					break;
				}

				bool log, rewrite;
				fnc::checkBase(log, rewrite);

				Matrix result = Matrix::multiply(matrixA, matrixB);

				if (rewrite) arr[id1] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 5: {
				int id = std::stoi(fnc::getNumberStringTemplate("Введите id матрицы: ", "int"));
				if (!fnc::checkId(id, arr.size())) break;

				Matrix matrixA = arr[id];
				if (matrixA.getRows() != matrixA.getCols()) {
					std::cout << "Количество строк и столбцов не совпадает" << std::endl;
					exit = fnc::exit();
					break;
				}

				bool log, rewrite;
				fnc::checkBase(log, rewrite);

				Matrix result = Matrix::calcInversed(matrixA);

				if (rewrite) arr[id] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 6: {break; }
			default: {
				std::cout << "Такой команды не существует" << std::endl;
				exit = fnc::exit();
				break;
			}
}
			break;
		}
		case (3): {
			if (arr.size() == 0) std::cout << "Список пуст..." << std::endl;
			else for (int i = 0; i < arr.size(); i++) fnc::coutBasicInfo(arr[i].arr, arr[i].getRows(), arr[i].getCols(), i);
			break;
		}
		case (4): {
			if (arr.size() < 1) {
				std::cout << "Список пуст: Удалять нечего" << std::endl;
				break;
			}
			fnc::coutArr({ "1. Удалить матрицу по 'id'", "2. Удалить последнюю в списке матрицу", "3. Удалить все матрицы из списка", "4. Отмена"});
			switch (std::stoi(fnc::getNumberStringTemplate("Выберите действие: ", "int"))) {
			case 1: {
				int id = std::stoi(fnc::getNumberStringTemplate("Введите 'id' матрицы", "int"));
				if (!fnc::checkId(id, arr.size())) break;

				arr.erase(arr.begin() + id, arr.begin() + id + 1);

				break;
			}
			case 2: {
				arr.pop_back();

				break;
			}
			case 3: {
				arr.clear();

				break;
			}
			case 4: {
				break;
			}
			}
			break;
		}
		case (5): {
			exit = true;
			break;
		}

		default:{
			std::cout << "Такой команды не существует" << std::endl;
			break;
		}
		}

	}

	return 0;
}
