#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;

int point()
{
    return rand() % 20 + 200;
}
int tire()
{
    return point() + point() + point();
}
char charToMorse(string &c)
{
    map<string, char> morse_code = {
        {"PT", 'A'},
        {"TPPP", 'B'},
        {"TPTP", 'C'},
        {"TPP", 'D'},
        {"P", 'E'},
        {"PPPT", 'F'},
        {"TTP", 'G'},
        {"PPPP", 'H'},
        {"PP", 'I'},
        {"PTTT", 'J'},
        {"TPT", 'K'},
        {"PTPP", 'L'},
        {"TT", 'M'},
        {"TP", 'N'},
        {"TTT", 'O'},
        {"PTTP", 'P'},
        {"TTPT", 'Q'},
        {"PTP", 'R'},
        {"PPP", 'S'},
        {"T", 'T'},
        {"PPT", 'U'},
        {"PPPT", 'V'},
        {"PTT", 'W'},
        {"TPPT", 'X'},
        {"TPTT", 'Y'},
        {"TTPP", 'Z'},
        {"PTTTT", '1'},
        {"PPTTT", '2'},
        {"PPPTT", '3'},
        {"PPPPT", '4'},
        {"PPPPP", '5'},
        {"TPPPP", '6'},
        {"TTPPP", '7'},
        {"TTTPP", '8'},
        {"TTTTP", '9'},
        {"TTTTT", '0'},
        {"M", ' '}
    };
    if (morse_code.count(c) > 0)
        return morse_code[c];
    return '-';
}
bool validate(string row)
{
    const short size = 11;
    bool er;
    const char allowed[size] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ','};
    for (int i = 0; i < row.size(); i++)
    {
        er = true;
        for (int j = 0; j < size; j++)
        {
            if (row[i] == allowed[j])
                er = false;
        }
        if (er)
            return false;
    }
    return true;
}
int get_int_by_string(string &row, bool &ispause)
{
    string tmp = "";
    if (row[0] != '0')
        for (int i = 0; i < row.size() - 2; i++)
            tmp += row[i];
    else
    {
        ispause = true;
        for (int i = 2; i < row.size(); i++)
            tmp += row[i];
    }
    return stoi(tmp);
}
char transformate(string &row)
{
    bool ispause = false;
    int n = get_int_by_string(row, ispause);
    if (ispause)
    {
        if (159 < n && n < 241)
            return 'S'; // Между точкой или тире
        else if (479 < n && n < 721)
            return 'B'; // Между буквой
        else if (1119 < n && n < 1681)
            return 'M'; // Между словом
    }
    else
    {
        if (159 < n && n < 241)
            return 'P'; // Точка
        else if (479 < n && n < 721)
            return 'T'; // tire
    }
    return '0';
}
void runTask(string filename1)
{
    ifstream file1(filename1);
    if (!file1.is_open())
    {
        cerr << "ERROR FILE OPEN!" << endl;
        return;
    }
    char tmp;
    string row = "";
    string sym = "";
    string word = "";
    string result = "";
    string result1 = "";
    while (getline(file1, row))
    {
        tmp = transformate(row);
        if (!validate(row) || tmp == '0')
        {
            cerr << "ERROR VALIDATE " << row << endl;
            break;
        }
        result += tmp;
        if (tmp == 'B' || tmp == 'M') {
            word += charToMorse(sym);
            sym = "";
            if (tmp == 'M') {
                if (word == "COMMA")
                    word = ",";
                else if (word == "DOT" || word == "POINT")
                    word = ".";
                result1 += word + ' ';
                word = "";
            }
        }
        else if (tmp != 'S') sym += tmp;
    }
    cout << result << endl;
    cout << result1;
    file1.close();

    ofstream file2("test2.csv", ios::trunc);
    file2 << result << endl;
    file2 << result1;
    file2.close();
}

int main()
{
    // cout << endl << charToMorse(test) << endl;
    string input_file = "test.csv";
    // string output_file = "test2.csv";
    runTask(input_file);
    return 0;
}
// Международная азбука Морзе
// 1. Длина точки равна одной единице.
// 2. tire равно трем единицам.
// 3. Расстояние между частями одной и той же буквы равно одной единице.
// 4. Расстояние между буквами равно трем единицам.
// 5. Расстояние между словами равно семи единицам.

// Условия задачи:
// 1) Входные данные — CSV-файл, содержащий длительности интервалов наличия и
// отсутствия сигнала в миллисекундах вида:
// «время сигнала, 0
// 0, время паузы
// время сигнала, 0
// 0, время паузы».
// 2) средняя длительность «точки» в передачах — 200 мсек +/- 10% в зависимости от
// дежурного оператора.
// 3) знаки препинания в распечатках должны представляться знаками препинания, а не
// наборами символов.
// 4) реализацию входного буфера выполнить с применением указанного в 13 вопросе
// аттестации типа данных.
// 5) алфавит и длительности символов представлены на схеме
// Задание для пропустивших 13 вопрос в сентябрьской аттестации
// Контролируемая мафией франшиза «Пиццерия дядюшки Энцо» расширяет своё присутствие
// на новый район. В ходе принудительного закрытия точек конкурирующей франшизы были
// получены логи заказов, анализ которых показал, что суточная нагрузка по объему и ритму
// практически не меняется.
// Требуется определить минимальное количество доставщиков, необходимых для
// выполнения главного правила франшизы «Любая пицца не позже, чем через 30 минут».
// Также директор нового предприятия хотел бы найти способ получения большого
