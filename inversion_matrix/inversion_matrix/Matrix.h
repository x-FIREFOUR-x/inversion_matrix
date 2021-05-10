#pragma once
using namespace std;
class Matrix
{
	int size;				// розмір матриці
	float** ptr_matrix;		// покажчик на матрицю 
public:
	Matrix(int);
	Matrix(const Matrix&);

};

