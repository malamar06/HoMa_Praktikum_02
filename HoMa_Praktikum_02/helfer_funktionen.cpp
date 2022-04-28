#include <iostream>
#include "CMyVektor.h"
#include "CMyMatrix.h"
#include <cassert>
using namespace std;
//Can Sana Kafam Girsin

CMyVektor testFunktion3(double x1, double x2, double x3, double x4)
{
	CMyVektor rErgebnis;
	rErgebnis.manual_push(x1 * x2 * exp(x3));
	rErgebnis.manual_push(x2 * x3 * x4);
	rErgebnis.manual_push(x4);
	return rErgebnis;
}

CMyVektor operator*(CMyMatrix A, CMyVektor B)
{
	int spalte = A.get_spalte();
	int linie = A.get_linie();
	int vectorL = B.get_dim();
	assert(vectorL == spalte);
	CMyVektor rErgebnis;
	double aktuelWert = 0;
	for (int i = 0; i < linie; i++)
	{
		for (int j = 0; j < vectorL; j++)
		{
			aktuelWert += A[i][j] * B[j];
		}
		rErgebnis.manual_push(aktuelWert);
		aktuelWert = 0;
	}
	return rErgebnis;
}


CMyVektor operator + (CMyVektor a, CMyVektor b)
{
	int dim_a = a.get_dim();
	int dim_b = b.get_dim();
	if (dim_a != dim_b)
	{
		return 0;//Error return: kann nicht addieren, wegen verschiedenen dimensionen,
	}
	CMyVektor summe;
	for (int i = 0; i < dim_a; i++)
	{
		summe.manual_push(a[i] + b[i]);
	}
	return summe;
}

bool operator == (CMyVektor a, CMyVektor b)
{
	if (a.get_dim() != b.get_dim()) //Prufung ob die von gleicher dimension ist
	{
		return false;
	}
	if (a.lenght() != b.lenght()) //wenn die leange nicht gleich ist, konnen die Vektoren nicht gleich sein
	{
		return false;
	}
	for (int i = 0; i < a.lenght(); i++)
	{
		if (a[i] != b[i])
		{
			return false;
		}
	}
	return true;
}

//Das hier soll villeicht in der Vektorclasse definiert werden, wiel es mit weniger funktionsanrufe funktionieren kann!
//Ich muss damit experimentieren, wie eigentlich operator funktion dahin funktioniert wird. Weil Operatorfunktionen in einer
//Classe nur eine Parameter haben durfen.
CMyVektor operator*(double lambda, CMyVektor a)//Skalar Multiplikation
{
	for (int i = 0; i < a.get_dim(); i++)
	{
		a.set_vektor_werte(i, a[i] * lambda);
	}
	return a;
}

double dummyfunktion1(CMyVektor punkt) //f(x) = x^2y + 5xy + y^2
{
	double ergebnis = 0;
	ergebnis += punkt[0] * punkt[0] * punkt[1];
	ergebnis += 5 * punkt[0] * punkt[1];
	ergebnis += punkt[1] * punkt[1];
	return ergebnis;
}

CMyVektor gradient(CMyVektor x, double (*funktion)(CMyVektor x))//Rechnet der Gradient an Punkt x (type CMyVektor weil f(Xn) : n >= 1
{																// sein kann) und return Gradient als Vektor.
	int dim_x = x.get_dim();
	long double h = 0.00000001; //h um abzuleiten
	CMyVektor derGradient; //return ergebnis
	for (int i = 0; i < dim_x; i++)
	{
		double transporter = 0;
		CMyVektor x1 = x;
		x1.add_zu_vektor_werte(i, h);//f(x + h)
		transporter = (funktion(x1) - funktion(x)) / h;//ableitung formal mit H! Was kann ich hier statt der Division nutzen???
		derGradient.manual_push(transporter);//Der Gradientvektor fuellen
	}
	return derGradient;
}

CMyVektor G_verfahren_ohneInfo(CMyVektor x, double (*funktion)(CMyVektor y), double lambda)
{
	CMyVektor aktuelPunkt = x;
	CMyVektor testPunkt;
	for (int schritt = 0; schritt < 25; schritt++)
	{
		CMyVektor aktuelGradient = gradient(aktuelPunkt, funktion);
		if (aktuelGradient.lenght() < 0.00001)
		{
			return aktuelPunkt;
		}

		testPunkt = aktuelPunkt + lambda * aktuelGradient;
		if (funktion(testPunkt) > funktion(aktuelPunkt))
		{//probieren double lambda zu bewegen
			lambda *= 2;
			CMyVektor doubleTestPunkt = aktuelPunkt + lambda * aktuelGradient;
			if (funktion(doubleTestPunkt) > funktion(testPunkt))
			{
				aktuelPunkt = doubleTestPunkt;
			}
			else
			{
				aktuelPunkt = testPunkt;
			}
		}
		else
		{
			while (funktion(testPunkt) <= funktion(aktuelPunkt))
			{
				lambda = lambda * 0.5;
				testPunkt = aktuelPunkt + lambda * aktuelGradient;
			}
			aktuelPunkt = testPunkt;
		}
	}
	return aktuelPunkt;
}

void G_verfahren(CMyVektor x, double (*funktion)(CMyVektor x), double lambda) //NICHT OPTIMIERT!!! MUSS OPTIMIERT WERDEN!
{
	for (static int schritt = 0; schritt < 25; schritt++)
	{
		if (gradient(x, funktion).lenght() < 0.00001) //Prufung, ob es genug nah ist
		{
			cout << endl << "==============================================";
			cout << endl << "Ende wegen ||grad f(x)||<1e-5 bei" << endl;
			cout << "x = ";
			x.print();
			cout << endl << "lambda = " << lambda << endl;
			cout << "f(x) = " << funktion(x) << endl;
			cout << "grad f(x) = ";
			gradient(x, funktion).print();
			cout << "||grad f(x)|| = " << gradient(x, funktion).lenght() << endl;
			return;
		}

		cout << endl << "==============================================" << "Schritt " << schritt << " :" << endl;
		cout << "x = ";
		x.print();
		cout << "Lambda = " << lambda << endl;
		cout << "f(x) = " << funktion(x) << endl;
		cout << "grad f(x) = ";
		gradient(x, funktion).print();
		cout << "||grad f(x)|| = " << gradient(x, funktion).lenght() << endl;

		CMyVektor x_neu = x + (lambda * gradient(x, funktion)); // ein schritt von start punkt

		cout << endl << "x_neu = ";
		x_neu.print();
		cout << "f(x_neu) = " << funktion(x_neu) << endl;

		if (funktion(x_neu) <= funktion(x)) //Wenn diese bedingung Wahr ist, dann bedeutet es, dass das Lambda zu Gross genommen ist.
		{									//Gradient verwiesst die korrekte Richtung, deswegen muss man die Menge des Verfahrens abnehmen.
			while (funktion(x_neu) <= funktion(x)) //Das Lambda halbieren und nochmal rechnen, ob x_neu noch kleiner ist
			{
				lambda = lambda * 0.5;
				cout << endl << "Halbiere Schrittweite: lambda = " << lambda << endl;
				x_neu = x + (lambda * gradient(x, funktion));//nochmal mit halbierte Lambda rechnen
				cout << endl << "x_neu = ";
				x_neu.print();
				cout << endl << "f(x_neu) = " << funktion(x_neu) << endl;
			}
			//wenn x_neu nicht mehr kleiner geht, korrektes Lambda gefunden,damit gewunchte Weg gegangen, und mit Verfahren weiter machen.
			x = x_neu;
		}
		else
		{
			//wenn wir in Korrekte Richtung (gradient) wie Lambda Weit gehen und gewuenchte Ergebnis( f(x_neu) > f(x) ) bekommen,
			//probieren wir die dasselbe operation mit Lambda*2 zu machen. Weil wir wissen mochten, ob wir in diesem Schritt mehr machen koennen. 
			lambda = lambda * 2;
			cout << endl << "Test mit doppelter Schrittweite (lambda = " << lambda << "):" << endl;
			CMyVektor x_test = x + (lambda * gradient(x, funktion));//nochmal mit verdoppelte Lambda rechnen
			cout << "x_test = ";
			x_test.print();
			cout << "f(x_test) = " << funktion(x_test) << endl;
			//kann ich doppel leange gehen ?
			if (funktion(x_test) > funktion(x_neu))//Ja, ich kann mit verdoppelte Lambda
			{
				x = x_test;
				cout << "verdoppele Schrittweite!";
			}
			else								   //Nein, ich kann nicht mit verdoppelte Lambda
			{
				x = x_neu;
				cout << "behalte alte Schrittweite!";
			}
		}
	}
	//Wenn das Program an dieser Linie kommt, die Schleife ist voll durchgegangen und das gewunchte neahe nicht gefunden.
	//Enden wir der Verfharen hier, nachdem 25 schritte gerechnet wurde. Einfach die info printen und das funktion beenden.
	cout << endl << "==============================================" << endl;
	cout << "Ende wegen Schrittanzahl = 25 bei" << endl;
	cout << "x = ";
	x.print();
	cout << endl << "lambda = " << lambda << endl;
	cout << "f(x) = " << funktion(x) << endl;
	cout << "grad f(x) = ";
	gradient(x, funktion).print();
	cout << "||grad f(x)|| = " << gradient(x, funktion).lenght() << endl;
	cout << "==============================================" << endl;
	return;
}

double testFunktion1(CMyVektor x) // erste funktion von aufgabeblatt f(x)
{
	double ergebnis = 0;
	ergebnis += sin(x[0] * x[1]);
	ergebnis += sin(x[0]);
	ergebnis += cos(x[1]);
	return ergebnis;
}

double testFunktion2(CMyVektor x)// zweite funktion von aufgabeblatt g(x)
{
	double ergebnis = 0;
	ergebnis += 2 * x[0] * x[0];
	ergebnis -= 2 * x[0] * x[1];
	ergebnis += x[1] * x[1];
	ergebnis += x[2] * x[2];
	ergebnis -= 2 * x[0];
	ergebnis -= 4 * x[2];
	ergebnis *= -1;
	return ergebnis;
}