//parallel_transform.cpp
#include <locale.h>
#include <time.h>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <ppl.h>
#include <iostream>
#include <cmath>
#define N1 200

double Task2(int x) {
	double ans = 0;
	int end = std::max(20, 20 * std::abs(x));
	for (int k = 1; k <= end; k++) {
		for (int j = 1; j <= end; j++) {
			double numerator = x * x;
			double denominator = x * x + 2 * k * k + j * j;
			if (denominator != 0) {
				ans += numerator / denominator * sin((k + 2 * j) * x);
			}
		}
	}
	return ans;
}



double My_Task(double x, double y) {
	return Task2(static_cast<int>(x));
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, ".ACP");
	std::vector<double> vX0(N1);
	std::deque<double> dX0(N1);
	std::list<double> lX0(N1);
	for (int k = 1; k <= N1; k++) {
		vX0[k - 1] = 100 * cos(k);
		dX0.push_back(vX0[k - 1]);
		lX0.push_back(vX0[k - 1]);
	}

	std::vector<double> vY0(N1);
	std::deque<double> dY0(N1);
	std::list<double> lY0(N1);
	for (int k = 1; k <= N1; k++) {
		vY0[k - 1] = 100 * cos(k);
		dY0.push_back(vY0[k - 1]);
		lY0.push_back(vY0[k - 1]);
	}


	double Time = clock();
	std::vector<double>::iterator vIt = std::transform(vX0.begin(), vX0.end(), vY0.begin(), vY0.begin(), My_Task);
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Вектор последовательно - Преобразование завершено" << std::endl
		<< "Время посл. обр: " << Time << " сек." << std::endl;
	Time = clock();

	std::deque<double>::iterator dIt = std::transform(dX0.begin(), dX0.end(), dY0.begin(), dY0.begin(), My_Task);
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Дек последовательно - Преобразование завершено" << std::endl
		<< "Время посл. обр: " << Time << " сек." << std::endl;
	Time = clock();

	std::list<double>::iterator lIt = std::transform(lX0.begin(), lX0.end(), lY0.begin(), lY0.begin(), My_Task);
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Лист последовательно - Преобразование завершено" << std::endl
		<< "Время посл. обр: " << Time << " сек." << std::endl;

	Time = clock();
	vIt = concurrency::parallel_transform(vX0.begin(), vX0.end(), vY0.begin(), vY0.begin(), My_Task);
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Вектор параллельно - Преобразование завершено" << std::endl
		<< "Время парал. обр.: " << Time << " сек." << std::endl;

	Time = clock();
	dIt = concurrency::parallel_transform(dX0.begin(), dX0.end(), dY0.begin(), dY0.begin(), My_Task);
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Дек параллельно - Преобразование завершено" << std::endl
		<< "Время парал. обр.: " << Time << " сек." << std::endl;

	Time = clock();
	lIt = concurrency::parallel_transform(lX0.begin(), lX0.end(), lY0.begin(), lY0.begin(), My_Task);
	Time = (clock() - Time) / CLOCKS_PER_SEC;
	std::cout << "Лист параллельно - Преобразование завершено" << std::endl
		<< "Время парал. обр.: " << Time << " сек." << std::endl;
}