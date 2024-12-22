#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    const int rows = 4;
    const int cols = 5;
    vector<vector<int>> matrix(rows, vector<int>(cols));
    
    for (auto& row : matrix) {
        generate(row.begin(), row.end(), []() { return rand() % 10; });
    }

    int max_row_index = -1;
    int max_sequence_length = 0;

    for (int i = 0; i < matrix.size(); ++i) {
        int current_length = 1;
        int max_length = 1;
        
        for (int j = 1; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == matrix[i][j-1]) {
                ++current_length;
                max_length = max(max_length, current_length);
            } else {
                current_length = 1;
            }
        }

        if (max_length > max_sequence_length) {
            max_sequence_length = max_length;
            max_row_index = i;
        }
    }

    cout << "Матрица:\n";
    for (const auto& row : matrix) {
        for (int num : row) cout << num << " ";
        cout << endl;
    }
    cout << "Номер строки с самой длинной серией одинаковых элементов: " << max_row_index << endl;

    return 0;
}
