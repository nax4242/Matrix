#pragma once
#include "Matrix.h"

template <typename T>
class TriangleMatrix : public Matrix<T> {
public:
    TriangleMatrix(size_t n = 1);
    TriangleMatrix(std::initializer_list<std::initializer_list<T>> data);
    TriangleMatrix(const MathVector<MathVector<T>>& vec);

    TriangleMatrix(const TriangleMatrix<T>&) = default;
    TriangleMatrix(TriangleMatrix<T>&&) noexcept = default;

    ~TriangleMatrix() = default;

    TriangleMatrix<T>& operator=(const TriangleMatrix<T>&) = default;
    TriangleMatrix<T>& operator=(TriangleMatrix<T>&&) noexcept = default;

    inline size_t size() const noexcept;
};

template <typename T>
TriangleMatrix<T>::TriangleMatrix(size_t n) : Matrix<T>(n, n) {
    for (size_t i = 0; i < n; i++) {
        (*this)[i] = MathVector<T>(n - i, nullptr, i);
    }
}

template <typename T>
TriangleMatrix<T>::TriangleMatrix(std::initializer_list<std::initializer_list<T>> data) : Matrix<T>(data) {
    size_t n = data.size();

    if (data.begin()->size() != n) {
        throw std::invalid_argument("Matrix must be square");
    }

    for (size_t i = 0; i < n; i++) {
        MathVector<T> row(n - i, nullptr, i);

        for (size_t j = 0; j < n; j++) {
            if (j < i && (*this)[i][j] != T()) {
                throw std::invalid_argument("Elements below the diagonal must be zero");
            }

            if (j >= i) row[j] = (*this)[i][j];
        }

        (*this)[i] = row;
    }
}

template <typename T>
TriangleMatrix<T>::TriangleMatrix(const MathVector<MathVector<T>>& vec) : Matrix<T>(vec) {}

template <typename T>
inline size_t TriangleMatrix<T>::size() const noexcept {
    return this->rows();
}
