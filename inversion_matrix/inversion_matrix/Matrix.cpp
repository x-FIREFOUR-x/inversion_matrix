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

 Matrix Matrix::div_cells()
{
	 if (size_line == size_column)
	 {
		 Matrix A11(size_line - 1, size_column - 1);		// 4 матриці на які поділені матриця A
		 Matrix A12(size_line - 1, 1);
		 Matrix A21(1, size_column - 1);
		 Matrix A22(1, 1);

			// поділ матриці A на 4 матриці розміром (n-1, n-1) (n-1, 1) (1, n-1) (1, 1)
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
						 A21.ptr_matrix[size_line -i -1][j] = ptr_matrix[i][j];
					 }
					 else
					 {
						 A22.ptr_matrix[size_line - i -1 ][size_column - j - 1] = ptr_matrix[i][j];
					 }
				 }
			 }
		 }

		 if (A11.size_column > 1)
		 {
			 Matrix A11_i = A11.div_cells();
			 Matrix X = multiplication(A11_i, A12);
			 Matrix Y = multiplication(A21, A11_i);
			 Matrix Q = multiplication(Y, A12);
			 Q = A22 - Q;
			 Matrix Q_i = inversion_order1(Q);

			 Matrix B11(size_line - 1, size_column - 1);		// 4 матриці на які поділена обернена матриця A
			 Matrix B12(size_line - 1, 1);
			 Matrix B21(1, size_column - 1);
			 Matrix B22(1, 1);

			 Matrix B11_ = multiplication(X, Q_i);
			 B11 = multiplication(B11_, Y);
			 B11 = A11_i + B11;
			 B12 = multiplication(X, Q_i);
			 B12 = -B12;
			 B21 = multiplication(Q_i, Y);
			 B21 = -B21;
			 B22 = Q_i;

			 Matrix B(size_line, size_column);		// обернена матриця до A, яка складається з B11, B12, B21, B22

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
			 Matrix A11_i = inversion_order1(A11);
			 Matrix X = multiplication(A11_i, A12);
			 Matrix Y = multiplication(A21, A11_i);
			 Matrix Q = multiplication(Y, A12);
			 Q = A22 - Q;
			 Matrix Q_i = inversion_order1(Q);

			 Matrix B11(size_line - 1, size_column - 1);		// 4 матриці на які поділена обернена матриця A
			 Matrix B12(size_line - 1, 1);
			 Matrix B21(1, size_column - 1);
			 Matrix B22(1, 1);

			 B11 = multiplication(X, Q_i);
			 B11 = multiplication(B11, Y);
			 B11 = A11_i + B11;
			 B12 = multiplication(X, Q_i);
			 B12 = -B12;
			 B21 = multiplication(Q_i, Y);
			 B21 = -B21;
			 B22 = Q_i;

			 Matrix B(size_line, size_column);		// обернена матриця до A, яка складається з B11, B12, B21, B22

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
							 B.ptr_matrix[i][j] = B12.ptr_matrix[i][size_column - j -1];
						 }
					 }
					 else
					 {
						 if (j < size_column - 1)
						 {
							 B.ptr_matrix[i][j] = B21.ptr_matrix[size_line - i -1][j];
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