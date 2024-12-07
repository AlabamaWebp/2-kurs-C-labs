#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;

int point() {
    return rand() % 20 + 200;
}
int tire() {
    return point() + point() + point();
}
string charToMorse(char c) {
    // Словарь соответствий символов и кода Морзе
    map<char, string> morse_code = {
        {'A', point() + tire()},
        {'B', tire() + point() + point() + point()},
        {'C', tire() + point() + tire() + point()},
        {'D', tire() + point() + point()},
        {'E', point()},
        {'F', point() + point() + tire() + point()},
        {'G', tire() + tire() + point()},
        {'H', point() + point() + point() + point()},
        {'I', point() + point()},
        {'J', point() + tire() + tire() + tire()},
        {'K', tire() + point() + tire()},
        {'L', point() + tire() + point() + point()},
        {'M', tire() + tire()},
        {'N', tire() + point()},
        {'O', tire() + tire() + tire()},
        {'P', point() + tire() + tire() + point()},
        {'Q', tire() + tire() + point() + tire()},
        {'R', point() + tire() + point()},
        {'S', point() + point() + point()},
        {'T', tire()},
        {'U', point() + point() + tire()},
        {'V', point() + point() + point() + tire()},
        {'W', point() + tire() + tire()},
        {'X', tire() + point() + point() + tire()},
        {'Y', tire() + point() + tire() + tire()},
        {'Z', tire() + tire() + point() + point()},
        {'1', point() + tire() + tire() + tire() + tire()},
        {'2', point() + point() + tire() + tire() + tire() + tire()},
        {'3', point() + point() + point() + tire() + tire() + tire() + tire()},
        {'4', point() + point() + point() + point() + tire() + tire() + tire() + tire() + tire()},
        {'5', point() + point() + point() + point() + point()},
        {'6', tire() + point() + point() + point() + point()},
        {'7', tire() + tire() + point() + point() + point()},
        {'8', tire() + tire() + tire() + point() + point()},
        {'9', tire() + tire() + tire() + tire() + point()},
        {'0', tire() + tire() + tire() + tire() + tire()}
    };
    c = toupper(c);
    if (morse_code.find(c) != morse_code.end()) {
        return morse_code[c];
    }
    return "";
}
bool validate(string row)
{
    const short size = 12;
    const char allowed[size] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ',', '.' };
    for (int i = 0; i < row.size(); i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (row[i] != allowed[j])
                return false;
        }
    }
    return true;
}
void generate_by_string(string str) {
    ofstream file("test.csv");
    for (int i = 0; i < str.size(); i++)
    {
        /* code */
    }
}
string char_to_morse(char sym) {

    return "";
}
void transformate(string &row, string &obr, string &dop)
{

}
void runTask(string filename1, string filename2)
{
    ifstream file1(filename1);
    ofstream file2(filename2, ios::trunc);
    if (!file1.is_open() || !file2.is_open())
    {
        cerr << "ERROR FILE OPEN!" << endl;
        return;
    }
    string row;
    string obr;
    string dop;
    while (getline(file1, row))
    {
        if (!validate(row))
        {
            file2 << row << ",ERROR" << endl;
            continue;
        }
        obr = row;
        if (row[0] == '1')
        {
            transformate(row, obr, dop);
        }
        else
            dop = row;
        file2 << row << "," << obr << "," << dop << endl;
    }
    file1.close();
    file2.close();
}

int main()
{
    string input_file = "si25_eliseev_task1.csv";
    string output_file = "result2_eliseev_3.csv";
    runTask(input_file, output_file);
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
