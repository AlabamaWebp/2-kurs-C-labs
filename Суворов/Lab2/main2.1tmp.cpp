#include <fstream>
#include <iostream>
#include <string>
#include <map>
using namespace std;

// ofstream file("test.csv");
int point()
{
    return rand() % 80 + 160;
}
// int point(bool son = false)
// {
//     if (!son)
//     {
//         file << point2() << ",0" << endl;
//         file << "0," << point2() << endl;
//     }
//     return rand() % 20 + 200;
// }
int tire()
{
    return point() + point() + point();
}
int mesh_bukvi()
{
    return point() + point() + point() + point() + point() + point() + point();
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
        {'G', "TTP"},
        {'H', "PPPP"},
        {'I', "PP"},
        {'J', "PTTT"},
        {'K', "TPT"},
        {'L', "PTPP"},
        {'M', "TT"},
        {'N', "TP"},
        {'O', "TTT"},
        {'P', "PTTP"},
        {'Q', "TTPT"},
        {'R', "PTP"},
        {'S', "PPP"},
        {'T', "T"},
        {'U', "PPT"},
        {'V', "PPPT"},
        {'W', "PTT"},
        {'X', "TPPT"},
        {'Y', "TPTT"},
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
        {' ', "M"}};
        // twenty three point five centigrade comma clear
    c = toupper(c);
    if (morse_code.count(c) > 0)
    {
        return morse_code[c];
    }
    return "ERROR";
}
int convert(char c) {
    if (c == 'P') {
        return point();
    }
    else if (c == 'T') {
        return tire();
    }
    return mesh_bukvi(); 
}
void generate_by_string(string str)
{
    ofstream file("task21.csv", ios::trunc);
    if (!file.is_open())
    {
        cerr << "ERROR FILE OPEN111!" << endl;
        return;
    }
    const int size = str.size() - 1;
    int size_tmp;
    string tmp;
    for (int i = 0; i < size; i++)
    {
        if (str[i] == ' ') continue;   
        tmp = charToMorse(str[i]);
        size_tmp = tmp.size() - 1;
        for (int j = 0; j < size_tmp; j++)
        {
            file << convert(tmp[j]) << ",0" << endl;
            file << "0," << point() << endl;
        } // все кроме последней
        // последнюю отдельно для определения паузы 
        file << convert(tmp[size_tmp]) << ",0" << endl;
        file << "0," << ((str[i + 1] != ' ') ? tire() : mesh_bukvi()) << endl;
        
    }
    // file << convert(tmp[size]) << ",0" << endl;
    file.close();
}

int main()
{
    string str = "twenty three point five centigrade comma clear 55 comma 3 ";
    generate_by_string(str);
    return 0;
}
// Международная азбука Морзе
// 1. Длина точки равна одной единице.
// 2. тире равно трем единицам.
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
