#include "Matrix.h"
Matrix::Matrix(int s)
{
	size = s;							// ��������� �������� ���� ����� �������
	ptr_matrix = new float* [size];		// �������� ���'�� ��� �������
	for (int i = 0; i < size; i++)
		ptr_matrix[i] = new float[size];
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
