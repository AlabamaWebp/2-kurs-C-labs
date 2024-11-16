#include <fstream>
#include <iostream>
#include <string>

using namespace std;
bool validate(string row)
{
    if (row.size() < 2 || row.size() > 16) return false;
    for (int i = 0; i < row.size(); i++)
    {
        if (row[i] != '0'&& row[i] != '1')
            return false;
    }
    return true;
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
            for (int i = 1; i < obr.size(); i++)
            {
                if (obr[i] == '0')
                    obr[i] = '1';
                else
                    obr[i] = '0';
            }
            dop = obr;
            for (int i = obr.size(); i > 1; i--)
            {
                if (obr[i] == '0')
                {
                    dop[i] = '1';
                    break;
                }
                else
                    dop[i] = '0';
            }
        }
        else
            dop = row;
        file2 << row << ","<< obr << "," << dop << endl;
    }
    file1.close();
    file2.close();
}

int main()
{
    string input_file = "task1.csv";
    string output_file = "result2_eliseev_3.csv";
    runTask(input_file, output_file);
    return 0;
}

