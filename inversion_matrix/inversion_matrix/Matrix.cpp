#include "Matrix.h"
Matrix::Matrix(int s)
{
	size_line = s;			// ��������� �������� ������� �����
	size_column = s;		// ��������� �������� ������� ��������

	ptr_matrix = new float* [size_line];		// �������� ���'�� ��� �������
	for (int i = 0; i < size_line; i++)
		ptr_matrix[i] = new float[size_column];
}
Matrix::Matrix(int l, int c)
{
	size_line = l;			// ��������� �������� ������� �����
	size_column = c;		// ��������� �������� ������� ��������

	ptr_matrix = new float* [size_line];		// �������� ���'�� ��� �������
	for (int i = 0; i < size_line; i++)
		ptr_matrix[i] = new float[size_column];
}
Matrix::~Matrix()
{
	for (int i = 0; i < size_line; i++)
		delete[]ptr_matrix[i];
	delete[]ptr_matrix;
}
Matrix::Matrix(const Matrix& origin)
{
	size_line = origin.size_line;
	size_column = origin.size_column;

	ptr_matrix = new float* [size_line];
	for (int i = 0; i < size_line; i++)
		ptr_matrix[i] = new float[size_column];

	for (int i = 0; i < size_line; i++)
	{
		for (int j = 0; j < size_column; j++)
		{
			ptr_matrix[i][j] = origin.ptr_matrix[i][j];
		}
	}

}

void Matrix::console_read()
{
	for (int i = 0; i < size_line; i++)
	{
		for (int j = 0; j < size_column; j++)
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
		for (int i = 0; i < size_line; i++)
		{
			for (int j = 0; j < size_column; j++)
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
	for (int i = 0; i < size_line; i++)
	{
		for (int j = 0; j < size_column; j++)
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
	for (int i = 0; i < size_line; i++)
	{
		for (int j = 0; j < size_column; j++)
		{
			fout << ptr_matrix[i][j];
		}
		fout << "\n";
	}
}

void Matrix::random(int min, int max)
{
	for (int i = 0; i < size_line; i++)
	{
		for (int j = 0; j < size_column; j++)
		{
			ptr_matrix[i][j] = rand() % (max - min + 1) + min;
		}
	}
}

float Matrix::determinant()
{
	if (size_line == size_column)
	{
		float determinant = 1;
		
		Matrix A = *this;
		float c_det = 1;   // ���������� �� ���� ������� ��������� ���������, �������� ������������ ����������� �� ���� ����������
	
		for (int i = 0; i < size_line; i++)
		{
			if (A.ptr_matrix[i][i] == 0)			// ����� ����� ������ ���� ��� 0
			{
				int number = i;		// ����� ���������� �����
				for (int k = i; k < size_line; k++)		// ����� ���������� �����
				{
					if (A.ptr_matrix[k][i] != 0)
					{
						number = k;
						break;
					}
				}
				if (number == i)
				{
					determinant = 0;
					break;
				}
				float* temp;
				temp = A.ptr_matrix[i];
				A.ptr_matrix[i] = A.ptr_matrix[number];
				A.ptr_matrix[number] = temp;

				c_det *= -1;
			}

			float coef = A.ptr_matrix[i][i];		// ���������� �� ���� ������� ����� �� �������� ����� ������� ��� ������������ ����. ���. ������� �� �������
			c_det *= coef;	
			for (int j = 0; j < size_column; j++)		// ������� (���� ����� i) �� ��� �������������� ���� ������� 1 �� ���
			{
				A.ptr_matrix[i][j] = A.ptr_matrix[i][j] / coef;
			}

			for (int k = i + 1; k < size_line; k++)	// ����� �� ����� ��������
			{
				float n = A.ptr_matrix[k][i];			// ������ ����� i ��� ������� ������ ��� � ����� k � ������� z ��������� ���� (��� �� ��� ��� ����� ���)	
				for (int z = 0; z < size_column; z++)		// ������� (�������� ����� k, i )
				{
					A.ptr_matrix[k][z] = A.ptr_matrix[k][z] - (A.ptr_matrix[i][z] * n);
				}

			}
		}

		for (int i = 0; i < size_line; i++)			// ��������� ��������� �� ������� ���� ��� ������� ������� �� �������� �������
		{
			determinant *= A.ptr_matrix[i][i];
		}
		determinant *= c_det;

		return determinant;
	}
}

Matrix Matrix::Gauss()
{
	if (size_line == size_column)
	{
		Matrix A = *this;						// ��������� ����� ��ﳿ ������ �������

		int size = size_line;		// ������ ������� ������� ���� ����������
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
			if (A.ptr_matrix[i][i] == 0)			// ����� ����� ������ ���� ��� 0
			{
				int number = i;		// ����� ���������� �����
				for (int k = i; k < size; k++)		// ����� ���������� �����
				{
					if (A.ptr_matrix[k][i] != 0)
					{
						number = k;
						break;
					}
				}
				float* temp;
				temp = A.ptr_matrix[i];
				A.ptr_matrix[i] = A.ptr_matrix[number];
				A.ptr_matrix[number] = temp;
				temp = E.ptr_matrix[i];
				E.ptr_matrix[i] = E.ptr_matrix[number];
				E.ptr_matrix[number] = temp;
			}

			float coef = A.ptr_matrix[i][i];		// ���������� �� ���� ������� ����� �� �������� ����� ������� ��� ������������ ����. ���. ������� �� �������
			for (int j = 0; j < size; j++)		// ������� (���� ����� i) �� ��� �������������� ���� ������� 1 �� ���
			{
				A.ptr_matrix[i][j] = A.ptr_matrix[i][j] / coef;
				E.ptr_matrix[i][j] = E.ptr_matrix[i][j] / coef;
			}

			for (int k = i + 1; k < size; k++)	// ����� �� ����� ��������
			{
				float n = A.ptr_matrix[k][i];			// ������ ����� i ��� ������� ������ ��� � ����� k � ������� z ��������� ���� (��� �� ��� ��� ����� ���)	
				for (int z = 0; z < size; z++)		// ������� (�������� ����� k, i )
				{
					A.ptr_matrix[k][z] = A.ptr_matrix[k][z] - (A.ptr_matrix[i][z] * n);
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
	else
	{
		cout << endl << "Guess input not squre" << endl;
		return 0;
	}
}
Matrix Matrix::div_cells()
{
	if (size_line == size_column)
	{
		Matrix A11(size_line - 1, size_column - 1);		// 4 ������� �� �� ������ ������� A
		Matrix A12(size_line - 1, 1);
		Matrix A21(1, size_column - 1);
		Matrix A22(1, 1);

		// ���� ������� A �� 4 ������� ������� (n-1, n-1) (n-1, 1) (1, n-1) (1, 1)
		for (int i = 0; i < size_line; i++)
		{
			for (int j = 0; j < size_column; j++)
			{
				if (i < size_line - 1)
				{
					if (j < size_column - 1)
					{
						A11.ptr_matrix[i][j] = ptr_matrix[i][j];
					}
					else
					{
						A12.ptr_matrix[i][size_column - j - 1] = ptr_matrix[i][j];
					}
				}
				else
				{
					if (j < size_column - 1)
					{
						A21.ptr_matrix[size_line - i - 1][j] = ptr_matrix[i][j];
					}
					else
					{
						A22.ptr_matrix[size_line - i - 1][size_column - j - 1] = ptr_matrix[i][j];
					}
				}
			}
		}

		// ����� ������ (���� ������� �������� �� ����� ������� ���� �� ���� ���� �� ����� �� �������� ������� ��� 1)
		if (A11.size_column > 2)
		{
			Matrix A11_i = A11.div_cells();			// ������ ������ ��� ����������� �������� �� A11 ������ ���� �� ����� ������ 1
			Matrix X = A11_i * A12;
			Matrix Y = A21 * A11_i;
			Matrix Q = A22 - (Y * A12);
			Matrix Q_i = inversion_order1(Q);

			Matrix B11(size_line - 1, size_column - 1);		// 4 ������� �� �� ������� �������� ������� A
			Matrix B12(size_line - 1, 1);
			Matrix B21(1, size_column - 1);
			Matrix B22(1, 1);

			B11 = A11_i + (X * Q_i * Y);
			B12 = -(X * Q_i);
			B21 = -(Q_i * Y);
			B22 = Q_i;

			Matrix B(size_line, size_column);		// �������� ������� �� A, ��� ���������� � B11, B12, B21, B22

			   // ��������� ������� ������ B �� ����
			for (int i = 0; i < size_line; i++)
			{
				for (int j = 0; j < size_column; j++)
				{
					if (i < size_line - 1)
					{
						if (j < size_column - 1)
						{
							B.ptr_matrix[i][j] = B11.ptr_matrix[i][j];
						}
						else
						{
							B.ptr_matrix[i][j] = B12.ptr_matrix[i][size_column - j - 1];
						}
					}
					else
					{
						if (j < size_column - 1)
						{
							B.ptr_matrix[i][j] = B21.ptr_matrix[size_line - i - 1][j];
						}
						else
						{
							B.ptr_matrix[i][j] = B22.ptr_matrix[size_line - i - 1][size_column - j - 1];
						}
					}
				}
			}

			return B;
		}
		else
		{
			Matrix A11_i = inversion_order2(A11);
			Matrix X = A11_i * A12;
			Matrix Y = A21 * A11_i;
			Matrix Q = A22 - (Y * A12);
			Matrix Q_i = inversion_order1(Q);

			Matrix B11(size_line - 1, size_column - 1);		// 4 ������� �� �� ������� �������� ������� A
			Matrix B12(size_line - 1, 1);
			Matrix B21(1, size_column - 1);
			Matrix B22(1, 1);

			B11 = A11_i + (X * Q_i * Y);
			B12 = -(X * Q_i);
			B21 = -(Q_i * Y);
			B22 = Q_i;

			Matrix B(size_line, size_column);		// �������� ������� �� A, ��� ���������� � B11, B12, B21, B22

			   // ��������� ������� ������ B �� ����
			for (int i = 0; i < size_line; i++)
			{
				for (int j = 0; j < size_column; j++)
				{
					if (i < size_line - 1)
					{
						if (j < size_column - 1)
						{
							B.ptr_matrix[i][j] = B11.ptr_matrix[i][j];
						}
						else
						{
							B.ptr_matrix[i][j] = B12.ptr_matrix[i][size_column - j - 1];
						}
					}
					else
					{
						if (j < size_column - 1)
						{
							B.ptr_matrix[i][j] = B21.ptr_matrix[size_line - i - 1][j];
						}
						else
						{
							B.ptr_matrix[i][j] = B22.ptr_matrix[size_line - i - 1][size_column - j - 1];
						}
					}
				}
			}

			return B;
		}


	}
	else
	{
		cout << endl << "div_cells input not squre matrix" << endl;
		return 0;
	}
}

 Matrix Matrix::inversion_order2(Matrix A)
{
	 if (A.size_line == A.size_column && A.size_line == 2)
	 {
		 Matrix B(A.size_line, A.size_column);		// �������� ������� ������� A
		 float det = (A.ptr_matrix[0][0] * A.ptr_matrix[1][1]) - (A.ptr_matrix[0][1] * A.ptr_matrix[1][0]);		// ��������� ������� A

		 B.ptr_matrix[0][0] = A.ptr_matrix[1][1] / det;
		 B.ptr_matrix[0][1] = -1 * A.ptr_matrix[0][1] / det;
		 B.ptr_matrix[1][0] = -1 * A.ptr_matrix[1][0] / det;
		 B.ptr_matrix[1][1] = A.ptr_matrix[0][0] / det;

		 return B;
	 }
	 else
	 {
		 cout << endl << "inversion input not correct matrix" << endl;
		 return 0;
	 }
}
 Matrix Matrix::inversion_order1(Matrix A)
 {
	 if (A.size_line == A.size_column && A.size_line == 1)
	 {
		 Matrix B(A.size_line, A.size_column);
		 B.ptr_matrix[0][0] = 1 / A.ptr_matrix[0][0];
		 return B;
	 }
	 else
	 {
		 cout << endl << "inversion_1 input not correct matrix" << endl;
		 return 0;
	 }
 }

 Matrix Matrix::operator-(const Matrix B)
 {
	 Matrix C(size_line, size_column);

	 for (int i = 0; i < size_line; i++)
	 {
		 for (int j = 0; j < size_column; j++)
		 {
			 C.ptr_matrix[i][j] = ptr_matrix[i][j] - B.ptr_matrix[i][j];
		 }
	 }

	 return C;
 }
 Matrix Matrix:: operator-()
 {
	 Matrix C(size_line, size_column);

	 for (int i = 0; i < size_line; i++)
	 {
		 for (int j = 0; j < size_column; j++)
		 {
			 C.ptr_matrix[i][j] = 0 - ptr_matrix[i][j];
		 }
	 }
	 return C;
 }
 Matrix Matrix::operator+(const Matrix B)
 {
	 Matrix C(size_line, size_column);

	 for (int i = 0; i < size_line; i++)
	 {
		 for (int j = 0; j < size_column; j++)
		 {
			 C.ptr_matrix[i][j] = ptr_matrix[i][j] + B.ptr_matrix[i][j];
		 }
	 }

	 return C;
 }
 Matrix Matrix::operator=(const Matrix& A)
 {
	 for (int i = 0; i < size_line; i++)
	 {
		 for (int j = 0; j < size_column; j++)
		 {
			 ptr_matrix[i][j] = A.ptr_matrix[i][j];
		 }
	 }
	 return *this;
 }
 Matrix Matrix::operator*(const Matrix& B)
 {
	 if (size_column == B.size_line)
	 {
		 Matrix C(size_line, B.size_column);
		 for (int i = 0; i < size_line; i++)
		 {
			 for (int j = 0; j < B.size_column; j++)
			 {
				 float S = 0;
				 for (int k = 0; k < size_column; k++)
				 {
					 S += ptr_matrix[i][k] * B.ptr_matrix[k][j];
				 }
				 C.ptr_matrix[i][j] = S;
			 }
		 }
		 return C;
	 }
	 else
	 {
		 cout << endl << "multiplicate input not correct matrix" << endl;
		 return 0;
	 }
 }