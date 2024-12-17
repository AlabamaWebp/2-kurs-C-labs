#include <iostream>
#include <cmath>
using namespace std;

class Triangle {
private:
    double a, b, c;

    void validateSides() {
        if (a <= 0 || b <= 0 || c <= 0) {
            cerr << "Ошибка: сторона должна быть > 0" << endl;
            throw invalid_argument("Стороны должны быть положительными числами");
        }
        if (a + b <= c || a + c <= b || b + c <= a) {
            cerr << "Ошибка: невозможно создать треугольник с такими сторонами" << endl;
            throw invalid_argument("Несуществующий треугольник");
        }
    }

public:

    operator double() {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    operator string() {
        return "Треугольник со сторонами " + to_string(a) + ", " + to_string(b) + ", " + to_string(c);
    }

    Triangle(string& str) {
        cout << str << endl;
        if (sscanf(str.c_str(), "%lf,%lf,%lf", &a, &b, &c) != 3) {
            cerr << "Ошибка: неправильный формат строки" << endl;
            throw invalid_argument("Неправильный формат строки");
        }
        validateSides();
    }
};

void printMenu() {
    cout << "Выберите действие:\n";
    cout << "1. Создать треугольник из строки\n";
    cout << "2. Показать информацию о треугольнике\n";
    cout << "4. Вычислить площадь треугольника\n";
    cout << "0. Выйти\n";
}

int main() {
    Triangle* t = nullptr;
    int choice;
    double a, b, c;
    string str;

    while (true) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите строку для создания треугольника (например, 3,4,5): " << endl;
                cin.ignore();
                getline(cin, str);
                try {
                    delete t;
                    t = new Triangle(str);
                    cout << "Треугольник создан из строки: " << (string)(*t) << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                    t = nullptr;
                }
                break;
            case 2:
                if (t) {
                    cout << "Информация о треугольнике: " << (string)*t << endl;
                } else {
                    cerr << "Треугольник не создан\n";
                }
                break;
            case 3:
                if (t) {
                    cout << "Площадь треугольника: " << (double)*t << endl;
                } else {
                    cerr << "Треугольник не создан\n";
                }
                break;
            case 0:
                delete t;
                return 0;
            default:
                cerr << "Ошибка: неверный выбор\n";
                break;
        }
    }
    return 0;
}
