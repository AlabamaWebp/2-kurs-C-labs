#include <iostream>
#include <cmath>
using namespace std;

class Calculator1 {
protected:
    double a, b;
public:
    Calculator1() { a = 0; b = 0; }
    ~Calculator1() {}
    void inputFirst() { cout << "Введите первое число: "; cin >> a; }
    void inputSecond() { cout << "Введите второе число: "; cin >> b; }
    void output() { cout << "A: " << a << " B: " << b << endl; }
    double add() { return a + b; }
    double subtract() { return a - b; }
    virtual void showOperations() {
        cout << "1. Сложение\n2. Вычитание\n3. Выход\n";
    }
    virtual bool executeOperation(int choice) {
        switch (choice) {
            case 1: inputFirst(); inputSecond(); cout << "Сумма: " << add() << endl; return true;
            case 2: inputFirst(); inputSecond(); cout << "Разность: " << subtract() << endl; return true;
            case 3: return false;
            default: cout << "Неверный выбор, попробуйте снова.\n"; return true;
        }
    }
};

class Calculator2 : public Calculator1 {
public:
    Calculator2() : Calculator1() {}
    ~Calculator2() {}
    double multiply() { return a * b; }
    double divide() { return b != 0 ? a / b : 0; }
    void showOperations() override {
        cout << "1. Сложение\n2. Вычитание\n3. Умножение\n4. Деление\n5. Выход\n";
    }
    bool executeOperation(int choice) override {
        switch (choice) {
            case 1: case 2: Calculator1::executeOperation(choice); return true;
            case 3: inputFirst(); inputSecond(); cout << "Произведение: " << multiply() << endl; return true;
            case 4: inputFirst(); inputSecond(); cout << "Частное: " << divide() << endl; return true;
            case 5: return false;
            default: cout << "Неверный выбор, попробуйте снова.\n"; return true;
        }
    }
};

class Calculator3 : public Calculator2 {
public:
    Calculator3() : Calculator2() {}
    ~Calculator3() {}
    string toBinary(int number) {
        string result = "";
        while (number > 0) {
            result = (number % 2 == 0 ? "0" : "1") + result;
            number /= 2;
        }
        return result == "" ? "0" : result;
    }
    void outputBinary() { inputFirst(); cout << "Двоичный A: " << toBinary(static_cast<int>(a)) << endl; inputSecond(); cout << "Двоичный B: " << toBinary(static_cast<int>(b)) << endl; }
    void showOperations() override {
        cout << "1. Сложение\n2. Вычитание\n3. Умножение\n4. Деление\n5. Перевод в двоичную систему\n6. Выход\n";
    }
    bool executeOperation(int choice) override {
        switch (choice) {
            case 1: case 2: case 3: case 4: Calculator2::executeOperation(choice); return true;
            case 5: outputBinary(); return true;
            case 6: return false;
            default: cout << "Неверный выбор, попробуйте снова.\n"; return true;
        }
    }
};

void showMainMenu() {
    cout << "Выберите калькулятор:\n1. Калькулятор 1 ( + , - )\n2. Калькулятор 2 ( + , - , * , / )\n3. Калькулятор 3 ( + , - , * , / , перевод в двоичную систему)\n4. Выход\n";
}

int main() {
    int calcChoice, opChoice;
    do {
        showMainMenu();
        cin >> calcChoice;

        if (calcChoice == 4) break;

        Calculator1* calc = nullptr;
        switch (calcChoice) {
            case 1: calc = new Calculator1(); break;
            case 2: calc = new Calculator2(); break;
            case 3: calc = new Calculator3(); break;
            default: cout << "Неверный выбор, попробуйте снова.\n"; continue;
        }

        bool continueOperations = true;
        do {
            calc->showOperations();
            cin >> opChoice;
            continueOperations = calc->executeOperation(opChoice);
        } while (continueOperations);

        delete calc;

    } while (calcChoice != 4);

    return 0;
}
