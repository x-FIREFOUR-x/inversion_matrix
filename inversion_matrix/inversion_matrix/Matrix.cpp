#include "Matrix.h"
Matrix::Matrix(int s)
{
	size_line = s;			// присвоєння значення кількості рядків
	size_column = s;		// присвоєння значення кількості стовбців

	ptr_matrix = new float* [size_line];		// виділення пам'яті для матриці
	for (int i = 0; i < size_line; i++)
		ptr_matrix[i] = new float[size_column];
}
Matrix::Matrix(int l, int c)
{
	size_line = l;			// присвоєння значення кількості рядків
	size_column = c;		// присвоєння значення кількості стовбців

	ptr_matrix = new float* [size_line];		// виділення пам'яті для матриці
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
Matrix Matrix::Gauss()
{
	if (size_line == size_column)
	{
		Matrix A = *this;						// створення обєкта копії вхідної матриці
		/*Matrix A(size);
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				A.ptr_matrix[i][j] = ptr_matrix[i][j];
			}
		}*/

		int size = size_line;		// вхідна матриця повинна бути квадратною
		Matrix E(size);							// одинична матриця яка стане оберненою до даної
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
		// прямий хід
		for (int i = 0; i < size; i++)		// рядок який віднімають
		{
			float coef = A.ptr_matrix[i][i];		// коефіцієнт на який потрібно ділити всі елементи рядка матриці для перетворення елем. гол. діагоналі на одиниці
			for (int j = 0; j < size; j++)		// стовбці (елем рядка i) які теж перебразуються коли роблять 1 на діаг
			{
				A.ptr_matrix[i][j] = A.ptr_matrix[i][j] / coef;
				E.ptr_matrix[i][j] = E.ptr_matrix[i][j] / coef;
			}

			for (int k = i + 1; k < size; k++)	// рядок від якого віднімають
			{
				float n = A.ptr_matrix[k][i];			// кількісті рядків i яку потрібно відняти щоб в рядку k і стовбці z утворився нуль (щоб під гол діаг стали нулі)	
				for (int z = 0; z < size; z++)		// стовбці (елементи рядків k, i )
				{
					A.ptr_matrix[k][z] = A.ptr_matrix[k][z] - (A.ptr_matrix[i][z] * n);
					E.ptr_matrix[k][z] = E.ptr_matrix[k][z] - (E.ptr_matrix[i][z] * n);
				}

			}
		}
		// зворотній хід
		for (int i = size - 1; i >= 0; i--)		// рядок який віднімають
		{
			for (int k = i - 1; k >= 0; k--)		// рядок від якого віднімають
			{
				float n = A.ptr_matrix[k][i];			// кількісті рядків i яку потрібно відняти щоб в рядку k і стовбці z утворився нуль  (щоб під гол діаг стали нулі)
				for (int z = size - 1; z >= 0; z--)		// стовбці (елементи рядків k, i )
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
Matrix Matrix::multiplication(Matrix A, Matrix B)
{
	if (A.size_column == B.size_line)
	{
		Matrix C(A.size_line, B.size_column);
		for (int i = 0; i < A.size_line; i++)
		{
			for (int j = 0; j < B.size_column; j++)
			{
				float S = 0;
				for (int k = 0; k < A.size_column; k++)
				{
					S += A.ptr_matrix[i][k] * B.ptr_matrix[k][j];
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
 Matrix Matrix::inversion_order2(Matrix A)
{
	 if (A.size_line == A.size_column && A.size_line == 2)
	 {
		 Matrix B(A.size_line, A.size_column);		// обернена матриці матриці A
		 float det = (A.ptr_matrix[0][0] * A.ptr_matrix[1][1]) - (A.ptr_matrix[0][1] * A.ptr_matrix[1][0]);		// визначник матриці A

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