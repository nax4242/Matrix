#pragma once
#include "MathVector.h"

template <typename T>
class Matrix : public MathVector<MathVector<T>> {
public:
    Matrix(size_t rows, size_t cols);
    Matrix(std::initializer_list<std::initializer_list<T>> data);
    Matrix(const Matrix<T>& other);

    Matrix(const MathVector<MathVector<T>>& vec);
    ~Matrix() {}

    inline size_t rows() const noexcept;
    inline size_t cols() const noexcept;

    using MathVector<MathVector<T>>::operator*;
    Matrix<T> operator*(const Matrix<T>& other) const;
    Matrix<T> transpose() const;
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : MathVector<MathVector<T>>(rows) {
    for (size_t i = 0; i < rows; i++) {
        (*this)[i] = MathVector<T>(cols);
    }
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> data) : MathVector<MathVector<T>>(data.size()) {
    size_t expected_row_size = data.begin()->size();

    size_t i = 0;
    for (const auto& row : data) {
        if (row.size() != expected_row_size) {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
        
        (*this)[i] = MathVector<T>(row);
        i++;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : MathVector<MathVector<T>>(other) {}

template <typename T>
Matrix<T>::Matrix(const MathVector<MathVector<T>>& vec) : MathVector<MathVector<T>>(vec) {}

template <typename T>
inline size_t Matrix<T>::rows() const noexcept {
    return this->size();
}

template <typename T>
inline size_t Matrix<T>::cols() const noexcept {
    return (*this)[0].size();
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
    if (cols() != other.rows()) {
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
    }

    Matrix<T> result(rows(), other.cols());
    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < other.cols(); j++) {
            double sum = 0;

            for (int k = 0; k < cols(); k++) {
                sum += (*this)[i][k] * other[k][j];
            }

            result[i][j] = sum;
        }
    }

    return result;
}

template <typename T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> result(cols(), rows());

    for (int i = 0; i < rows(); i++) {
        for (int j = 0; j < cols(); j++) {
            result[j][i] = (*this)[i][j];
        }
    }

    return result;
}