#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Matrix
{
	int size;				// розмір матриці
	float** ptr_matrix;		// покажчик на матрицю 
public:
	Matrix(int);
	Matrix(const Matrix&);
	void console_read();
	void file_read(string);
};

