#pragma once
using namespace std;
class Matrix
{
	int size;				// ����� �������
	float** ptr_matrix;		// �������� �� ������� 
public:
	Matrix(int);
	Matrix(const Matrix&);

};

