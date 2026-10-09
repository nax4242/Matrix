#pragma once
#include <initializer_list>
#include "vector.h"

template <typename T>
class MathVector : protected Vector<T> {
public:
	using Vector<T>::operator[];
	using Vector<T>::size;
	using Vector<T>::capacity;
	using Vector<T>::is_empty;
	using Vector<T>::is_full;

	MathVector(size_t size = 1, T* data = nullptr);
	MathVector(std::initializer_list<T> data);
	MathVector(const MathVector<T>& other);

	~MathVector() {}


	MathVector<T> operator*(double val) const noexcept;
	MathVector<T>& operator*=(double val) noexcept;

	MathVector<T> operator+(const MathVector<T>& other) const;
	MathVector<T>& operator+=(const MathVector<T>& other);

	MathVector<T> operator-(const MathVector<T>& other) const;
	MathVector<T>& operator-=(const MathVector<T>& other);

	double operator*(const MathVector<T>& other) const;

	inline size_t size() const noexcept;
};

template <typename T>
inline size_t MathVector<T>::size() const noexcept { 
	return Vector<T>::size();
}

template <typename T>
MathVector<T>::MathVector(size_t size, T* data) : Vector<T>(data, size) {
	Vector<T>::shrink_to_fit();
}

template <typename T>	
MathVector<T>::MathVector(std::initializer_list<T> data) : Vector<T>(data) {
	Vector<T>::shrink_to_fit();
}

template <typename T>
MathVector<T>::MathVector(const MathVector<T>& other) : Vector<T>(other) {
	Vector<T>::shrink_to_fit();
}

template <typename T>
MathVector<T> MathVector<T>::operator*(double val) const noexcept {
	MathVector<T> result(*this);
	return result *= val;
}

template <typename T>
MathVector<T>& MathVector<T>::operator*=(double val) noexcept {
	for (size_t i = 0; i < this->size(); ++i) {
		(*this)[i] *= val;
	}

	return *this;
}

template <typename T>
MathVector<T> MathVector<T>::operator+(const MathVector<T>& other) const {
	MathVector<T> result(*this);
	return result += other;
}

template <typename T>
MathVector<T>& MathVector<T>::operator+=(const MathVector<T>& other) {
	if (this->size() != other.size()) {
		throw std::invalid_argument("Vectors must be of the same size for addition.");
	}

	for (size_t i = 0; i < this->size(); ++i) {
		(*this)[i] += other[i];
	}

	return *this;
}

template <typename T>
MathVector<T> MathVector<T>::operator-(const MathVector<T>& other) const {
	MathVector<T> result(*this);
	return result -= other;;
}

template <typename T>	
MathVector<T>& MathVector<T>::operator-=(const MathVector<T>& other) {
	if (this->size() != other.size()) {
		throw std::invalid_argument("Vectors must be of the same size for subtraction.");
	}

	for (size_t i = 0; i < this->size(); ++i) {
		(*this)[i] -= other[i];
	}

	return *this;
}

template <typename T>
double MathVector<T>::operator*(const MathVector<T>& other) const {
	if (this->size() != other.size()) {
		throw std::invalid_argument("Vectors must be of the same size for dot product.");
	}

	double result = 0.0;

	for (size_t i = 0; i < this->size(); ++i) {
		result += (*this)[i] * other[i];
	}

	return result;
}