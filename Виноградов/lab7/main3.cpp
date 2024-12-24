#include <iostream>
#include <vector>
#include <algorithm>
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

class task3
{
    Matrix m;
    int max_length = 0;
    vector<int> row_indices;

public:
    task3() : m(Matrix()) {
        m.print();
    }
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
    void runTask()
    {
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
    }
    void print()
    {
        if (row_indices.size() > 1)
            cout << "Строки с самой длинной серией одинаковых элементов: ";
        else
            cout << "Строка с самой длинной серией одинаковых элементов: ";
        for (int index : row_indices)
            cout << index + 1 << " ";
        cout << endl;
    }
};

int
main()
{
    srand(time(0));
    task3 t;
    t.runTask();
    t.print();
    return 0;
}
// Определить номер строки, в которой находится самая длинная серия одинаковых элементов.