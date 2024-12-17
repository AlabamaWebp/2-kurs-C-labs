
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
void transformate(string &row, float &min)
{
    float tmp;
    int last_index = 0;
    int tmp_i;
    last_index = row.find(",");
    min = stof(row.substr(0, last_index));
    while (last_index != -1)
    {
        tmp_i = row.find(",", last_index + 1);
        if (tmp_i == -1)
            tmp = stof(row.substr(last_index + 1));
        else
            tmp = stof(row.substr(last_index + 1, tmp_i - last_index - 1));
        if (tmp < min)
            min = tmp;
        last_index = tmp_i;
    }
}
void runTask(string filename1, string filename2)
{
    ifstream file1(filename1);
    if (!file1.is_open())
    {
        cerr << "ERROR FILE OPEN!" << endl;
        return;
    }
    string row;
    getline(file1, row);
    float min;
    transformate(row, min);
    file1.close();

    ofstream file2(filename2, ios::trunc);
    file2 << min;
    file2.close();
}

int main()
{
    string input_file = "task31.csv";
    string output_file = "result31.csv";
    runTask(input_file, output_file);
    return 0;
}
