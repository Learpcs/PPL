//parallel_for.cpp
#include <locale.h>
#include <time.h>
#include <ppl.h>
#include <iostream>
#include <cmath> 
#define NNN 200

/*
��������� ���������
����� ����. ���.: 17.585 ���.
��������� ���������
����� �����. ���.: 2.113 ���
*/

double TaskOne(int x) {
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

double My_Task(double x) {
    return TaskOne(static_cast<int>(x)); // ���������� � int, ���� �����
}

int main()
{
    setlocale(LC_ALL, ".ACP");
    double V[NNN];
    double Time = clock();

    for (int k = 0; k < NNN; k++) {
        V[k] = My_Task(100 * cos(k));
    }

    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "��������� ���������" << std::endl
        << "����� ����. ���.: " << Time << " ���." << std::endl;

    Time = clock();
    Concurrency::parallel_for(0, NNN, [&V](size_t k) { V[k] = My_Task(100 * cos(k)); });

    Time = (clock() - Time) / CLOCKS_PER_SEC;
    std::cout << "��������� ���������" << std::endl
        << "����� �����. ���.: " << Time << " ���." << std::endl;

    return 0;
}
