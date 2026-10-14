#pragma once
#include <initializer_list>
#include "vector.h"

template <typename T>
class MathVector : protected Vector<T> {
	size_t _start_index;

public:
	using Vector<T>::size;
	using Vector<T>::capacity;
	using Vector<T>::is_empty;
	using Vector<T>::is_full;

	MathVector(size_t size = 1, T* data = nullptr, size_t start_index = 0);
	MathVector(std::initializer_list<T> data);
	MathVector(const MathVector<T>& other);

	~MathVector() {}

	inline size_t start_index() const noexcept;

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

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
inline size_t MathVector<T>::start_index() const noexcept {
	return _start_index;
}

template <typename T>
inline size_t MathVector<T>::size() const noexcept { 
	return Vector<T>::size();
}

template <typename T>
MathVector<T>::MathVector(size_t size, T* data, size_t start_index) : Vector<T>(data, size), _start_index(start_index) {
	Vector<T>::shrink_to_fit();
}

template <typename T>	
MathVector<T>::MathVector(std::initializer_list<T> data) : Vector<T>(data), _start_index(0) {
	Vector<T>::shrink_to_fit();
}

template <typename T>
MathVector<T>::MathVector(const MathVector<T>& other) : Vector<T>(other), _start_index(other._start_index) {
	Vector<T>::shrink_to_fit();
}

template <typename T>
T& MathVector<T>::operator[](size_t index) {
	if (index >= _start_index + size()) {
		throw std::out_of_range("Index out of range.");
	}

	if (index < _start_index) {
		static T def;
		def = T();
		return def;
	}

	return Vector<T>::operator[](index - _start_index);
}

template <typename T>
const T& MathVector<T>::operator[](size_t index) const {
	if (index >= _start_index + size()) {
		throw std::out_of_range("Index out of range.");
	}

	if (index < _start_index) {
		static const T def = T();
		return def;
	}

	return Vector<T>::operator[](index - _start_index);
}

template <typename T>
MathVector<T> MathVector<T>::operator*(double val) const noexcept {
	MathVector<T> result(*this);
	return result *= val;
}

template <typename T>
MathVector<T>& MathVector<T>::operator*=(double val) noexcept {
	for (size_t i = _start_index; i < _start_index + size(); i++) {
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
	if (size() != other.size() || _start_index != other._start_index) {
		throw std::invalid_argument("Vectors must be of the same size for addition.");
	}

	for (size_t i = _start_index; i < _start_index + size(); i++) {
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
	if (this->size() != other.size() || _start_index != other._start_index) {
		throw std::invalid_argument("Vectors must be of the same size for subtraction.");
	}

	for (size_t i = _start_index; i < _start_index + size(); i++) {
		(*this)[i] -= other[i];
	}

	return *this;
}

template <typename T>
double MathVector<T>::operator*(const MathVector<T>& other) const {
	if (this->size() != other.size() || _start_index != other._start_index) {
		throw std::invalid_argument("Vectors must be of the same size for dot product.");
	}

	double result = 0.0;

	for (size_t i = _start_index; i < _start_index + size(); i++) {
		result += (*this)[i] * other[i];
	}

	return result;
}