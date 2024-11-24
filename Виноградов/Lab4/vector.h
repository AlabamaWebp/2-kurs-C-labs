#ifndef VECTOR_H
#define VECTOR_H

#include <string>

class Vector {
public:
    Vector(int size);
    ~Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    double& operator[](int index);
    const double& operator[](int index) const;

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(const Vector& other) const;
    Vector operator*(double scalar) const;

    std::string toString() const;

    int size;
private:
    double* elements;
};

#endif // VECTOR_H
