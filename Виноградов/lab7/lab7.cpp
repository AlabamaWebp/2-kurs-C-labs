#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ctime>

using namespace std;

class Matrix
{
public:
    const int rows = 5;
    const int cols = 10;
    vector<vector<int>> data;
    Matrix()
    {
        data = vector<vector<int>>(rows, vector<int>(cols));
        for (auto &row : data)
        {
            generate(row.begin(), row.end(), []()
                     { return rand() % 10; });
        }
    }
    void print()
    {
        cout << "Матрица:" << endl;
        for (const auto &row : data)
        {
            for (int num : row)
            {
                cout << num << " ";
            }
            cout << endl;
        }
    }
};

class lab7
{
public:
    void fillMas(vector<double> &arr)
    {
        generate(arr.begin(), arr.end(), []()
                 { return (rand() % 20 - 10) / 1.0; });
    }
    double summAfterMax(vector<double> &arr)
    {
        auto min_elem = min_element(arr.begin(), arr.end());
        auto max_elem = max_element(arr.begin(), arr.end());
        if (min_elem > max_elem)
            swap(min_elem, max_elem);
        return accumulate(min_elem + 1, max_elem, 1.0, multiplies<double>());
    }
    /// task2
    double sum(vector<double> &arr)
    {
        auto pos_elem = find_if(arr.begin(), arr.end(), [](double x)
                                { return x > 0; });
        return accumulate(pos_elem + 1, arr.end(), 0.0);
    }
    void rebase(vector<double> &arr)
    {
        double a = -2.0, b = 2.0;
        partition(arr.begin(), arr.end(), [a, b](double x)
                  { return x >= a && x <= b; });
    }
    // task3
    void show(vector<double> &arr)
    {
        // cout << "Массив: ";
        for (double num : arr)
            cout << num << " ";
        cout << endl;
    }
    // lab3
    vector<int> matixFindMaxInRows(Matrix m)
    {
        vector<int> row_indices;
        int max_length = 0;
        for (int i = 0; i < m.rows; ++i)
        {
            int cur_len = findLongest(m.data[i]);
            if (cur_len > max_length)
            {
                max_length = cur_len;
                row_indices.clear();
                row_indices.push_back(i);
            }
            else if (cur_len == max_length)
                row_indices.push_back(i);
        }
        return row_indices;
    }

private:
    int findLongest(vector<int> &row)
    {
        if (row.empty())
            return 0;

        int max_length = 1;
        int current_length = 1;

        for (int i = 1; i < row.size(); ++i)
        {
            if (row[i] == row[i - 1])
                ++current_length;
            else
            {
                max_length = max(max_length, current_length);
                current_length = 1;
            }
        }
        max_length = max(max_length, current_length);

        return max_length;
    }
};
int main()
{
    srand(time(0));
    int N = 10;
    vector<double> arr = vector<double>(N);
    lab7 t;
    cout << "Задание 1" << endl;
    // произведение элементов массива, расположенных между максимальным и минимальным элементами.
    t.fillMas(arr);
    t.show(arr);
    cout << t.summAfterMax(arr) << endl;
    // 2
    cout << "Задание 2" << endl;
    // сумму элементов массива, расположенных после первого положительного элемента. Преобразовать массив таким образом,
    // чтобы сначала располагались все элементы, целая часть которых лежит в интервале [а,Ь], а потом - все остальные.
    cout << "Сумма элементов после первого положительного: " << t.sum(arr) << endl;
    t.rebase(arr);
    cout << "Преобразованный массив: ";
    t.show(arr);
    // 3
    cout << "Задание 3" << endl;
    // Определить номер строки, в которой находится самая длинная серия одинаковых элементов.
    Matrix m;
    m.print();
    vector<int> row_indices = t.matixFindMaxInRows(m);
    if (row_indices.size() > 1)
        cout << "Строки с самой длинной серией одинаковых элементов: ";
    else if (row_indices.size() == m.rows)
    {
        cout << "Нет строки с самой длинной серией одинаковых элементов: ";
        return 0;
    }
    else
        cout << "Строка с самой длинной серией одинаковых элементов: ";

    for (int index : row_indices)
        cout << index + 1 << " ";
    cout << endl;
    return 0;
}
