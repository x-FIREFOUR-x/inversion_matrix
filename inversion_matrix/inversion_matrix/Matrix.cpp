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
		
		for (int k = i+1; k < size; k++)	// рядок від якого віднімають
		{
			float n = A.ptr_matrix[k][i];			// кількісті рядків i яку потрібно відняти щоб в рядку k і стовбці z утворився нуль (щоб під гол діаг стали нулі)	
			for (int z = 0; z < size; z++)		// стовбці (елементи рядків k, i )
			{
					A.ptr_matrix[k][z] = A.ptr_matrix[k][z] - (A.ptr_matrix[i][z]  * n);
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