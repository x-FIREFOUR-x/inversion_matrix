#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
class Matrix
{
	int size;				// ����� �������
	float** ptr_matrix;		// �������� �� ������� 
public:
	Matrix(int);
	~Matrix();
	Matrix(const Matrix&);
	void console_read();
	void file_read(string);
	void console_write();
	void file_write(string);
};

