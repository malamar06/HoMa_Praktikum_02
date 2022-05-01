#include <iostream>
#include "CMyVektor.h"
#include "helfer_funktionen.h"
#include "CMyMatrix.h"
#include <vector>


int main()
{
	CMyVektor control(1, 1);

	newtonVerfahren2dim(control, testFunktion6);
	


	return 0;
} 