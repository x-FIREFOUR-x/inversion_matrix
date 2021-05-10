#include "Matrix.h"
Matrix::Matrix(int s)
{
	size = s;							// присвоєння значення полю розмір матриці
	ptr_matrix = new float* [size];		// виділення пам'яті для матриці
	for (int i = 0; i < size; i++)
		ptr_matrix[i] = new float[size];
}
Matrix::~Matrix()
{
	for (int i = 0; i < size; i++)
		delete[]ptr_matrix[i];
	delete[]ptr_matrix;
}
Matrix::Matrix(const Matrix& origin)
{
	size = origin.size;

	ptr_matrix = new float* [size];
	for (int i = 0; i < size; i++)
		ptr_matrix[i] = new float[size];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ptr_matrix[i][j] = origin.ptr_matrix[i][j];
		}
	}

}
void Matrix::console_read()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cin >> ptr_matrix[i][j];
		}
	}
}
void Matrix::file_read(string file)
{
	ifstream fin;
	fin.open(file);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fin >> ptr_matrix[i][j];
		}
	}
}