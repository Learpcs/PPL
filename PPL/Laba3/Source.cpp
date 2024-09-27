//parallel_sort.cpp
#include <locale.h>
#include <time.h>
#include <vector>
#include <complex>
#include <algorithm>
#include <ppl.h>
#include <iostream>
#define NNN 50000000
using namespace std;
int main(int argc, char* argv[])
{
    setlocale(LC_ALL, ".ACP");
    vector<double> X0(NNN);
    for (int k = 0; k < NNN; k++)
        X0[k] = sin(k * sqrt(k) / (1 + sqrt(k)));

    vector<double> X = X0;
    double Time = clock();
    sort(X.begin(), X.end(),
        [](const complex<double>& left, const complex<double>& right) {
            return left.real() < right.real(); });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    cout << "Сортировка завершена" << endl
        << "Время посл. сортировки: " << Time << " сек." << endl;
    X = X0;
    Time = clock();
    concurrency::parallel_sort(X.begin(), X.end(),
        [](const complex<double>& left, const complex<double>& right) {
            return left.real() < right.real(); });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    cout << "Сортировка завершена" << endl
        << "Время парал. сортировки: " << Time << " сек." << endl;
    X = X0;
    Time = clock();
    concurrency::parallel_buffered_sort(X.begin(), X.end(),
        [](const complex<double>& left, const complex<double>& right) {
            return left.real() < right.real(); });
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    cout << "Сортировка завершена" << endl
        << "Время парал. сортировки: " << Time << " сек." << endl;
}