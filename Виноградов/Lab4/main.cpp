#include <iostream>
#include <string>
#include <cmath>

using namespace std;
// TODO MathObject
class MathObject
{
public:
    virtual MathObject *add(MathObject &) = 0;
    virtual MathObject *subtract(MathObject &) = 0;
    virtual MathObject *multiply(MathObject &) = 0;
    virtual MathObject *multiply(double) = 0;
    virtual string toString() = 0;
};
int get_rand()
{
    return rand() % 50 + 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO Matrix
class Matrix : public MathObject
{
private:
    int rows;
    int cols;
    double **data;

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols)
    {
        data = new double *[rows];
        for (int i = 0; i < rows; ++i)
        {
            data[i] = new double[cols];
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] = get_rand();
            }
        }
    }
    ~Matrix()
    {
        for (int i = 0; i < rows; ++i)
        {
            delete[] data[i];
        }
        delete[] data;
    }

    MathObject *add(MathObject &obj) override
    {
        Matrix &other = dynamic_cast<Matrix &>(obj);
        if (rows != other.rows || cols != other.cols)
        {
            cerr << "Ошибка" << endl;
        }
        Matrix *result = new Matrix(rows, cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result->data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    MathObject *subtract(MathObject &obj) override
    {
        Matrix &other = dynamic_cast<Matrix &>(obj);
        if (rows != other.rows || cols != other.cols)
        {
            cerr << "Ошибка" << endl;
        }
        Matrix *result = new Matrix(rows, cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result->data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    MathObject *multiply(MathObject &obj) override
    {
        Matrix &other = dynamic_cast<Matrix &>(obj);
        if (cols != other.rows)
        {
            cerr << "Ошибка" << endl;
        }
        Matrix *result = new Matrix(rows, other.cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < other.cols; ++j)
            {
                result->data[i][j] = 0;
                for (int k = 0; k < cols; ++k)
                {
                    result->data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    MathObject *multiply(double scalar) override
    {
        Matrix *result = new Matrix(rows, cols);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result->data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    string toString() override
    {
        string result;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result += to_string(data[i][j]) + " ";
            }
            result += "\n";
        }
        return result;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO Polynomial
class Polynomial : public MathObject
{
private:
    int degree;
    double *coefficients;

public:
    Polynomial(int degree) : degree(degree)
    {
        coefficients = new double[degree + 1];
        for (int i = 0; i <= degree; ++i)
            coefficients[i] = get_rand();
    }
    ~Polynomial()
    {
        delete[] coefficients;
    }

    MathObject *add(MathObject &obj) override
    {
        Polynomial &other = dynamic_cast<Polynomial &>(obj);
        int maxDegree = max(degree, other.degree);
        Polynomial *result = new Polynomial(maxDegree);
        for (int i = 0; i <= maxDegree; ++i)
        {
            result->coefficients[i] = (i <= degree ? coefficients[i] : 0) + (i <= other.degree ? other.coefficients[i] : 0);
        }
        return result;
    }

    MathObject *subtract(MathObject &obj) override
    {
        Polynomial &other = dynamic_cast<Polynomial &>(obj);
        int maxDegree = max(degree, other.degree);
        Polynomial *result = new Polynomial(maxDegree);
        for (int i = 0; i <= maxDegree; ++i)
        {
            result->coefficients[i] = (i <= degree ? coefficients[i] : 0) - (i <= other.degree ? other.coefficients[i] : 0);
        }
        return result;
    }

    MathObject *multiply(MathObject &obj) override
    {
        Polynomial &other = dynamic_cast<Polynomial &>(obj);
        int newDegree = degree + other.degree;
        Polynomial *result = new Polynomial(newDegree);
        for (int i = 0; i <= newDegree; ++i)
        {
            result->coefficients[i] = 0;
        }
        for (int i = 0; i <= degree; ++i)
        {
            for (int j = 0; j <= other.degree; ++j)
            {
                result->coefficients[i + j] += coefficients[i] * other.coefficients[j];
            }
        }
        return result;
    }

    MathObject *multiply(double scalar) override
    {
        Polynomial *result = new Polynomial(degree);
        for (int i = 0; i <= degree; ++i)
        {
            result->coefficients[i] = coefficients[i] * scalar;
        }
        return result;
    }

    string toString() override
    {
        string result;
        for (int i = degree; i >= 0; --i)
        {
            result += to_string(coefficients[i]) + "x^" + to_string(i) + (i > 0 ? " + " : "");
        }
        return result;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  TODO Vector
class Vector : public MathObject
{
private:
    int size;
    double *data;

public:
    Vector(int size) : size(size)
    {
        data = new double[size];
        for (int i = 0; i < size; ++i)
        {
            data[i] = get_rand();
        }
    }
    ~Vector()
    {
        delete[] data;
    }

    MathObject *add(MathObject &obj) override
    {
        Vector &other = dynamic_cast<Vector &>(obj);
        if (size != other.size)
        {
            cerr << "Ошибка: Размеры векторов должны совпадать для сложения" << endl;
            return nullptr;
        }
        Vector *result = new Vector(size);
        for (int i = 0; i < size; ++i)
        {
            result->data[i] = data[i] + other.data[i];
        }
        return result;
    }

    MathObject *subtract(MathObject &obj) override
    {
        Vector &other = dynamic_cast<Vector &>(obj);
        if (size != other.size)
        {
            cerr << "Ошибка: Размеры векторов должны совпадать для вычитания" << endl;
            return nullptr;
        }
        Vector *result = new Vector(size);
        for (int i = 0; i < size; ++i)
        {
            result->data[i] = data[i] - other.data[i];
        }
        return result;
    }

    MathObject *multiply(MathObject &obj) override
    {
        cerr << "Ошибка: Операция умножения векторов не определена" << endl;
        return nullptr;
    }

    MathObject *multiply(double scalar) override
    {
        Vector *result = new Vector(size);
        for (int i = 0; i < size; ++i)
        {
            result->data[i] = data[i] * scalar;
        }
        return result;
    }

    string toString() override
    {
        string result;
        for (int i = 0; i < size; ++i)
        {
            result += to_string(data[i]) + " ";
        }
        return result;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  TODO Fraction
class Fraction : public MathObject
{
private:
    int numerator;
    int denominator;

public:
    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
    {
        if (denominator == 0)
            cerr << "Ошибка: знаменатель не может быть равен нулю" << endl;
    }
    Fraction()
    {
        numerator = get_rand();
        denominator = get_rand();
    }

    MathObject *add(MathObject &obj) override
    {
        Fraction &other = dynamic_cast<Fraction &>(obj);
        int commonDenominator = denominator * other.denominator;
        int newNumerator = numerator * other.denominator + other.numerator * denominator;
        return new Fraction(newNumerator, commonDenominator);
    }

    MathObject *subtract(MathObject &obj) override
    {
        Fraction &other = dynamic_cast<Fraction &>(obj);
        int commonDenominator = denominator * other.denominator;
        int newNumerator = numerator * other.denominator - other.numerator * denominator;
        return new Fraction(newNumerator, commonDenominator);
    }

    MathObject *multiply(MathObject &obj) override
    {
        Fraction &other = dynamic_cast<Fraction &>(obj);
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return new Fraction(newNumerator, newDenominator);
    }

    MathObject *multiply(double scalar) override
    {
        int newNumerator = numerator * scalar;
        return new Fraction(newNumerator, denominator);
    }

    string toString() override
    {
        return to_string(numerator) + "/" + to_string(denominator);
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  TODO Complex
class Complex : public MathObject
{
private:
    double real;
    double imag;

public:
    Complex(double real1, double imag1)
    {
        real = real1;
        imag = imag1;
    }
    Complex()
    {
        real = get_rand();
        imag = get_rand();
    }

    MathObject *add(MathObject &obj) override
    {
        Complex &other = dynamic_cast<Complex &>(obj);
        return new Complex(real + other.real, imag + other.imag);
    }

    MathObject *subtract(MathObject &obj) override
    {
        Complex &other = dynamic_cast<Complex &>(obj);
        return new Complex(real - other.real, imag - other.imag);
    }

    MathObject *multiply(MathObject &obj) override
    {
        Complex &other = dynamic_cast<Complex &>(obj);
        return new Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    MathObject *multiply(double scalar) override
    {
        return new Complex(real * scalar, imag * scalar);
    }

    string toString() override
    {
        return to_string(real) + " + " + to_string(imag) + "i";
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO Shape ~
class Shape
{
public:
    virtual void move(double dx, double dy) = 0;
    virtual void rotate(double angle) = 0;
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual void display() = 0;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO Triangle
class Triangle : public Shape
{
    double base, height;
    double x, y;
    double rotation;

public:
    Triangle() : base(get_rand()), height(get_rand()), x(0), y(0), rotation(0) {}

    void move(double dx, double dy) override
    {
        x += dx;
        y += dy;
    }

    void rotate(double angle) override
    {
        rotation += angle;
    }

    double area() override
    {
        return (base * height) / 2;
    }

    double perimeter() override
    {
        double side = sqrt((base / 2) * (base / 2) + height * height);
        return base + 2 * side;
    }

    void display() override
    {
        cout << "Треугольник: База = " << base << ", Высота = " << height
             << ", x = " << x << ", y = " << y
             << ", угол = " << rotation << " градусов\n";
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO Rectangle
class Rectangle : public Shape
{
    double width, height;
    double x, y;
    double rotation;

public:
    Rectangle() : width(get_rand()), height(get_rand()), x(0), y(0), rotation(0) {}

    void move(double dx, double dy) override
    {
        x += dx;
        y += dy;
    }

    void rotate(double angle) override
    {
        rotation += angle;
    }

    double area() override
    {
        return width * height;
    }

    double perimeter() override
    {
        return 2 * (width + height);
    }

    void display() override
    {
        cout << "Прямоугольник: Ширина = " << width << ", Высота = " << height
             << ", x = " << x << ", y = " << y
             << ", угол = " << rotation << " градусов\n";
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO Rhombus
class Rhombus : public Shape
{
    double diagonal1, diagonal2;
    double x, y;
    double rotation;

public:
    Rhombus() : diagonal1(get_rand()), diagonal2(get_rand()), x(0), y(0), rotation(0) {}

    void move(double dx, double dy) override
    {
        x += dx;
        y += dy;
    }

    void rotate(double angle) override
    {
        rotation += angle;
    }

    double area() override
    {
        return (diagonal1 * diagonal2) / 2;
    }

    double perimeter() override
    {
        double side = sqrt((diagonal1 / 2) * (diagonal1 / 2) + (diagonal2 / 2) * (diagonal2 / 2));
        return 4 * side;
    }

    void display() override
    {
        cout << "Ромб: 1 диагональ = " << diagonal1 << ", 2 диагональ = " << diagonal2
             << ", x = " << x << ", y = " << y
             << ", угол = " << rotation << " градусов\n";
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO Ellipse
class Ellipse : public Shape
{
public:
    Ellipse() : majorAxis(get_rand()), minorAxis(get_rand()), x(0), y(0), rotation(0) {}

    void move(double dx, double dy) override
    {
        x += dx;
        y += dy;
    }

    void rotate(double angle) override
    {
        rotation += angle;
    }

    double area() override
    {
        return M_PI * majorAxis * minorAxis;
    }

    double perimeter() override
    {
        return M_PI * (3 * (majorAxis + minorAxis) - sqrt((3 * majorAxis + minorAxis) * (majorAxis + 3 * minorAxis)));
    }

    void display() override
    {
        cout << "Эллипс: главная ось = " << majorAxis << ", вторая ось = " << minorAxis
             << ", x = " << x << ", y = " << y
             << ", угол = " << rotation << " градусов\n";
    }

private:
    double majorAxis, minorAxis;
    double x, y;
    double rotation;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO Trapezoid
class Trapezoid : public Shape
{
public:
    Trapezoid() : base1(get_rand()), base2(get_rand()), height(get_rand()), side1(get_rand()), side2(get_rand()), x(0), y(0), rotation(0) {}

    void move(double dx, double dy) override
    {
        x += dx;
        y += dy;
    }

    void rotate(double angle) override
    {
        rotation += angle;
    }

    double area() override
    {
        return (base1 + base2) * height / 2;
    }

    double perimeter() override
    {
        return base1 + base2 + side1 + side2;
    }

    void display() override
    {
        cout << "Трапеция: верхняя основа = " << base1 << ", нижняя основа = " << base2
             << ", Высота = " << height << ", левая сторона = " << side1 << ", правая сторона = " << side2
             << ", x = " << x << ", y = " << y
             << ", угол = " << rotation << " градусов\n";
    }

private:
    double base1, base2, height, side1, side2;
    double x, y;
    double rotation;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO MENUS
void showObjectMenu(int choice)
{
    MathObject *one;
    MathObject *two;
    MathObject *tmp;
    int choice55;
    switch (choice)
    {
    case 1:
        one = new Matrix(3, 3);
        two = new Matrix(3, 3);
        break;
    case 2:
        one = new Polynomial(3);
        two = new Polynomial(3);
        break;
    case 3:
        one = new Vector(3);
        two = new Vector(3);
        break;
    case 4:
        one = new Fraction();
        two = new Fraction();
        break;
    case 5:
        one = new Complex();
        two = new Complex();
        break;
    default:
        break;
    }
    cout << "Объект 1. " << endl
         << one->toString() << endl
         << "Объект 2. " << endl
         << two->toString() << endl;
    while (true)
    {
        cout << "Выберите операцию:\n";
        cout << "1. Сложение\n";
        cout << "2. Вычитание\n";
        cout << "3. Умножение на объект\n";
        cout << "4. Умножение на число\n";
        cout << "5. Выход\n";
        cout << "Ваш выбор: ";
        int operationChoice;
        cin >> operationChoice;
        tmp = nullptr;
        switch (operationChoice)
        {
        case 1:
            tmp = one->add(*two);
            break;
        case 2:
            tmp = one->subtract(*two);
            break;
        case 3:
            tmp = one->multiply(*two);
            break;
        case 4:
            cout << "Введите число на которое умножить объект: ";
            cin >> choice55;
            tmp = one->multiply(choice55);
            break;
        case 5:
            return;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
        if (tmp != nullptr)
        {
            cout << tmp->toString() << endl;
        }
    }
}
void showMathObjectMenu()
{
    int choice;
    while (true)
    {
        cout << "Выберите математический объект:\n";
        cout << "1. Матрица\n";
        cout << "2. Полином\n";
        cout << "3. Вектор\n";
        cout << "4. Дробь\n";
        cout << "5. Комплексное число\n";
        cout << "6. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice >= 1 && choice <= 5)
        {
            showObjectMenu(choice);
        }
        else if (choice == 6)
        {
            return;
        }
        else
        {
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }
}
void showFigureMenu(int choice)
{
    Shape *one;
    // int choice55;
    switch (choice)
    {
    case 1:
        one = new Triangle();
        break;
    case 2:
        one = new Rectangle();
        break;
    case 3:
        one = new Rhombus();
        break;
    case 4:
        one = new Ellipse();
        break;
    case 5:
        one = new Trapezoid();
        break;
    default:
        break;
    }
    one->display();
    while (true)
    {
        cout << "Выберите операцию:\n";
        cout << "1. Случайное перемещение\n";
        cout << "2. Случайный поворот\n";
        cout << "3. Нахождение площади\n";
        cout << "4. Нахождение периметра\n";
        cout << "5. Выход\n";
        cout << "Ваш выбор: ";
        int operationChoice;
        cin >> operationChoice;
        switch (operationChoice)
        {
        case 1:

            one->move(get_rand(), get_rand());
            one->display();
            break;
        case 2:
            one->rotate(get_rand());
            one->display();
            break;
        case 3:
            cout << "периметр = " << one->perimeter() << endl;
            break;
        case 4:
            cout << "площадь = " << one->area() << endl;
            break;
        case 5:
            return;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }
}
void showFigures()
{
    int choice;
    while (true)
    {
        cout << "Выберите фигуру:\n";
        cout << "1. Треугольник\n";
        cout << "2. Прямоугольник\n";
        cout << "3. Ромб\n";
        cout << "4. Эллипс\n";
        cout << "5. Трапеция\n";
        cout << "6. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        if (choice >= 1 && choice <= 5)
            showFigureMenu(choice);
        else if (choice == 6)
            return;
        else
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
    }
}
void menu()
{
    int choice;
    while (true)
    {
        cout << "Выберите действие:\n";
        cout << "1. Математические объекты\n";
        cout << "2. Геометрические фигуры\n";
        cout << "3. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1)
            showMathObjectMenu();
        else if (choice == 2)
            showFigures();
        else if (choice == 3)
        {
            cout << "Выход...\n";
            return;
        }
        else
        {
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }
}
int main()
{
    menu();
    return 0;
}