#include <iostream>
#include "Matrix.h"
using namespace std;

void showMenu() {
    cout << "1. Транспонировать матрицу" << endl;
    cout << "2. Повернуть матрицу" << endl;
    cout << "3. Сортировать строки матрицы" << endl;
    cout << "4. Изменить порядок столбцов на обратный" << endl;
    cout << "0. Выход" << endl;
}

int main() {
    cout << "Текущая матрица:" << endl;
    Matrix m(3, 3);
    m.print();
    int choice;

    do {
        showMenu();
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
                m.transpose();
                cout << "Матрица транспонирована." << endl;
                break;
            case 2:
                m.rotate();
                cout << "Матрица повернута." << endl;
                break;
            case 3:
                m.sortRows();
                cout << "Строки матрицы отсортированы." << endl;
                break;
            case 4:
                m.reverseColumns();
                cout << "Порядок столбцов изменен на обратный." << endl;
                break;
            case 0:
                cout << "Выход из программы." << endl;
                return 0;
            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
                break;
        }
        cout << endl;
        m.print();
    } while (choice != 6);

    return 0;
}
