
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void sort(int *mas, int &size)
{
    int min;
    int id;
    for (int i = 0; i < size; i++)
    {
        min = mas[i];
        id = i;
        for (int j = i; j < size; j++)
            if (min > mas[j]) {
                min = mas[j];
                id = j;
            }
        if (id != i)
            swap(mas[i], mas[id]);
        for (int i = 0; i < size; i++)
        {
            cout << mas[i] << " ";
        }
            
        cout <<  endl;
    }
}

void transformate(string &row, int *mas, int &size)
{
    size = 1;
    int last_index = row.find(",");
    int tmp_i;
    mas[0] = stoi(row.substr(0, last_index));
    while (last_index != -1)
    {
        tmp_i = row.find(",", last_index + 1);
        if (tmp_i == -1)
            mas[size] = stoi(row.substr(last_index + 1));
        else
            mas[size] = stoi(row.substr(last_index + 1, tmp_i - last_index - 1));
        last_index = tmp_i;
        size++;
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
    int size;
    int *mas = new int();
    transformate(row, mas, size);
    file1.close();
    sort(mas, size);
    ofstream file2(filename2, ios::trunc);
    for (int i = 0; i < size-1; i++)
        file2 << mas[i] << ",";
    file2 << mas[size-1];
    file2.close();
}

int main()
{
    string input_file = "task32.csv";
    string output_file = "result32.csv";
    runTask(input_file, output_file);
    return 0;
}
