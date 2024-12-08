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
string charToMorse(char c)
{
    map<char, string> morse_code = {
        {'A', "PT"},
        {'B', "TPPP"},
        {'C', "TPTP"},
        {'D', "TPP"},
        {'E', "P"},
        {'F', "PPPT"},
        {'G', "TT"},
        {'H', "PPPP"},
        {'I', "PP"},
        {'J', "PTTT"},
        {'K', "TPT"},
        {'L', "PTPP"},
        {'M', "TT"},
        {'N', "TP"},
        {'O', "TTT"},
        {'P', "PTTP"},
        {'Q', "TTP"},
        {'R', "PTP"},
        {'S', "PPP"},
        {'T', "T"},
        {'U', "PPT"},
        {'V', "PPPT"},
        {'W', "PTT"},
        {'X', "TPPT"},
        {'Y', "TPPTT"},
        {'Z', "TTPP"},
        {'1', "PTTTT"},
        {'2', "PPTTT"},
        {'3', "PPPTT"},
        {'4', "PPPPT"},
        {'5', "PPPPP"},
        {'6', "TPPPP"},
        {'7', "TTPPP"},
        {'8', "TTPPP"},
        {'9', "TTTPP"},
        {'0', "TTTTP"},
        {' ', "P"}};
    c = toupper(c);
    if (morse_code.count(c) > 0)
    {
        return morse_code[c];
    }
    return "ERROR";
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
int get_int_by_string(string &row)
{
    string tmp = "";
    if (row[0] != '0')
    {
        for (int i = 0; i < row.size() - 2; i++)
            tmp += row[i];
    }
    else
    {
        for (int i = 2; i < row.size(); i++)
            tmp += row[i];
    }
    return stoi(tmp);
}
char transformate(string &row)
{
    int n = get_int_by_string(row);
    if (160 < n && n < 240)
        return 'P';
    else if (580 < n && n < 720)
        return 'T';
    else if (1120 < n && n < 1680)
        return ' ';
    else
        return 'E';
}
void runTask(string filename1)
{
    ifstream file1(filename1);
    if (!file1.is_open())
    {
        cerr << "ERROR FILE OPEN!" << endl;
        return;
    }
    string row;
    string res = "";
    while (getline(file1, row))
    {
        if (!validate(row))
        {
            // file2 << row << ",ERROR" << endl;
            // continue;
            cerr << "ERROR VALIDATE";
            break;
        }
        res += transformate(row);
    }
    cout << res;
    file1.close();
    // ofstream file2(filename2, ios::trunc);
    // file2.close();
}

int main()
{
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
