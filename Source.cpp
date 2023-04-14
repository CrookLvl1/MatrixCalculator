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

//������� ���������� ���� ������� ���� ��� ��������� � �������, ���� ���, �� ���������� -1
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
		fnc::coutArr({ " >>>>>>> Matrix Calculator v1.00", "1. ������� �������", "2. ��������� ��������", "3. ������� ������� � �������", "4. �������� ������ ������", "5. ������� �������", "6. ���������", "7. ����� �� ���������"});

		int action = std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"));
		switch (action) {
		case (1): {
			//��������� ����� � ��������
			int rows = std::stoi(fnc::getNumberStringTemplate("������� ���������� ����� �������: ", "int")),
				columns = std::stoi(fnc::getNumberStringTemplate("������� ���������� �������� �������: ", "int"));

			bool done = false;
			int action;
			//��������� ������� �������� �������
			while (!done) {
				fnc::coutArr({ " >>> ��� ��������� �������", "1. ��������� ������� � ���������� ������� ��� �����������", "2. ��������� ������� � �������������", "3. ������ ���������� �������" });
				action = std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"));
				if (action != 1 && action != 2 && action != 3) {
					done = false;
					std::cout << "�� ���������� ����� ��������" << std::endl;
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
				int seed = std::stoi(fnc::getNumberStringTemplate("������� ���� ���������: ", "int")),
					left = std::stoi(fnc::getNumberStringTemplate("������� ����� �������: ", "int")),
					right = std::stoi(fnc::getNumberStringTemplate("������� ������ �������: ", "int"));

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
				std::cout << "� ������ ��� �� ����� �������" << std::endl;
				break;
			}
			fnc::coutArr({ " >>> ������ ��������: ", "1. ������� �������", "2. �������� ������� �� �����", "3. ����� ������������ �������", "4. �������� ������� �� �������", "5. ����� �������� �������", "6. ��������������� �������", "7. �����"});
			int operation = std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"));
			switch (operation) {
			case 1: {
				if (arr.size() < 2) {
					std::cout << "� ������ ������������� ���������� ������";
					exit = fnc::exit();
					break;
				}
				int id1 = std::stoi(fnc::getNumberStringTemplate("������� id ������ �������: ", "int")),
					id2 = std::stoi(fnc::getNumberStringTemplate("������� id ������ �������: ", "int"));

				int index1 = indexOfId(id1, arr);
				if (index1 == -1) {
					std::cout << "������� � id = " << id1 << " ��� � ������" << std::endl;
					break;
				}

				int index2 = indexOfId(id2, arr);
				if (index2 == -1) {
					std::cout << "������� � id = " << id2 << " ��� � ������" << std::endl;
					break;
				}


				Matrix matrixA = arr[index1],
					matrixB = arr[index2];
				if (matrixA.getRows() != matrixB.getRows() || matrixA.getCols() != matrixB.getCols()) {
					std::cout << "������ ��� ������� ������ �� ���������: �������� ����������" << std::endl;
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
				int id = std::stoi(fnc::getNumberStringTemplate("������� 'id' �������: ", "int"));

				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "������� � id = " << id << " ��� � ������" << std::endl;
					break;
				}

				bool rewrite;
				fnc::checkBase(rewrite);

				Matrix result = Matrix::multOnNumber(arr[index], std::stod(fnc::getNumberStringTemplate("������� �����: ", "float")));

				if (rewrite) arr[index] = result;
				else arr.push_back(result);
				if (log) Matrix::showMatrix(result);

				break;
			}
			case 3: {
				int id = std::stoi(fnc::getNumberStringTemplate("������� id �������: ", "int"));

				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "������� � id = " << id << " ��� � ������" << std::endl;
					break;
				}

				if (arr[index].getCols() != arr[index].getRows()) {
					std::cout << "���������� ����� � �������� �� ���������: ����� ������������ ����������" << std::endl;
					exit = fnc::exit();
					break;
				}

				std::cout << "������������ = " << Matrix::calcDet(arr[index]) << std::endl;

				break;
			}
			case 4: {
				if (arr.size() < 2) {
					std::cout << "� ������ ������������� ���������� ������";
					exit = fnc::exit();
					break;
				}

				int id1 = std::stoi(fnc::getNumberStringTemplate("������� id ������ �������: ", "int")),
					id2 = std::stoi(fnc::getNumberStringTemplate("������� id ������ �������: ", "int"));

				int index1 = indexOfId(id1, arr);
				if (index1 == -1) {
					std::cout << "������� � id = " << id1 << " ��� � ������" << std::endl;
					break;
				}

				int index2 = indexOfId(id2, arr);
				if (index2 == -1) {
					std::cout << "������� � id = " << id2 << " ��� � ������" << std::endl;
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
				int id = std::stoi(fnc::getNumberStringTemplate("������� id �������: ", "int"));

				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "������� � id = " << id << " ��� � ������" << std::endl;
					break;
				}

				Matrix matrixA = arr[index];
				if (matrixA.getRows() != matrixA.getCols()) {
					std::cout << "���������� ����� � �������� �� ���������" << std::endl;
					exit = fnc::exit();
					break;
				}
				if (Matrix::calcDet(matrixA) == 0) {
					std::cout << "������������ ����� ����, ����� �������� ������� ����������... ";
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
				int id = std::stoi(fnc::getNumberStringTemplate("������� id �������: ", "int"));

				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "������� � id = " << id << " ��� � ������" << std::endl;
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
			int id = std::stoi(fnc::getNumberStringTemplate("������� id �������: ", "int"));

			int index = indexOfId(id, arr);
			if (index == -1) {
				std::cout << "������� � id = " << id << " ��� � ������" << std::endl;
				break;
			}

			Matrix::showMatrix(arr[index]);
			break;
		}
		case (4): {
			if (arr.size() <= 0) std::cout << "������ ����..." << std::endl;
			else for (int i = 0; i < arr.size(); i++) Matrix::showBasicInfo(arr[i]);
			break;
		}
		case (5): {
			if (arr.size() <= 0) {
				std::cout << "������ ������ ����... " << std::endl;
				break;
			}
			fnc::coutArr({ "1. ������� �� id", "2. ������� ��������� � ������", "3. ������� ���", "4. �����"});
			switch (std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"))) {
			case(1): {
				int id = std::stoi(fnc::getNumberStringTemplate("������� id: "));
				int index = indexOfId(id, arr);
				if (index == -1) {
					std::cout << "������� � id = " << id << " ��� � ������" << std::endl;
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
				fnc::coutArr({"�� �������? ", "1. ��", "2. ���" });
				if (std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int")) != 1) break;

				arr.clear();
				break;
			}
			case(4):
				break;
			}
			break;
		}
		case (6): {
			fnc::coutArr({ "1. ����� ������� � ������� (������ = " + (std::string(log ? "true)" : "false)")), "2. �����" });
			switch (std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"))) {
			case 1: {
				fnc::coutArr({ "�������� ������� � ������� ����� ��������? ", "1. ��", "2. ���" });
				log = (std::stoi(fnc::getNumberStringTemplate("�������� ��������: ", "int"))) == 1 ? true : false;
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
			std::cout << "����� ������� �� ����������" << std::endl;
			break;
		}
		std::cout << std::endl;
	}

	return 0;
}