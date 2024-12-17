#include <iostream>
using namespace std;
const int MAX_SIZE = 100;

class Node
{
public:
    int data;
    Node *next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList
{
private:
    Node *head;
    int size;

    void checkIndex(int index)
    {
        if (index < 0 || index >= size)
        {
            cerr << "Ошибка: индекс вне диапазона" << endl;
            throw logic_error("Индекс вне диапазона");
        }
    }

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    int getSize()
    {
        return size;
    }

    int get(int index)
    {
        checkIndex(index);
        Node *current = head;
        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    void add(int value)
    {
        if (size >= MAX_SIZE)
        {
            cerr << "Ошибка: попытка добавить элемент в список больше максимального размера" << endl;
            throw logic_error("Максимальный размер списка превышен");
        }
        Node *newNode = new Node(value);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        ++size;
    }

    void removeFirst()
    {
        if (size == 0)
        {
            cerr << "Ошибка: попытка удалить элемент из пустого списка" << endl;
            throw logic_error("Список пуст");
        }
        Node *temp = head;
        head = head->next;
        delete temp;
        --size;
    }

    void removeLast()
    {
        if (size == 0)
        {
            cerr << "Ошибка: попытка удалить элемент из пустого списка" << endl;
            throw logic_error("Список пуст");
        }
        if (size == 1)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Node *current = head;
            while (current->next->next != nullptr)
            {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        --size;
    }
};

void printMenu()
{
    cout << "Выберите действие:\n";
    cout << "1. Добавить элемент\n";
    cout << "2. Удалить элемент из начала\n";
    cout << "3. Удалить элемент из конца\n";
    cout << "4. Получить элемент по индексу\n";
    cout << "5. Вывести размер списка\n";
    cout << "6. Выйти\n";
}

int main()
{
    LinkedList list;
    int choice;
    int value;
    int index;

    while (true)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Введите значение для добавления: ";
            cin >> value;
            try
            {
                list.add(value);
                cout << "Элемент добавлен.\n";
            }
            catch (const exception &e)
            {
                cerr << e.what() << endl;
            }
            break;
        case 2:
            try
            {
                list.removeFirst();
                cout << "Элемент удалён из начала.\n";
            }
            catch (const exception &e)
            {
                cerr << e.what() << endl;
            }
            break;
        case 3:
            try
            {
                list.removeLast();
                cout << "Элемент удалён с конца.\n";
            }
            catch (const exception &e)
            {
                cerr << e.what() << endl;
            }
            break;
        case 4:
            cout << "Введите индекс для получения элемента: ";
            cin >> index;
            try
            {
                cout << "Элемент с индексом " << index << ": " << list.get(index) << endl;
            }
            catch (const exception &e)
            {
                cerr << e.what() << endl;
            }
            break;
        case 5:
            cout << "Текущий размер списка: " << list.getSize() << endl;
            break;
        case 6:
            return 0;
        default:
            cerr << "Ошибка: неверный выбор\n";
            break;
        }
    }

    return 0;
}
