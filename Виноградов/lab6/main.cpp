#include <iostream>
using namespace std;
class Matrix
{
private:
    int rows;
    int cols;
    int **data;

public:
    Matrix() : rows(0), cols(0), data(nullptr) {}

    Matrix(int r, int c) : rows(r), cols(c)
    {
        data = new int *[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols]();
            for (int j = 0; j < cols; j++)
                data[i][j] = rand() % 10;
        }
    }

    ~Matrix()
    {
        for (int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
    }

    void display()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    void transpose()
    {
        int **transposed = new int *[cols];
        for (int i = 0; i < cols; ++i)
            transposed[i] = new int[rows];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                transposed[j][i] = data[i][j];

        for (int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;

        data = transposed;
        swap(rows, cols);
    }

    void reverseColumns()
    {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols / 2; ++j)
                swap(data[i][j], data[i][cols - j - 1]);
    }

    void sortRows()
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                for (int k = 0; k < cols - 1; ++k)
                {
                    if (data[i][k] > data[i][k+1])
                    {
                        swap(data[i][j], data[i][k]);
                    }
                }
            }
        }
    }

    void rotatePoChasovoi()
    {
        transpose();
        reverseColumns();
    }
};

int main()
{
    int rows = 2, cols = 2;
    Matrix matrix(rows, cols);

    cout << "Исходная матрица:" << endl;
    matrix.display();

    int choice;
    do
    {
        cout << "Выберите действие: \n"
             << "1 - Транспонировать матрицу\n"
             << "2 - Повернуть матрицу по часовой стрелке\n"
             << "3 - Сортировать строки\n"
             << "4 - Изменить порядок столбцов на обратный\n"
             << "0 - Выход\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            matrix.transpose();
            cout << "Транспонированная матрица:" << endl;
            matrix.display();
            break;
        case 2:
            matrix.rotatePoChasovoi();
            cout << "Матрица после поворота:" << endl;
            matrix.display();
            break;
        case 3:
            matrix.sortRows();
            cout << "Матрица после сортировки строк:" << endl;
            matrix.display();
            break;
        case 4:
            matrix.reverseColumns();
            cout << "Матрица с обратным порядком столбцов:" << endl;
            matrix.display();
            break;
        case 0:
            cout << "Выход..." << endl;
            break;
        default:
            cout << "Недопустимый выбор, попробуйте снова." << endl;
        }

    } while (choice != 0);

    return 0;
}