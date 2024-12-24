#include <iostream>
using namespace std;

int get_rand()
{
    return rand() % 50 + 1;
}

class Node
{
public:
    int data;
    Node *next;
    Node(int d) : data(d), next(nullptr) {}
};

class LinkedList
{
private:
    Node *head;
    int size;
    const int max_size = 100;

    void checkIndex(int index)
    {
        if (index < 0 || index >= size)
        {
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
        if (size >= max_size)
        {
            cerr << "Ошибка: попытка добавить элемент в список больше максимального размера" << endl;
            throw logic_error("Максимальный размер списка превышен");
        }
        Node *newNode = new Node(value);
        if (head == nullptr)
            head = newNode;
        else
        {
            Node *current = head;
            while (current->next != nullptr)
                current = current->next;
            current->next = newNode;
        }
        ++size;
    }

    void removeFirst()
    {
        if (size == 0)
        {
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

    void showAll()
    {
        Node *current = head;
        for (int i = 0; i < size; i++)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

void showMenu()
{
    cout << "Выберите действие:\n";
    cout << "1. Добавить элемент\n";
    cout << "2. Удалить элемент из начала\n";
    cout << "3. Удалить элемент из конца\n";
    cout << "4. Получить элемент по индексу\n";
    cout << "5. Вывести размер списка\n";
    cout << "6. Вывести все элементы\n";
    cout << "0. Выйти\n";
}

int main()
{
    LinkedList list;
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
                list.add(get_rand());
                cout << "Элемент добавлен.\n";
                break;
            case 2:
                list.removeFirst();
                cout << "Элемент удалён из начала.\n";
                break;
            case 3:
                list.removeLast();
                cout << "Элемент удалён с конца.\n";
                break;
            case 4:
                cout << "Введите индекс для получения элемента: ";
                cin >> index;
                cout << "Элемент с индексом " << index << ": " << list.get(index) << endl;
                break;
            case 5:
                cout << "Текущий размер списка: " << list.getSize() << endl;
                break;
            case 6:
                list.showAll();
                break;
            case 0:
                return 0;
            default:
                cerr << "Ошибка: неверный выбор\n";
                break;
            }
        }
        catch (exception &e)
        {
            cerr << e.what() << endl;
        }
    }

    return 0;
}
