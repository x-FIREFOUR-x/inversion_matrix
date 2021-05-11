#include "Matrix.h"
Matrix::Matrix(int s)
{
	size = s;							// ��������� �������� ���� ����� �������
	ptr_matrix = new float* [size];		// �������� ���'�� ��� �������
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
	if (fin.is_open())
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				fin >> ptr_matrix[i][j];
			}
		}
	}
	else
	{

	}
	
}
void Matrix::console_write()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << setprecision(3) << setw(6) << ptr_matrix[i][j] << " ";
		}
		cout << endl;
	}
}
void Matrix::file_write(string file)
{
	ofstream fout;
	fout.open(file);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fout << ptr_matrix[i][j];
		}
		fout << "\n";
	}
}
Matrix Matrix::Gauss()
{
	Matrix A = *this;
	/*Matrix A(size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			A.ptr_matrix[i][j] = ptr_matrix[i][j];
		}
	}*/

	Matrix E(size);							// �������� ������� ��� ����� ��������� �� ����
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				E.ptr_matrix[i][j] = 1;
			}
			else
			{
				E.ptr_matrix[i][j] = 0;
			}
		}
	}
			// ������ ���
	for (int i = 0; i < size; i++)		// ����� ���� ��������
	{
		float coef = A.ptr_matrix[i][i];		// ���������� �� ���� ������� ����� �� �������� ����� ������� ��� ������������ ����. ���. ������� �� �������
		for (int j = 0; j < size; j++)		// ������� (���� ����� i) �� ��� �������������� ���� ������� 1 �� ���
		{
			A.ptr_matrix[i][j] = A.ptr_matrix[i][j] / coef;
			E.ptr_matrix[i][j] = E.ptr_matrix[i][j] / coef;
		}
		
		for (int k = i+1; k < size; k++)	// ����� �� ����� ��������
		{
			float n = A.ptr_matrix[k][i];			// ������ ����� i ��� ������� ������ ��� � ����� k � ������� z ��������� ���� (��� �� ��� ��� ����� ���)	
			for (int z = 0; z < size; z++)		// ������� (�������� ����� k, i )
			{
					A.ptr_matrix[k][z] = A.ptr_matrix[k][z] - (A.ptr_matrix[i][z]  * n);
					E.ptr_matrix[k][z] = E.ptr_matrix[k][z] - (E.ptr_matrix[i][z] * n);
			}

		}
	}
		// �������� ���
	for (int i = size - 1; i >= 0; i--)		// ����� ���� ��������
	{
		for (int k = i - 1; k >= 0; k--)		// ����� �� ����� ��������
		{
			float n = A.ptr_matrix[k][i];			// ������ ����� i ��� ������� ������ ��� � ����� k � ������� z ��������� ����  (��� �� ��� ��� ����� ���)
			for (int z = size - 1; z >= 0; z--)		// ������� (�������� ����� k, i )
			{
				A.ptr_matrix[k][z] = A.ptr_matrix[k][z] - A.ptr_matrix[i][z] * n;
				E.ptr_matrix[k][z] = E.ptr_matrix[k][z] - E.ptr_matrix[i][z] * n;
			}
		}
	}

	return E;
}