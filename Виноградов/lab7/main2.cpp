#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
void output(vector<double> arr)
{
    for (const auto &elem : arr)
    {
        cout << elem << " ";
    }
    cout << endl;
}
int main()
{
    const int N = 10;
    vector<double> arr(N);
    generate(arr.begin(), arr.end(), []()
             { return (rand() % 20 - 10) / 1.0; });

    auto pos_elem = find_if(arr.begin(), arr.end(), [](double x)
                            { return x > 0; });
    double sum = accumulate(pos_elem + 1, arr.end(), 0.0);
    cout << "Сумма элементов после первого положительного: " << sum << endl;

    output(arr);

    double a = -2.0, b = 2.0;
    partition(arr.begin(), arr.end(), [a, b](double x)
              { return x >= a && x <= b; });

    cout << "Преобразованный массив: ";
    output(arr);

    return 0;
}
