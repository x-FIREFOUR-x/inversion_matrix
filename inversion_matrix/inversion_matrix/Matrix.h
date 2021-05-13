#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
class Matrix
{
	//int size;				// ����� �������
	int size_line;			// ������� ����� �������
	int size_column;		// ������� �������� �������
	float** ptr_matrix;		// �������� �� ������� 

	
public:
	Matrix(int);
	Matrix(int, int);
	~Matrix();
	Matrix(const Matrix&);
	void console_read();
	void file_read(string);
	void console_write();
	void file_write(string);
	Matrix Gauss();
	static Matrix inversion_order2(Matrix);				// ��������� ������� ������� 2
	static Matrix inversion_order1(Matrix);				// ��������� ������� ������� 1
	Matrix div_cells();
	Matrix operator-(const Matrix);
	Matrix operator+(const Matrix);
	Matrix operator-();
	Matrix operator=(const Matrix&);
	Matrix operator*(const Matrix&);
};

