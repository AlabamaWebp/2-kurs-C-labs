#include <iostream>
using namespace std;
int main()
{
    const int size = 4;
    int a[size][size];
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            a[i][j] = rand() % 101;
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
