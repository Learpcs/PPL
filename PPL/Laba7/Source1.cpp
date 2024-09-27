#define _USE_MATH_DEFINES //Simps_Tst.cpp
#include <iostream>
#include <cmath>
#include <time.h>
#include "Header.h"
#include <locale.h>
using namespace std;

class My_Class {
private:
	double y;
	const int NNN = 200000; //����� ��������� ������� ��������������
	const double _Inf = 5000.0; //����������� ������� ������ ��������������
public:
	My_Class(double _y = 0.0) { y = _y; }
	double Sub_Int_Func(double x)
	{
		double Tmp = 15 * log(10.0) + log(abs(x)) - sqrt(x);
		int N = Tmp > 0 ? ceil(Tmp * Tmp + 1) : 1;
		double P = exp(-sqrt(abs(x)));
		double Tmp2 = y * y + x * x;
		for (int k = 0; k <= N; k++)
			P *= cos(x / (sqrt(Tmp2) + exp(sqrt((double)k)) * cos(1.0 / (k + 1))));
		return P;
	}

	double Quad()
	{
		return MethodCall::Simpson(0.0, _Inf, NNN, [this](double x) {return Sub_Int_Func(x); });
	}

	double Concurrent_Quad()
	{
		return MethodCall::Concurrent_Simpson(0.0, _Inf, NNN, [this](double x) {return Sub_Int_Func(x); });
	}

};


int main(void)
{
	setlocale(LC_ALL, ".ACP");
	double y;
	cout << "y="; cin >> y;

	My_Class TObj(y);
	double Tms = clock();
	double F = TObj.Quad();
	Tms = (clock() - Tms) / CLOCKS_PER_SEC;
	cout.precision(8);
	cout << "F=" << F << endl << "�����=" << Tms << " �" << endl;
	Tms = clock();
	F = TObj.Concurrent_Quad();
	Tms = (clock() - Tms) / CLOCKS_PER_SEC;
	cout << "F=" << F << endl << "�����=" << Tms << " �" << endl;
}