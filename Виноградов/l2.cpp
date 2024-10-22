#include <iostream>
#include <cmath>
using namespace std;

class Pentagon {
private:
    double side;

public:
    Pentagon() { side = 0; }
    void inputSide() { 
        cout << "Введите длину стороны: "; 
        cin >> side; 
    }
    void printResults() const {
        cout << "Сторона: " << side << " - Площадь: " << getArea() << " - Периметр: " << getPerimeter() << endl;
    }
    double getArea() const {
        return (sqrt(5 * (5 + 2 * sqrt(5))) * side * side) / 4;
    }
    double getPerimeter() const {
        return 5 * side;
    }
};

void inputPentagons(Pentagon* pentagons, int n) {
    for(int i = 0; i < n; i++) {
        cout << "Пятиугольник " << i+1 << ". ";
        pentagons[i].inputSide();
    }
}

Pentagon findMaxAreaPentagon(const Pentagon* pentagons, int n) {
    Pentagon maxAreaPentagon = pentagons[0];
    for(int i = 1; i < n; i++) if(pentagons[i].getArea() > maxAreaPentagon.getArea()) maxAreaPentagon = pentagons[i];
    return maxAreaPentagon;
}

Pentagon findMaxPerimeterPentagon(const Pentagon* pentagons, int n) {
    Pentagon maxPerimeterPentagon = pentagons[0];
    for(int i = 1; i < n; i++) if(pentagons[i].getPerimeter() > maxPerimeterPentagon.getPerimeter()) maxPerimeterPentagon = pentagons[i];
    return maxPerimeterPentagon;
}
// 3. Определить класс, описывающий правильный пятиугольник.
//  Запрограммировать класс, позволяющий создать несколько таких объектов,
//  найти большие по площади и периметру, из этих объектов.
void printResults(const Pentagon& maxAreaPentagon, const Pentagon& maxPerimeterPentagon) {
    cout << "Максимальная площадь: ";
    maxAreaPentagon.printResults();
    cout << "Максимальный периметр: ";
    maxPerimeterPentagon.printResults();
}

int main() {
    int n;
    cout << "Введите количество пятиугольников: ";
    cin >> n;
    Pentagon* pentagons = new Pentagon[n];
    inputPentagons(pentagons, n);
    printResults(findMaxAreaPentagon(pentagons, n), findMaxPerimeterPentagon(pentagons, n));
    delete[] pentagons;
    return 0;
}
