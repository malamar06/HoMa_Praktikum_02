#include <iostream>
#include "CMyVektor.h"
#include "helfer_funktionen.h"
#include "CMyMatrix.h"
#include <vector>


int main()
{
	CMyVektor control(1, 1);

	newtonVerfahren2dim(control, testFunktion6);
	
	//CMyVektor control2(1, 2, 0, 3);
	//jacobi(control2 ,testFunktion3).schoen_print();

	return 0;
} 