#include "vector.h"
#include <iostream>

Vector::Vector(int size) : size(size) {
    elements = new double[size];
    for (int i = 0; i < size; ++i) {
        elements[i] = 0.0;
    }
}

Vector::~Vector() {
    delete[] elements;
}

Vector::Vector(const Vector& other) : size(other.size) {
    elements = new double[size];
    for (int i = 0; i < size; ++i) {
        elements[i] = other.elements[i];
    }
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) return *this;

    delete[] elements;

    size = other.size;
    elements = new double[size];
    for (int i = 0; i < size; ++i) {
        elements[i] = other.elements[i];
    }
    return *this;
}

double& Vector::operator[](int index) {
    return elements[index];
}

const double& Vector::operator[](int index) const {
    return elements[index];
}

Vector Vector::operator+(const Vector& other) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.elements[i] = elements[i] + other.elements[i];
    }
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.elements[i] = elements[i] - other.elements[i];
    }
    return result;
}

Vector Vector::operator*(const Vector& other) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.elements[i] = elements[i] * other.elements[i];
    }
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(size);
    for (int i = 0; i < size; ++i) {
        result.elements[i] = elements[i] * scalar;
    }
    return result;
}

std::string Vector::toString() const {
    std::string result;
    for (int i = 0; i < size; ++i) {
        result += std::to_string(elements[i]) + " ";
    }
    result += "\n";
    return result;
}
