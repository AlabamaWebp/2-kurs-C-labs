#include <iostream>
using namespace std;

int get_rand()
{
    return rand() % 50 + 1;
}

class Vector
{
private:
    int *data;
    int size;
    const int max_size = 100;

    void checkIndex(int index)
    {
        if (index < 0 || index >= size)
            throw logic_error("Индекс вне диапазона");
    }

public:
    Vector()
    {
        size = 0;
        data = new int();
    }

    ~Vector()
    {
        delete[] data;
    }

    int getSize()
    {
        return size;
    }

    int get(int index)
    {
        checkIndex(index);
        return data[index];
    }

    void add(int value)
    {
        if ((size + 1) >= max_size)
            throw logic_error("Максимальный размер вектора превышен");
        data[size++] = value;
    }

    void showAll()
    {
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        cout << endl;
    }

    void removeFirst()
    {
        if (size == 0)
            throw logic_error("Вектор пуст");
        for (int i = 1; i < size; ++i)
            data[i - 1] = data[i];
        --size;
    }

    void removeLast()
    {
        if (size == 0)
            throw logic_error("Вектор пуст");
        --size;
    }
};

void showMenu()
{
    cout << "Выберите действие:\n";
    cout << "1. Добавить элемент\n";
    cout << "2. Удалить элемент из начала\n";
    cout << "3. Удалить элемент из конца\n";
    cout << "4. Получить элемент по индексу\n";
    cout << "5. Вывести размер вектора\n";
    cout << "6. Вывести все элементы\n";
    cout << "0. Выйти\n";
}

int main()
{
    Vector vec;
    int choice;
    int index;

    while (true)
    {
        showMenu();
        cin >> choice;
        try
        {
            switch (choice)
            {
            case 1:
                vec.add(get_rand());
                cout << "Элемент добавлен.\n";
                break;
            case 2:
                vec.removeFirst();
                cout << "Элемент удалён из начала.\n";
                break;
            case 3:
                vec.removeLast();
                cout << "Элемент удалён с конца.\n";
                break;
            case 4:
                cout << "Введите индекс для получения элемента: ";
                cin >> index;
                cout << "Элемент с индексом " << index << ": " << vec.get(index) << endl;
                break;
            case 5:
                cout << "Текущий размер вектора: " << vec.getSize() << endl;
                break;
            case 6:
                vec.showAll();
                break;
            case 0:
                return 0;
            default:
                cerr << "Ошибка: неверный выбор" << endl;
                break;
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << endl;
        }
    }

    return 0;
}
