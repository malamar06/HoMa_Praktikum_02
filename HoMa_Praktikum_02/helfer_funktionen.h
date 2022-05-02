#pragma once
#include "CMyVektor.h"
#include "CMyMatrix.h"

CMyVektor newtonVerfahren2dim(CMyVektor startpunkt, CMyVektor(*funktion)(CMyVektor x));

CMyVektor testFunktion6(CMyVektor x);

void G_verfahren_mini_staticlambda(CMyVektor x, double (*funktion)(CMyVektor y), double lambda);

CMyMatrix jacobi(CMyVektor x, CMyVektor(*funktion)(CMyVektor x));

CMyVektor operator*(CMyMatrix A, CMyVektor B);

double testFunktion5(CMyVektor x);

double testFunktion4(CMyVektor x);

CMyVektor operator - (CMyVektor a, CMyVektor b);

void G_verfahren_mini(CMyVektor x, double (*funktion)(CMyVektor y), double lambda);

CMyVektor testFunktion3(CMyVektor x);

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

