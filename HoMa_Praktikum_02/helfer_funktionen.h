#pragma once
#include "CMyVektor.h"
#include "CMyMatrix.h"

CMyVektor testFunktion3(double x1, double x2, double x3, double x4);

CMyVektor operator*(CMyMatrix A, CMyVektor B);

CMyVektor operator + (CMyVektor a, CMyVektor b);

CMyVektor operator*(double lambda, CMyVektor a);

bool operator == (CMyVektor a, CMyVektor b);

double dummyfunktion1(CMyVektor punkt); //f(x) = x^2y + 5xy + y^2

CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x));

void G_verfahren(CMyVektor x, double (*funktion)(CMyVektor x), double lambda = 1);

double testFunktion1(CMyVektor x); // erste funktion von aufgabeblatt f(x)

double testFunktion2(CMyVektor x); // zweite funktion von aufgabeblatt g(x)

CMyVektor G_verfahren_ohneInfo(CMyVektor x, double (*funktion)(CMyVektor y), double lambda = 1);

