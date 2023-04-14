#pragma once
#include <vector>
#include <math.h>
#include "mainFunctions.h"
#include <iostream>
using namespace fnc;
using namespace std;

class Matrix {
private:
	static int idCounter;
	//rows - ���������� �����, columns - ���������� ��������, lineLength - ������������ ����� ������
	int _rows, _columns, _lineLength;
public:
	int id;
	//��������� ������
	std::vector<std::vector<double>> arr = {};
	
	//�������, ����������� �������� ���������� ����� ��� �������� � �������.
	int getRows() { return this->_rows; }
	int getCols() { return this->_columns; }

	//�����������, ��� �������� ������� �������, gen - ��������� �������, ���� false, �� ������ ����������;
	//options - ���������, ���� true, �� ��������� ������� ����������� ��� ��������� ��������� �����
	Matrix(int rows, int columns, bool gen = true, bool options = false, int seed = 0, int left = 0, int right = 0) {
		this->_rows = rows;
		this->_columns = columns;
		this->_lineLength = 0;
		//���������� ����������� ���������� idCounter
		this->id = this->idCounter++;

		if (!gen) genUserMatrix(this->arr, rows, columns, this->_lineLength);

		else if (options) fnc::genRandMatrix(this->arr, rows, columns, this->_lineLength, seed, left, right);
		
		else fnc::genRandMatrix(this->arr, rows, columns, this->_lineLength);

	}
	
	//������� �����������
	Matrix(int rows, int columns, int lineLength) {
		this->_rows = rows;
		this->_columns = columns;
		this->_lineLength = lineLength;
		this->id = this->idCounter++;
		
	}

	//������� ������� ������� � �������
	static void showMatrix(Matrix& matrix) {
		if (matrix.arr.size() == 0) {
			std::cout << "������� ������" << std::endl;
			return;
		}

		std::cout << " >>> �������: " << std::endl;
		std::cout << std::endl;
		std::string line = "";
		int length = matrix._columns * matrix._lineLength + (matrix._columns - 1) * 3 + 2;
		while (line.length() < length) line += '-';
		

		for (int i = 0; i < matrix._rows; i++) {
			std::cout << "|";
			for (int j = 0; j < matrix._columns; j++) {
				std::cout << fnc::enchanceStr(fnc::trimNRound(std::to_string(matrix.arr[i][j]), 2), matrix._lineLength);
				if (j != matrix._columns - 1) std::cout << " | ";
			}
			std::cout << "|" << std::endl;
			if (!(i == matrix._rows - 1)) std::cout << line << std::endl;
		}
		std::cout << std::endl;


	}

	//������� ������� ���������� � ������� � ���� ������
	static void showBasicInfo(Matrix& matrix) {
		std::cout << "ID = " << matrix.id << " || ������ = " << matrix._rows << "x" << matrix._columns << " || �������� = ";
		std::cout << "{";

		for (int i = 0; i < matrix._rows; i++) {
			std::cout << "{";
			for (int j = 0; j < matrix._columns; j++) {
				if (j != matrix._columns - 1) std::cout << matrix.arr[i][j] << ", ";
				else std::cout << matrix.arr[i][j];
			}
			if (i != matrix._rows - 1) std::cout << "}, ";
			else std::cout << "}";
		}

		std::cout << "}" << std::endl;;
	}

	
	//������� ������������� ������� � ���������� �����
	static Matrix getTranspMatrix(Matrix& matrix) {
		if (matrix._rows == 0 || matrix._columns == 0) return Matrix(0, 0, 0);
		Matrix resultMatrix(matrix._columns, matrix._rows, matrix._lineLength);
		resultMatrix.arr = fnc::transPos(matrix.arr, matrix._rows, matrix._columns);

		return resultMatrix;
	}

	//������� ���������� ������������
	static double calcDet(Matrix& matrix) {
		if (matrix._columns != matrix._rows) return 0;
		return fnc::calcDet(matrix.arr);
	}

	//�������� ���� ������, ������� ���������� ������ �������
	static Matrix addition(Matrix& matrixA, Matrix& matrixB) {
		if (matrixA._rows != matrixB._rows || matrixA._columns != matrixB._columns) return Matrix(0, 0, 0);

		Matrix resultMatrix(matrixA._rows, matrixA._columns, 0);
		std::vector<double> tempArr;
		for (int i = 0; i < matrixA._rows; i++) {
			tempArr = {};
			for (int j = 0; j < matrixA._columns; j++) {
				tempArr.push_back(matrixA.arr[i][j] + matrixB.arr[i][j]);

				fnc::checkLineLength(resultMatrix._lineLength, matrixA.arr[i][j]);
			}
			resultMatrix.arr.push_back(tempArr);
		}
		return resultMatrix;
	}

	//��������� ������� �� �����, ������� ���������� ������ �������
	static Matrix multOnNumber(Matrix& matrix, double multiplier) {
		Matrix resultMatrix(matrix._rows, matrix._columns, 0);
		std::vector<double> tempArr;
		double tmp;
		for (int i = 0; i < matrix._rows; i++) {
			tempArr = {};
			for (int j = 0; j < matrix._columns; j++) {
				tmp = matrix.arr[i][j] * multiplier;
				tempArr.push_back(tmp);

				fnc::checkLineLength(resultMatrix._lineLength, tmp);
			}
			resultMatrix.arr.push_back(tempArr);
		}
		return resultMatrix;
	}

	//��������� ������� matrixA �� ������� matrixB, ���������� ������ �������
	static Matrix multiply(Matrix& matrixA, Matrix& matrixB) {
		if (matrixA._columns != matrixB._rows) return Matrix(0, 0, 0);

		Matrix resultMatrix(matrixA._rows, matrixB._columns, 0);
		std::vector<double> tempArr;
		double res;

		for (int i = 0; i < matrixA._rows; i++) {
			tempArr = {};
			for (int j = 0; j < matrixB._columns; j++) {
				res = 0;
				for (int k = 0; k < matrixA._columns; k++) {
					res += matrixA.arr[i][k] * matrixB.arr[k][j];
				}
				tempArr.push_back(res);

				fnc::checkLineLength(resultMatrix._lineLength, res);
			}
			resultMatrix.arr.push_back(tempArr);
		}

		return resultMatrix;
	}

	//���������� �������� �������, ���������� ������ �������
	static Matrix calcInversed(Matrix& matrix) {
		double det = fnc::calcDet(matrix.arr);
		if (det == 0) return Matrix(0, 0, 0);
		double res;
		Matrix resultMatrix(matrix._rows, matrix._columns, 0);

		std::vector<double> tempArr;
		for (int i = 0; i < matrix._rows; i++) {
			tempArr = {};
			for (int j = 0; j < matrix._columns; j++) {
				res = fnc::calcDet(fnc::getAlgAdd(matrix.arr, i, j)) / det;
				if ((i + j) % 2 == 1) res = -res;
				fnc::checkLineLength(resultMatrix._lineLength, res);
				tempArr.push_back(res);
			}
			resultMatrix.arr.push_back(tempArr);
		}
		resultMatrix.arr = fnc::transPos(resultMatrix.arr, resultMatrix._rows, resultMatrix._columns);
		//��� ���������������� ������� �������� ����� � �������� �������� �������

		
		int tmp = resultMatrix._rows;
		resultMatrix._rows = resultMatrix._columns;
		resultMatrix._columns = tmp;

		std::cout << "success";
		return resultMatrix;
		
	}

};
//������������� ����������� ���������� idCounter
int Matrix::idCounter = 0;