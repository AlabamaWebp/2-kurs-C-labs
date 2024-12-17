#include <iostream>
using namespace std;
const int MAX_SIZE = 100;
class Vector {
private:
    int* data;
    int size;

    void checkIndex(int index) {
        if (index < 0 || index >= size) {
            // cerr << "Ошибка: индекс вне диапазона" << endl;
            throw logic_error("Индекс вне диапазона");
        }
    }

public:
    Vector() {
        size = 0;
        data = new int();
    }

    ~Vector() {
        delete[] data;
    }

    int getSize() {
        return size;
    }

    int get(int index) {
        checkIndex(index);
        return data[index];
    }

    void add(int value) {
        if ((size + 1) >= MAX_SIZE) {
            throw logic_error("Максимальный размер вектора превышен");
        }
        data[size++] = value;
    }

    void removeFirst() {
        if (size == 0) {
            // cerr << "Ошибка: попытка удалить элемент из пустого вектора" << endl;
            throw logic_error("Вектор пуст");
        }
        for (int i = 1; i < size; ++i) {
            data[i - 1] = data[i];
        }
        --size;
    }

    void removeLast() {
        if (size == 0) {
            // cerr << "Ошибка: попытка удалить элемент из пустого вектора" << endl;
            throw logic_error("Вектор пуст");
        }
        --size;
    }
};

void printMenu() {
    cout << "Выберите действие:\n";
    cout << "1. Добавить элемент\n";
    cout << "2. Удалить элемент из начала\n";
    cout << "3. Удалить элемент из конца\n";
    cout << "4. Получить элемент по индексу\n";
    cout << "5. Вывести размер вектора\n";
    cout << "6. Выйти\n";
}

int main() {
    Vector vec;
    int choice;
    int value;
    int index;

    while (true) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите значение для добавления: ";
                cin >> value;
                try {
                    vec.add(value);
                    cout << "Элемент добавлен.\n";
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 2:
                try {
                    vec.removeFirst();
                    cout << "Элемент удалён из начала.\n";
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 3:
                try {
                    vec.removeLast();
                    cout << "Элемент удалён с конца.\n";
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 4:
                cout << "Введите индекс для получения элемента: ";
                cin >> index;
                try {
                    cout << "Элемент с индексом " << index << ": " << vec.get(index) << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            case 5:
                cout << "Текущий размер вектора: " << vec.getSize() << endl;
                break;
            case 6:
                return 0;
            default:
                cerr << "Ошибка: неверный выбор" << endl;
                break;
        }
    }

    return 0;
}
