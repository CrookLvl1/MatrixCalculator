#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <Windows.h>
using namespace std;

//������� �� ����� mainFunctions.h
#include "mainFunctions.h"
//����� ������� �� ����� Matrix.h
#include "Matrix.h"
using namespace fnc;

int main() {
	SetConsoleCP(1251);
	setlocale(LC_ALL, "Russian");

	
	Matrix m(2, 2, true, true, 10);
	std::vector<Matrix> arr = {m};
	bool exit = false;
	
	while (!exit) {
		fnc::coutArr({ " >>>>>>> Matrix Calculator v1.00", "1. ������� �������", "2. ��������� ��������", "3. �������� ������ ������", "4. ������� �������",  "5. ����� �� ���������"});

		switch (std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"))) {
		case (1): {
			//��������� ����� � ��������
			int rows = std::stoi(fnc:: getNumberStringTemplate("������� ���������� ����� �������: ", "int")),
				columns = std::stoi(fnc::getNumberStringTemplate("������� ���������� �������� �������: ", "int"));

			bool done = false;
			int action;
			//��������� ������� �������� �������
			while (!done) {
				coutArr({ " >>> ��� ��������� �������", "1. ��������� ������� � ���������� ������� ��� �����������", "2. ��������� ������� � �������������", "3. ������ ���������� �������"});
				action = std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"));
				if (action != 1 && action != 2 && action != 3) {
					done = false;
					std::cout << "�� ���������� ����� ��������" << std::endl;
				}
				done = true;
			}

			coutArr({ " >>> ����� ������� � �������: ", "1. ������� ������� � ������� ����� ��������", "2. �� �������� �������" });
			bool log = std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int")) == 1 ? true : false;


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
				int seed = std::stoi(fnc::getNumberStringTemplate("������� ���� ���������: ", "int")),
					left = std::stoi(fnc::getNumberStringTemplate("������� ����� �������: ", "int")),
					right = std::stoi(fnc::getNumberStringTemplate("������� ������ �������: ", "int"));

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
				std::cout << "����� ������� �� ����������" << std::endl;
			}
			}
			break;
		}
		case (2): {
			if (arr.size() < 1) {
				std::cout << "� ������ ��� �� ����� �������" << std::endl;
				break;
			}
			fnc::coutArr({ " >>> ������ ��������: ", "1. ������� �������", "2. �������� ������� �� �����", "3. ����� ������������ �������", "4. �������� ������� �� �������", "5. ����� �������� �������", "6. ������"});
			int operation = std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"));
			switch (operation) {
			case 1: {
				if (arr.size() < 2) {
					std::cout << "� ������ ������������� ���������� ������" << std::endl;;
					exit = fnc::exit();
					break;
				}
				int id1 = std::stoi(fnc::getNumberStringTemplate("������� 'id' ������ �������: ", "int")),
					id2 = std::stoi(fnc::getNumberStringTemplate("������� 'id' ������ �������: ", "int"));

				if (!fnc::checkId(id1, arr.size()) || !fnc::checkId(id2, arr.size())) break;

				Matrix matrixA = arr[id1],
					matrixB = arr[id2];
				if (matrixA.getRows() != matrixB.getRows() || matrixA.getCols() != matrixB.getCols()) {
					std::cout << "������ ��� ������� ������ �� ���������: �������� ����������" << std::endl;
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
				int id = std::stoi(fnc::getNumberStringTemplate("������� 'id' �������: ", "int"));
				if (!fnc::checkId(id, arr.size())) break;

				bool log, rewrite;
				fnc::checkBase(log, rewrite);

				Matrix result = Matrix::multOnNumber(arr[id], std::stod(fnc::getNumberStringTemplate("������� �����: ", "float")));

				if (rewrite) arr[id] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 3: {
				int id = std::stoi(fnc::getNumberStringTemplate("������� id �������: ", "int"));

				if (!fnc::checkId(id, arr.size())) break;

				if (arr[id].getCols() != arr[id].getRows()) {
					std::cout << "���������� ����� � �������� �� ���������: ����� ������������ ����������" << std::endl;
					exit = fnc::exit();
					break;
				}

				std::cout << "������������ = " << Matrix::calcDet(arr[id]) << std::endl;

				break;
			}
			case 4: {
				if (arr.size() < 2) {
					std::cout << "� ������ ������������� ���������� ������" << std::endl;;
					exit = fnc::exit();
					break;
				}
				int id1 = std::stoi(fnc::getNumberStringTemplate("������� 'id' ������ �������: ", "int")),
					id2 = std::stoi(fnc::getNumberStringTemplate("������� 'id' ������ �������: ", "int"));

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
				int id = std::stoi(fnc::getNumberStringTemplate("������� id �������: ", "int"));
				if (!fnc::checkId(id, arr.size())) break;

				Matrix matrixA = arr[id];
				if (matrixA.getRows() != matrixA.getCols()) {
					std::cout << "���������� ����� � �������� �� ���������" << std::endl;
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
				std::cout << "����� ������� �� ����������" << std::endl;
				exit = fnc::exit();
				break;
			}
}
			break;
		}
		case (3): {
			if (arr.size() == 0) std::cout << "������ ����..." << std::endl;
			else for (int i = 0; i < arr.size(); i++) fnc::coutBasicInfo(arr[i].arr, arr[i].getRows(), arr[i].getCols(), i);
			break;
		}
		case (4): {
			if (arr.size() < 1) {
				std::cout << "������ ����: ������� ������" << std::endl;
				break;
			}
			fnc::coutArr({ "1. ������� ������� �� 'id'", "2. ������� ��������� � ������ �������", "3. ������� ��� ������� �� ������", "4. ������"});
			switch (std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"))) {
			case 1: {
				int id = std::stoi(fnc::getNumberStringTemplate("������� 'id' �������", "int"));
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
			std::cout << "����� ������� �� ����������" << std::endl;
			break;
		}
		}

	}

	return 0;
}
