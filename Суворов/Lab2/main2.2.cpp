#include <fstream>
#include <iostream>
#include <string>
#include <list>
using namespace std;

bool validate(string row)
{
    const short size = 10;
    bool er;
    const char allowed[size] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for (int i = 0; i < row.size(); i++)
    {
        er = true;
        if (i == 2 && row[i] == ':')
            er = false;
        else if (i == 5 && row[i] == ',')
            er = false;
        else
        {
            for (int j = 0; j < size; j++)
            {
                if (row[i] == allowed[j])
                    er = false;
            }
        }
        if (er)
            return false;
    }
    return true;
}
// class dostav {
//     short hours;
//     short minutes;
//     short time;
//     short back_hours;
//     short back_minutes;
//     bool err = false;
//     public:
//     dostav(string r) {
//         try {
//             hours = stoi(r.substr(0, 2));
//             minutes = stoi(r.substr(3, 2));
//             time = stoi(r.substr(6));

//             back_hours = hours;
//             back_minutes = minutes + (time * 2 + 10);
//             cout << back_minutes << endl;
//             if (back_minutes >= 60) {
//                 back_hours += (minutes / 60) + 1;
//                 back_minutes -= 60;
//             }
//         }
//         catch {
//             err = true;
//         }
//     }
//     string get_back() {
//         string h = to_string(back_hours);
//         string m = to_string(back_minutes);
//         if (back_minutes < 10)
//             m = "0" + m;
//         if (back_hours < 10)
//             h = "0" + h;
//         return h + ":" + m;
//     }
// };
string dostav2(string r)
{
    short hours = stoi(r.substr(0, 2));
    short minutes = stoi(r.substr(3, 2));
    short time = stoi(r.substr(6));

    short back_hours = hours;
    short back_minutes = minutes + (time * 2 + 10);
    if (back_minutes >= 60)
    {
        back_hours += (minutes / 60) + 1;
        back_minutes -= 60;
    }
    string h = to_string(back_hours);
    string m = to_string(back_minutes);
    if (back_minutes < 10)
        m = "0" + m;
    if (back_hours < 10)
        h = "0" + h;
    return h + ":" + m;
}

bool compare(string &first, string &second)
{
    short hours1 = stoi(first.substr(0, 2));
    short minutes1 = stoi(first.substr(3, 2));
    short hours2 = stoi(second.substr(0, 2));
    short minutes2 = stoi(second.substr(3, 2));
    bool biggest_or_eq = false;
    if (hours1 > hours2)
        biggest_or_eq = true;
    if (hours1 == hours2 && minutes1 > minutes2)
        biggest_or_eq = true;
    return biggest_or_eq;
}
void runTask(string filename1)
{
    ifstream file1(filename1);
    if (!file1.is_open())
    {
        cerr << "ERROR FILE OPEN!" << endl;
        return;
    }
    list<string> list{};
    int max_curiers = 0;
    int curiers = 0;
    string row;
    string time;
    string tmp;
    while (getline(file1, row))
    {
        if (!validate(row))
        {
            cerr << "ERROR VALIDATE " << endl;
            return;
        }
        time = row.substr(0, 5);
        list.remove_if([&time](string &s)
                       { return compare(time, s); });

        list.push_back(dostav2(row));
        curiers = list.size();
        if (curiers > max_curiers)
            max_curiers = curiers;
    }
    file1.close();
    cout << "Min curiers: " << max_curiers << endl;
    ofstream file2("answer22", ios::trunc);
    file2 << "Min curiers: " << max_curiers;
    file2.close();
}

int main()
{
    string input_file = "task22.csv";
    runTask(input_file);
    return 0;
}
