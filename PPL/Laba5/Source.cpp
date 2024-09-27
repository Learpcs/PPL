//parallel_task_group.cpp
#include <locale.h>
#include <time.h>
#include <ppl.h>
#include <iostream>
#define NNN 1000
using namespace std;

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
    return TaskOne(static_cast<int>(x)); // Приведение к int, если нужно
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, ".ACP");
    double V[NNN];
    double Time = clock();
    for (int k = 0; k < NNN; k++) V[k] = My_Task(k);
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    cout << "Подзадачи завершены. Время: " << Time << " сек." << endl;
    Concurrency::task_group TGr;
    Time = clock();
    for (int k = 0; k < NNN; k++) TGr.run([&V, k]() {V[k] = My_Task(k); });
    TGr.wait();
    Time = (clock() - Time) / CLOCKS_PER_SEC;
    cout << "Подзадачи завершены. Время: " << Time << " сек." << endl;
}