// Matrix.cpp
#include <iostream>
#include "Matrix.h"

using namespace std;

void sort(int *mas, int &size)
{
    int min;
    int id;
    for (int i = 0; i < size; i++)
    {
        min = mas[i];
        id = i;
        for (int j = i; j < size; j++)
            if (min > mas[j]) {
                min = mas[j];
                id = j;
            }
        if (id != i)
            swap(mas[i], mas[id]);
    }
}
void Matrix::deleteData()
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] data[i];
    }
    delete[] data;
}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    data = new int *[rows];
    for (int i = 0; i < rows; ++i)
    {
        data[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
        {
            data[i][j] = rand() % 10;
        }
    }
}

Matrix::~Matrix()
{
    Matrix::deleteData();
}

void Matrix::transpose()
{
    int **transposed = new int *[cols];
    for (int i = 0; i < cols; ++i)
    {
        transposed[i] = new int[rows];
        for (int j = 0; j < rows; ++j)
        {
            transposed[i][j] = data[j][i];
        }
    }
    swap(rows, cols);
    Matrix::deleteData();
    data = transposed;
}

void Matrix::rotate()
{
    int **rotated = new int *[cols];
    for (int i = 0; i < cols; ++i)
    {
        rotated[i] = new int[rows];
        for (int j = 0; j < rows; ++j)
        {
            rotated[i][j] = data[rows - 1 - j][i];
        }
    }
    // swap(rows, cols);
    Matrix::deleteData();
    data = rotated;
}

void Matrix::sortRows()
{
    for (int i = 0; i < rows; ++i)
    {
        sort(data[i], cols);
    }
    Matrix::print();
}

void Matrix::reverseColumns()
{
    int **tmp = new int *[cols];
    for (int i = 0; i < cols; ++i)
    {
        tmp[i] = new int[rows];
        for (int j = 0; j < rows; ++j)
        {
            tmp[i][j] = data[i][rows - j - 1];
        }
    }

    deleteData();
    data = tmp;
}

void Matrix::print()
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
