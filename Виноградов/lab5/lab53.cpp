#include <iostream>
#include <cmath>
using namespace std;

class Triangle {
private:
    double a, b, c;

    void validateSides() {
        if (a <= 0 || b <= 0 || c <= 0) {
            cerr << "Ошибка: сторона не может быть нулевой или отрицательной" << endl;
            throw invalid_argument("Стороны должны быть положительными числами");
        }
        if (a + b <= c || a + c <= b || b + c <= a) {
            cerr << "Ошибка: невозможно создать треугольник с такими сторонами" << endl;
            throw invalid_argument("Несуществующий треугольник");
        }
    }

public:
    Triangle(double sideA, double sideB, double sideC) : a(sideA), b(sideB), c(sideC) {
        validateSides();
    }

    double area() {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    string toString() {
        return "Triangle(" + to_string(a) + ", " + to_string(b) + ", " + to_string(c) + ")";
    }

    Triangle fromString(const string& str) {
        double sideA, sideB, sideC;
        if (sscanf(str.c_str(), "Triangle(%lf, %lf, %lf)", &sideA, &sideB, &sideC) != 3) {
            cerr << "Ошибка: неправильный формат строки" << endl;
            throw invalid_argument("Неправильный формат строки");
        }
        return Triangle(sideA, sideB, sideC);
    }
};

void printMenu() {
    cout << "Выберите действие:\n";
    cout << "1. Создать треугольник\n";
    cout << "2. Показать информацию о треугольнике\n";
    cout << "3. Вычислить площадь треугольника\n";
    cout << "4. Создать треугольник из строки\n";
    cout << "5. Выйти\n";
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
                cout << "Введите стороны треугольника (a, b, c): ";
                cin >> a >> b >> c;
                try {
                    delete t;
                    t = new Triangle(a, b, c);
                    cout << "Треугольник создан: " << t->toString() << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                    t = nullptr;
                }
                break;
            case 2:
                if (t) {
                    cout << "Информация о треугольнике: " << t->toString() << endl;
                } else {
                    cerr << "Треугольник не создан\n";
                }
                break;
            case 3:
                if (t) {
                    cout << "Площадь треугольника: " << t->area() << endl;
                } else {
                    cerr << "Треугольник не создан\n";
                }
                break;
            case 4:
                cout << "Введите строку для создания треугольника (например, Triangle(3, 4, 5)): ";
                cin.ignore();
                getline(cin, str);
                try {
                    delete t;
                    t = Triangle::fromString(str);
                    cout << "Треугольник создан из строки: " << t->toString() << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                    t = nullptr;
                }
                break;
            case 5:
                delete t;
                return 0;
            default:
                cerr << "Ошибка: неверный выбор\n";
                break;
        }
    }
    return 0;
}
