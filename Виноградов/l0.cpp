/******************************************************************************
6. Дан список из n записей о студентах. Каждая запись содержит следующие поля: фамилия, имя, отчество, факультет, курс, группа, средняя успеваемость.
Вывести список студентов указанного факультета, курса и группы.
*******************************************************************************/

#include <iostream>
using namespace std;
const int razmer = 2;
const string f1[] = {"Пуртов", "Елисеев"};
const string i1[] = {"Дмитрий", "Илюша"};
const string o1[] = {"Андреевич", "Павлович"};
const string faq1[] = {"ФМФ", "ФИЯ"};
const string group1[razmer][razmer] = {{"СИ-15", "ОС-17"}, {"СИ-25", "ОС-27"}};

int get_rand()
{
    int tmp = rand() % razmer;
    return tmp;
}

class row1
{
    string f, i, o, faq, group;
    float usp;
    int course, faq_id, group_id;

public:
    void show()
    {
        cout << f << ", ";
        cout << i << ", ";
        cout << o << ", ";
        cout << faq << ", ";
        cout << group << ", ";
        cout << course << ", ";
        cout << usp << endl;
    }
    row1()
    {
        f = f1[get_rand()];
        i = i1[get_rand()];
        o = o1[get_rand()];
        faq_id = get_rand();
        faq = faq1[faq_id];
        course = rand() % 2 + 1;
        group_id = get_rand();
        group = group1[this->course - 1][group_id];
        usp = (rand() % 29) / 10. + 2;
    }
    bool find(int f, int c, int g)
    {

        return (this->faq_id == f && this->course == c && this->group_id == g);
    }
};
int colvo = 0;
void fill(row1 **mas)
{
    for (int i = 0; i < colvo; i++)
        mas[i] = new row1;
}
void show(row1 **mas, int count)
{
    for (int i = 0; i < count; i++)
        mas[i]->show();
}

/******************************************************************************
6. Дан список из n записей о студентах. Каждая запись содержит следующие поля: фамилия, имя, отчество, факультет, курс, группа, средняя успеваемость.
Вывести список студентов указанного факультета, курса и группы.
*******************************************************************************/
void getInputMas(string s, int &i, const string *m)
{
    for (int i = 0; i < razmer; i++)
        cout << i + 1 << ". " << m[i] << endl;
    cout << s + ": ";
    cin >> i;
    i--;
}
void getInput(string s, int &i)
{
    cout << s + ": ";
    cin >> i;
}

void find(row1 **MainRows)
{
    int f, c, g;
    getInputMas("Укажите факултет", f, faq1);
    getInput("Укажите курс", c);
    getInputMas("Укажите группу", g, group1[c - 1]);
    row1 **result = new row1 *;
    int size = 0;
    for (int i = 0; i < colvo; i++)
    {
        if (MainRows[i]->find(f, c, g))
        {
            result[size] = MainRows[i];
            size++;
        }
    }
    show(result, size);
    delete[] result;

    for (int i = 0; i < colvo; i++)
    {
        delete MainRows[i];
    }
    delete[] MainRows;
    MainRows = nullptr;
    result = nullptr;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    // cout.imbue(locale(""));
    cout << "Введите количество записей: ";
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

    row1 **MainRows = new row1 *;
    fill(MainRows);
    show(MainRows, colvo);
    find(MainRows);

    return 0;
}
