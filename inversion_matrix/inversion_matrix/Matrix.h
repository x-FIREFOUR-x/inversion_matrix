#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
class Matrix
{
	//int size;				// розмір матриці
	int size_line;			// кількість рядків матриці
	int size_column;		// кількість стовбців матриці
	float** ptr_matrix;		// покажчик на матрицю 

	
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
	static Matrix multiplication(Matrix, Matrix);		// множення довільної матриці яку можна помножити
	static Matrix inversion_order2(Matrix);				// обернення матриці порядку 2
};

