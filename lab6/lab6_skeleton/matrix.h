#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using namespace std;

template <typename T>
class Matrix {
private:
    size_t rows, cols;
    T* data;
    T dummy; // Dummy value for out-of-bounds access


public:

    // Parameterized constructor for creating a matrix with given dimensions
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols), data(new T[rows * cols]), dummy(T()){}


    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), data(new T[other.rows * other.cols]) {
        for (size_t i = 0; i < rows * cols; ++i) {
            data[i] = other.data[i];
        }
    }

    ~Matrix() {
        delete[] data;
    }

    // TODO1: Implement the assignment operator for the Matrix class
    // This operator should replace the current Matrix's contents with the contents of another Matrix.
    // It needs to safely handle self-assignment, release the current memory, and allocate new memory to hold the copied data.

    Matrix& operator=(const Matrix& other) {
        rows = other.rows; cols = other.cols;
        delete [] data;
        data = new T[rows * cols];
        for (int i = 0; i < rows * cols; ++i){
            data[i] = other.data[i];
        }
        return *this;
    }

    T& operator()(size_t row, size_t col) {
        if (row >= rows || col >= cols) {
            cerr << "Matrix subscript out of bounds" << endl;
            return dummy;
        }
        return data[row * cols + col];
    }

    const T& operator()(size_t row, size_t col) const {
        if (row >= rows || col >= cols) {
            cerr << "Matrix subscript out of bounds" << endl;
            return dummy;
        }
        return data[row * cols + col];
    }

    // TODO2: Implement the output operator to print the matrix to an ostream
    // You should iterate over each element of the matrix, printing each row on a new line.
    // Each element should be separated by a space.

    friend ostream& operator<<(ostream& os, const Matrix<T>& matrix) {
        for (int i = 0; i < matrix.rows * matrix.cols; ++i){
            if ((i+1) % matrix.cols == 0){
                os << matrix.data[i] << endl;
            } else {
                os << matrix.data[i] << " ";
            }
        }
        return os;
    }


    // TODO3.1: Implement the addition operator to add two matrices
    // We assume both matrices have the same dimensions before performing the addition.
    Matrix<T> operator+(const Matrix<T>& rhs) const {
        cout << "Performing addition operation" << endl;
        Matrix<T> item {rows,cols};
        for (int i = 0; i < rows * cols; ++i){
            item.data[i] = data[i] + rhs.data[i];
        }
        return item;
    }

    // TODO3.2: Implement the subtraction operator to subtract one matrix from another
    // We assume both matrices have the same dimensions before performing the subtraction.

    Matrix<T> operator-(const Matrix<T>& rhs) const {
        cout << "Performing subtraction operation" << endl;
        Matrix<T> item {rows,cols};
        for (int i = 0; i < rows * cols; ++i){
            item.data[i] = data[i] - rhs.data[i];
        }
        return item;
    }

    // TODO4: Implement the multiplication operator to multiply two matrices
    // We assume the number of columns in the first matrix equal the number of rows in the second matrix.
    // The resulting matrix should have the number of rows of the first matrix and the number of columns of the second matrix.

    Matrix<T> operator*(const Matrix<T>& rhs) const {
        cout << "Performing multiplication operation" << endl;
        Matrix<T> item {rows,rhs.cols};
        // int arr1row = 0;
        // int arr2col = 0;
        // for (int outerMat = 0; outerMat < rows * rhs.cols; ++outerMat){ //iterate horizontally through array
        //     item.data[outerMat] = 0;
        //     for( int i = arr1row * cols, j = arr2col * rhs.rows; i < cols * (arr1row + 1); ++i, j += rhs.rows){
        //         item.data[outerMat] += data[i] * rhs.data[j];
        //     }
        //     arr1row = outerMat / cols;
        //     arr2col = (outerMat % cols);
        // }

        // for (int i = 0; i < rows; ++i) {
        //     for (int j = 0; j < rhs.cols; ++j) {
        //         for (int k = 0; k < cols; ++k) {
        //             item.data[i * rhs.cols + j] += static_cast<int>(data[i * cols + k] * rhs.data[k * rhs.cols + j]);
        //         }
        //     }
        // }

        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < rhs.cols; ++j){
                item(i,j) = 0;
            }
        } 
        
        for (int i = 0; i < rows; ++i){
            for (int j = 0; j < rhs.cols; ++j){
                for (int k = 0; k < cols; ++k){
                    item(i,j) += this->operator()(i,k) * rhs(k,j);
                }
            }
        }

        return item;

    }

    // TODO5: Implement the inversion operator (~) to calculate the inverse of a 2x2 matrix
    // We assume the matrix is a invertible 2x2 matrix
    Matrix<T> operator~() const {
        cout << "Performing inversion operation" << endl;
        Matrix<T> item {rows, cols};
        T detInver = (data[0]*data[3] - data[1]*data[2]);
        item(0, 0) = data[3] / detInver;
        item(0, 1) = -data[1] / detInver;
        item(1, 0) = -data[2] / detInver;
        item(1, 1) = data[0] / detInver;
        return item;
        // T det = data[0] * data[3] - data[1] * data[2];
        // assert(det != 0); // Check if matrix is invertible

        // Matrix<T> result(2, 2);
        // result(0, 0) = data[3] / det;
        // result(0, 1) = -data[1] / det;
        // result(1, 0) = -data[2] / det;
        // result(1, 1) = data[0] / det;

        // return result;
    }

};


#endif // MATRIX_H
