#include <iostream>
#include <cassert>
#include "CMyMatrix.h"
#include "CMyVektor.h"
#include <iomanip>

void CMyMatrix::pushLinie(std::vector<double> newmatrixlinie)//um eine leere matrix einzufullen
{
	if (spalte != 0)
	{
		assert(newmatrixlinie.size() == spalte);
	}
	else
	{
		spalte = newmatrixlinie.size();
	}
	matrix.push_back(newmatrixlinie);
	linie++;
	return;
}

std::vector<double> CMyMatrix::operator[](int pos)
{
	return matrix[pos];
}

int CMyMatrix::get_spalte()
{
	return spalte;
}

int CMyMatrix::get_linie()
{
	return linie;
}

CMyMatrix::CMyMatrix(int linie_zahl, int spalte_zahl, std::vector<double> eingabe_arr)
{	
	assert(eingabe_arr.size() == linie_zahl * spalte_zahl);
	linie = linie_zahl;
	spalte = spalte_zahl;
	int counter = 0;//um in der eingabe_arr durchzulaufen	
	for (int i = 0; i < linie; i++)
	{
		std::vector<double> aktuele_linie;
		for (int j = 0; j < spalte; j++)
		{
			aktuele_linie.push_back(eingabe_arr[counter]);
			counter++;
		}
		matrix.push_back(aktuele_linie);
		aktuele_linie.clear();
	}
}


CMyMatrix::CMyMatrix()//leer matrix konstrukter
{
	linie = 0;
	spalte = 0;
	matrix.clear();
}

void CMyMatrix::matrix_setter(int linie_pos, int spalte_pos, double wert)
{
	matrix[linie_pos][spalte_pos] = wert;
}

double CMyMatrix::matrix_getter(int linie_pos, int spalte_pos)
{
	return matrix[linie_pos][spalte_pos];
}

CMyMatrix CMyMatrix::invers_2x2()
{
	//Inverse Formel: Matrix(abcd)^-1 = (1/ad - bc) * Matrix(d-b-ca)
	//hoeverszahl = 1 / (x11*x22 - x12*x21) 
	assert(linie == 2 || spalte == 2);
	//x11(a)=matrix[0][0] x12(b) = matrix[0][1] x21(c)=matrix[1][0] x22(d)=matrix[1][1]
	double hoeverszahl = 1 / (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
	std::vector<double> matrixWerte;
	matrixWerte.push_back(matrix[1][1] * hoeverszahl);
	matrixWerte.push_back(matrix[0][1] * hoeverszahl * -1);
	matrixWerte.push_back(matrix[1][0] * hoeverszahl * -1);
	matrixWerte.push_back(matrix[0][0] * hoeverszahl);
	CMyMatrix ergebnisMatrix(2, 2, matrixWerte);
	return ergebnisMatrix;
}

void CMyMatrix::print()
{
	for (int i = 0; i < linie; i++)
	{
		std::cout << "| ";
		for (int j = 0; j < spalte; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << "|\n";
	}
}

void CMyMatrix::schoen_print()
{
	for (int i = 0; i < linie; i++)
	{
		std::cout << "| ";
		for (int j = 0; j < spalte; j++)
		{
			std::cout.width(8);
			std::cout << std::setprecision(5) << matrix[i][j];
			if (j +1 == spalte)//if die lätzte spalte
			{
				std::cout << " ";
			}
			else
			{
				std::cout << "; ";
			}
		}
		std::cout << "|\n";
	}
}
