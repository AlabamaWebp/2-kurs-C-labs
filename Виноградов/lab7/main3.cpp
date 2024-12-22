#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int longest_series_length(const vector<int>& row) {
    if (row.empty()) return 0;

    int max_length = 1;
    int current_length = 1;

    for (size_t i = 1; i < row.size(); ++i) {
        if (row[i] == row[i - 1]) {
            ++current_length;
        } else {
            max_length = max(max_length, current_length);
            current_length = 1;
        }
    }
    max_length = max(max_length, current_length);

    return max_length;
}

int main() {
    srand(time(0));

    const int rows = 5;
    const int cols = 10;
    vector<vector<int>> matrix(rows, vector<int>(cols));

    for (auto& row : matrix) {
        generate(row.begin(), row.end(), []() { return rand() % 10; });
    }

    int max_length = 0;
    vector<int> row_indices;

    for (size_t i = 0; i < matrix.size(); ++i) {
        int current_length = longest_series_length(matrix[i]);
        if (current_length > max_length) {
            max_length = current_length;
            row_indices.clear();
            row_indices.push_back(i);
        } else if (current_length == max_length) {
            row_indices.push_back(i);
        }
    }

    cout << "Матрица:" << endl;
    for (const auto& row : matrix) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }

    if (!row_indices.empty()) {
        if (row_indices.size() > 1) 
            cout << "Строки с самой длинной серией одинаковых элементов: ";
        else 
            cout << "Строка с самой длинной серией одинаковых элементов: ";
        for (int index : row_indices) 
            cout << index + 1 << " ";
        cout << endl;
    } else {
        cout << "Матрица пуста." << endl;
    }

    return 0;
}
