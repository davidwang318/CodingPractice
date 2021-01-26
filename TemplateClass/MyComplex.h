#ifndef MY_COMPLEX_H
#define MY_COMPLEX_H

#include <iostream>

// Forward declaration
template <typename T> class MyComplex;

template <typename T>
std::ostream & operator << (std::ostream & out, const MyComplex<T> & c);

template <typename T>
std::istream & operator >> (std::istream & in, MyComplex<T> & c);

// MyComplex template class declaration
template<typename T>
class MyComplex {
private:
	T real, imag;
public:
	// Contructor
	explicit MyComplex<T> (T real = 0, T imag = 0): real(real), imag(imag) {};
	
	// Overload operator
	MyComplex<T> & operator += (const MyComplex<T> & rhs) {
		real += rhs.real;
		imag += rhs.imag;
		return *this;
	}
	MyComplex<T> & operator += (T value) {
		real += value;
		return *this;
	}
	bool operator == (const MyComplex<T> & rhs) const {
		return (real == rhs.real && imag == rhs.imag);
	}
	bool operator != (const MyComplex<T> & rhs) const {
		return !(*this == rhs);
	}
	MyComplex<T> & operator ++ (); // only definition: ++MyComplex
	const MyComplex<T> operator ++ (int dummy); // only definition: MyComplex++

	// Friends
	friend std::ostream & operator << <> (std::ostream& out, const MyComplex<T> & c); // out << c;
	friend std::istream & operator >> <> (std::istream & in, MyComplex<T> & c); // in >> c;
	// Inline implementation for easy use
	friend const MyComplex<T> operator + (const MyComplex<T> & lhs, const MyComplex<T> & rhs) {
		MyComplex<T> result(lhs);
		result += rhs;
		return result;
	};
	friend const MyComplex<T> operator + (const MyComplex<T> & lhs, T value) {
		MyComplex<T> result(lhs);
		result += value;
		return result;
	};
	friend const MyComplex<T> operator + (T value, const MyComplex<T>& rhs) {
		return rhs + value;
	};
};

// Function implementation:
template <typename T>
MyComplex<T> & MyComplex<T>::operator++ () {
	++real;
	return *this;
}
template <typename T>
const MyComplex<T> MyComplex<T>::operator++ (int dummy) {
	MyComplex<T> saved(*this);
	++real;
	return saved;
}
template <typename T>
std::ostream& operator << (std::ostream& out, const MyComplex<T> & c) {
	out << '(' << c.real << ',' << c.imag << ')';
	return out;
}
template <typename T>
std::istream& operator >> (std::istream& in, MyComplex<T> & c) {
	T inReal, inImag;
	char inChar;
	bool validInput = false;
	in >> inChar;
	if (inChar == '(') {
		in >> inReal >> inChar;
		if (inChar == ')') {
			c = MyComplex<T>(inReal, inImag);
			validInput = true;
		}
	}
	if (!validInput) in.setstate(std::ios_base::failbit);
	return in;
}

#endif