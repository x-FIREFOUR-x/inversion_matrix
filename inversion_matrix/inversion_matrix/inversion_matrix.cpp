#include <iostream>
#include <ctime>
#include "Matrix.h"
using namespace std;

int main()
{
	srand(time(NULL));

	/*Matrix A(4);
	A.random(-20, 50);
	//A.console_read();
	cout << endl;
	A.console_write();
	//Matrix B(4);
	Matrix B = A.Gauss();
	cout << endl;
	B.console_write();

	bool correct;
	Matrix C = A.div_cells(correct);
	cout << endl;
	C.console_write();

	if (A.determinant() != 0)
	{
		Matrix E1 = A * B;
		cout << endl;
		E1.console_write();
	}
	else
	{
		cout << "Matrix det =0 (Guess)" << endl;
	}
	
	if (correct)
	{
		Matrix E2 = A * C;
		cout << endl;
		E2.console_write();
	}
	else
	{
		cout << "dont correct operation div cells" << endl;
	}
	*/
		
	/*Matrix A(4);
	A.console_read();
	cout << endl;
	A.console_write();
	float det = A.determinant();
	cout << det << endl;

	if (det == 0)
	{
		cout << "det";
	}*/

	/*Matrix A(3, 2);
	A.console_read();

	Matrix B(2, 3);
	B.console_read();

	Matrix C = Matrix::multiplication(A, B);
	C.console_write();*/

	/*Matrix A(2, 2);
	A.console_read();

	Matrix B(2, 2);
	B.console_read();

	Matrix C = Matrix::multiplication(B, A);
	C.console_write();*/

	/*Matrix A(2, 2);
	A.console_read();

	Matrix C = Matrix::inversion_order2(A);
	C.console_write();*/

	/*Matrix A(2);
	A.console_read();
	Matrix B(2);
	B.console_read();
	Matrix C = A + B;
	C.console_write();*/

	return 0;

}

