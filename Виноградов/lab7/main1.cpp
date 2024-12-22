#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int N = 10;
    vector<double> arr(N);
    generate(arr.begin(), arr.end(), []() { return rand() % 10; });

    auto min_elem = min_element(arr.begin(), arr.end());
    auto max_elem = max_element(arr.begin(), arr.end());

    if (min_elem > max_elem) swap(min_elem, max_elem);

    double p = accumulate(min_elem + 1, max_elem, 1.0, multiplies<double>());

    cout << "Массив: ";
    for (double num : arr) cout << num << " ";
    cout << "\nПроизведение элементов: " << p << endl;

    return 0;
}
