//parallel_radixsort.cpp
#include <locale.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <ppl.h>
#include <iostream>
#include <cmath>
#define NNN 100000000
using namespace std;
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".ACP");
	vector<double> X0(NNN);
	for (int k = 0; k < NNN; k++)
		X0[k] = 4e9 * sin(k * sqrt(k) / (1 + sqrt(k)));
	vector<double> X(X0);//������������ �����

	double Time = clock();
	sort(X.begin(), X.end());
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	cout << "���������� ���������" << endl
		<< "����� ����. ����������: " << Time << " ���." << endl;
	X = X0;
	Time = clock();
	concurrency::parallel_sort(X.begin(), X.end());
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	cout << "���������� ���������" << endl
		<< "����� parallel_sort: " << Time << " ���." << endl;
	X = X0;
	Time = clock();
	concurrency::parallel_buffered_sort(X.begin(), X.end());
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	cout << "���������� ���������" << endl
		<< "����� parallel_buffered_sort: " << Time << " ���." << endl;
	X = X0;
	Time = clock();
	concurrency::parallel_radixsort(X.begin(), X.end());
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	cout << "���������� ���������" << endl
		<< "����� parallel_radix_sort: " << Time << " ���." << endl;

}