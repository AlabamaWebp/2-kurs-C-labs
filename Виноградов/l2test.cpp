#include <iostream>
#include <cmath>

using namespace std;

class Pentagon {
private:
    double side;
    int number;

public:
    Pentagon() { side = 0; number = 0; }
    void inputSide(int num) {
        number = num;
        cout << "Введите длину стороны для пятиугольника " << number << ": ";
        cin >> side;
    }
    void printResults() {
        cout << "Пятиугольник " << number << " - Сторона: " << side << " - Площадь: " << getArea() << " - Периметр: " << getPerimeter() << endl;
    }
    double getArea() {
        return (sqrt(5 * (5 + 2 * sqrt(5))) * side * side) / 4;
    }
    double getPerimeter() {
        return 5 * side;
    }
};

void inputPentagons(Pentagon* pentagons, int n) {
    for (int i = 0; i < n; i++) {
        pentagons[i].inputSide(i + 1);
    }
}

void findMaxAreaPentagons(Pentagon* pentagons, int n, Pentagon* maxAreaPentagons, int &maxCount) {
    double maxArea = pentagons[0].getArea();
    maxAreaPentagons[0] = pentagons[0];
    maxCount = 1;

    for (int i = 1; i < n; i++) {
        double area = pentagons[i].getArea();
        if (area > maxArea) {
            maxArea = area;
            maxAreaPentagons[0] = pentagons[i];
            maxCount = 1;
        } else if (area == maxArea) {
            maxAreaPentagons[maxCount++] = pentagons[i];
        }
    }
}

void findMaxPerimeterPentagons(Pentagon* pentagons, int n, Pentagon* maxPerimeterPentagons, int &maxCount) {
    double maxPerimeter = pentagons[0].getPerimeter();
    maxPerimeterPentagons[0] = pentagons[0];
    maxCount = 1;

    for (int i = 1; i < n; i++) {
        double perimeter = pentagons[i].getPerimeter();
        if (perimeter > maxPerimeter) {
            maxPerimeter = perimeter;
            maxPerimeterPentagons[0] = pentagons[i];
            maxCount = 1;
        } else if (perimeter == maxPerimeter) {
            maxPerimeterPentagons[maxCount++] = pentagons[i];
        }
    }
}

void printResults(Pentagon* pentagons, int count) {
    for (int i = 0; i < count; i++) {
        pentagons[i].printResults();
    }
}

int main() {
    int n;
    cout << "Введите количество пятиугольников: ";
    cin >> n;
    Pentagon* pentagons = new Pentagon[n];
    inputPentagons(pentagons, n);

    Pentagon* maxAreaPentagons = new Pentagon[n];
    Pentagon* maxPerimeterPentagons = new Pentagon[n];
    int maxAreaCount, maxPerimeterCount;

    findMaxAreaPentagons(pentagons, n, maxAreaPentagons, maxAreaCount);
    findMaxPerimeterPentagons(pentagons, n, maxPerimeterPentagons, maxPerimeterCount);

    cout << "Максимальная площадь:\n";
    printResults(maxAreaPentagons, maxAreaCount);
    cout << "Максимальный периметр:\n";
    printResults(maxPerimeterPentagons, maxPerimeterCount);

    delete[] pentagons;
    delete[] maxAreaPentagons;
    delete[] maxPerimeterPentagons;
    
    pentagons = nullptr;
    maxAreaPentagons = nullptr;
    maxPerimeterPentagons = nullptr;


    return 0;
}
