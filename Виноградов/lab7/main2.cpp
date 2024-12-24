#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class task2
{
    const int N = 10;
    vector<double> arr;

public:
    task2()
    {
        arr = vector<double>(N);
        generate(arr.begin(), arr.end(), []()
                 { return (rand() % 20 - 10) / 1.0; });
        output();
    }
    void output()
    {
        for (double &elem : arr)
        {
            cout << elem << " ";
        }
        cout << endl;
    }
    double sum()
    {
        auto pos_elem = find_if(arr.begin(), arr.end(), [](double x)
                                { return x > 0; });
        return accumulate(pos_elem + 1, arr.end(), 0.0);
    }
    void rebase()
    {
        double a = -2.0, b = 2.0;
        partition(arr.begin(), arr.end(), [a, b](double x)
                  { return x >= a && x <= b; });
    }
};
int main()
{
    task2 t;
    cout << "Сумма элементов после первого положительного: " << t.sum() << endl;
    t.rebase();
    cout << "Преобразованный массив: ";
    t.output();
    return 0;
}
// сумму элементов массива, расположенных после первого положительного элемента. Преобразовать массив таким образом,
// чтобы сначала располагались все элементы, целая часть которых лежит в интервале [а,Ь], а потом - все остальные.