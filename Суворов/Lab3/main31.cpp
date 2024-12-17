
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
float transformate(string &row)
{
    float tmp;
    float min;
    int last_index = 0;
    last_index = row.find(",");
    min = stof(row.substr(0, last_index));
    for (int i = 0; i < row.size(); i++)
    {
        last_index = row.find(",", last_index);
    }
}
void runTask(string filename1, string filename2)
{
    ifstream file1(filename1);
    if (!file1.is_open() || !file2.is_open())
    {
        cerr << "ERROR FILE OPEN!" << endl;
        return;
    }
    string row;
    getline(file1, row);
    transformate(row);
    file1.close();

    ofstream file2(filename2, ios::trunc);
    file2.close();
}

int main()
{
    string input_file = "task31.csv";
    string output_file = "result31.csv";
    runTask(input_file, output_file);
    return 0;
}
