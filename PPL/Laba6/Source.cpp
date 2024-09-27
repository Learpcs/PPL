//concurrent_vector.cpp
#define _USE_MATH_DEFINES
#include <locale.h>
#include <time.h>
#include <vector>
#include <ppl.h>
#include <concurrent_vector.h>
#include <iostream>
#include <cmath>
#define N1 400 //����� ����� �� ������� �����������
#define N2 50

double Func(double x, double y)
{
	double Tmp = 0;
	for (int k = 1; k <= N2; k++)
		for (int j = 1; j <= N2; j++)
			Tmp += cos(k * x) * sin(j * y) / ((1 + k + j) * sqrt(1 + k * k * k * k + j * j * j * j));
	return Tmp;
}

struct Point
{
	double x, y, f;
	Point(double _x, double _y, double _f)
	{
		x = _x; y = _y; f = _f;
	}
};

const double eps = 1e-4;

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".ACP");
	std::vector<Point> Pts;
	double h = 2.0 * M_PI / N1;
	double Time = clock();
	for (int k = 0; k < N1; k++)
		for (int j = 0; j < N1; j++) {
			double x = h * k;
			double y = h * j;
			double f = Func(x, y);
			if (Func(x, y + eps) - f < 0)
				Pts.push_back(Point(x, y, f));
		}
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "���������� ���������. ������ ����������: " << Pts.size() << std::endl
		<< "����� : " << Time << " ���." << std::endl;
	Pts.clear();
	concurrency::concurrent_vector<Point> CPts;
	Time = clock();
	concurrency::parallel_for(0, N1,
		[&CPts, h](int k) {
			for (int j = 0; j < N1; j++) {
				double x = h * k;
				double y = h * j;
				double f = Func(x, y);
				if (Func(x, y + eps) - f < 0)
					CPts.push_back(Point(x, y, f));
			}}
	);
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "���������� ���������. ������ ����������: " << CPts.size() << std::endl
		<< "����� : " << Time << " ���." << std::endl;
	CPts.clear();
}