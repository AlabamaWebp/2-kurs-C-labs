class Matrix {
private:
    int rows;
    int cols;
    int** data;
    void deleteData();
public:
    Matrix(int rows, int cols);
    ~Matrix();

    void transpose();
    void rotate();
    void sortRows();
    void reverseColumns();
    void print();
};