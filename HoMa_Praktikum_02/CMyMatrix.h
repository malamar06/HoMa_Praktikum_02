#pragma once
#include <vector>


class CMyMatrix
{
private:
	int linie;
	int spalte;
	std::vector<std::vector<double>> matrix;
public:

	void schoen_print();

	void pushLinie(std::vector<double> newmatrixlinie);

	std::vector<double> operator[](int pos);

	int get_spalte();

	int get_linie();

	CMyMatrix(int linie_zahl, int spalte_zahl, std::vector<double> eingabe_arr);

	CMyMatrix();

	void matrix_setter(int linie_pos, int spalte_pos, double wert);

	double matrix_getter(int linie_pos, int spalte_pos);

	CMyMatrix invers_2x2();
	
	void print();
};