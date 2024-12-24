#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>

using namespace std;

class task1
{
    int N = 10;
    vector<double> arr = vector<double>(N);

public:
    task1()
    {
        generate(arr.begin(), arr.end(), []()
                 { return rand() % 10; });
    }
    double findMax()
    {

        auto min_elem = min_element(arr.begin(), arr.end());
        auto max_elem = max_element(arr.begin(), arr.end());

        if (min_elem > max_elem)
            swap(min_elem, max_elem);

        return accumulate(min_elem + 1, max_elem, 1.0, multiplies<double>());
    }
    void show()
    {
        cout << "Массив: ";
        for (double num : arr)
            cout << num << " ";
        cout << endl;
    }
};

int main()
{
    srand(time(0));
    task1 t;
    t.show();
    cout << t.findMax() << endl;
    return 0;
}
// произведение элементов массива, расположенных между максимальным и минимальным элементами.