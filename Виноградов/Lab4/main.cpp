#include <iostream>
#include <string>

using namespace std;

class MathObject
{
public:
    virtual MathObject *add(MathObject &) = 0;
    virtual MathObject *subtract(MathObject &) = 0;
    virtual MathObject *multiply(MathObject &) = 0;
    virtual MathObject *multiply(double) = 0;
    virtual string toString() = 0;
    virtual ~MathObject() = default;
};
int get_rand()
{
    return rand() % 51;
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

    // int gcd(int a, int b)
    // {
    //     return b == 0 ? a : gcd(b, a % b);
    // }

    // void reduce()
    // {
    //     int divisor = gcd(numerator, denominator);
    //     numerator /= divisor;
    //     denominator /= divisor;
    // }

public:
    Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
    {
        if (denominator == 0)
            cerr << "Ошибка: знаменатель не может быть равен нулю" << endl;
        // reduce();
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

void showMathObjectMenu() {
    int choice;
    while (true) {
        cout << "Выберите математический объект:\n";
        cout << "1. Матрица\n";
        cout << "2. Полином\n";
        cout << "3. Вектор\n";
        cout << "4. Дробь\n";
        cout << "5. Комплексное число\n";
        cout << "6. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            showObjectMenu(choice);
        } else if (choice == 6) {
            return;
        } else {
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }
}

void showObjectMenu(int choice) {
    while (true) {
        cout << "Выберите операцию:\n";
        cout << "1. Сложение\n";
        cout << "2. Вычитание\n";
        cout << "3. Умножение на объект\n";
        cout << "4. Умножение на число\n";
        cout << "5. Показать объект\n";
        cout << "6. Выход\n";
        cout << "Ваш выбор: ";
        int operationChoice;
        cin >> operationChoice;

        switch (operationChoice) {
        case 1:
            // Логика сложения
            cout << "Выполняется сложение...\n";
            break;
        case 2:
            // Логика вычитания
            cout << "Выполняется вычитание...\n";
            break;
        case 3:
            // Логика умножения на объект
            cout << "Выполняется умножение на объект...\n";
            break;
        case 4:
            // Логика умножения на число
            cout << "Выполняется умножение на число...\n";
            break;
        case 5:
            // Логика отображения объекта
            cout << "Отображение объекта...\n";
            break;
        case 6:
            return;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }
}
void menu() {
    int choice;
    while (true) {
        cout << "Выберите действие:\n";
        cout << "1. Математические объекты\n";
        cout << "2. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 1) {
            showMathObjectMenu();
        } else if (choice == 2) {
            cout << "Выход...\n";
            return;
        } else {
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }
}
int main() {
    menu();
    return 0;
}
