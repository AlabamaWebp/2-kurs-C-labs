/******************************************************************************
Создать файл f, компоненты которого являются целыми числами.
Получить файл g, образованный из компонент файла f, имеющих четные цифры.
*******************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

int get_rand()
{
    int tmp = rand() % 10;
    return tmp;
}
int colvo = 0;
class text_file
{
    fstream file;
    string name;

public:
    text_file(string name1)
    {
        name = name1;
        file.open(name, ios::out);
        file.close();
    }
    void fill_data(string data)
    {
        file.open(name, ios::out);
        if (!file.is_open())
        {
            cout << "Не удалось открыть файл для записи" << endl;
            return;
        }
        file << data;
        file.close();
    }
    string get_data()
    {
        file.open(name, ios::in);
        if (!file.is_open())
        {
            cout << "Не удалось открыть файл для записи" << endl;
            return "";
        }
        string data = "";
        getline(file, data);
        file.close();
        return data;
    }
};
void fill_rand(text_file *f)
{
    string data = "";
    for (int i = 0; i < colvo; i++)
    {
        data += to_string(get_rand() + 1);
    }
    f->fill_data(data);
}
void run_task(text_file *f, text_file *g)
{
    string data = f->get_data();
    string out = "";
    for (int i = 0; i < data.length(); i++)
    {
        if (data[i] % 2 == 0)
            out += data[i];
    }
    g->fill_data(out);
}
int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Введите количество чисел: ";
    cin >> colvo;
    if (colvo == 0)
    {
        cout << "Список пуст";
        return 0;
    }
    else if (colvo > 101)
    {
        cout << "Много, не хочу";
        return 0;
    }

    text_file *f = new text_file("f");
    text_file *g = new text_file("g");

    fill_rand(f);
    run_task(f, g);

    delete f;
    delete g;
    f = nullptr;
    g = nullptr;

    return 0;
}
