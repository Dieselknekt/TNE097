#include "complex.h"

Complex::Complex() {
    real = 0.0;
    imag = 0.0;
}

Complex::Complex(double re, double im) {
    real = re;
    imag = im;
}

Complex::~Complex() {
    // nothing to clean up
}

double Complex::getReal(void) {
    return real;
}

double Complex::getImaginary(void) {
    return imag;
}

void Complex::setReal(double re) {
    real = re;
}

void Complex::setImaginary(double im) {
    imag = im;
}

Complex Complex::operator+(Complex& c) {
    return Complex(real + c.real, imag + c.imag);
}

Complex Complex::operator-(Complex& c) {
    return Complex(real - c.real, imag - c.imag);
}

Complex Complex::operator*(Complex& c) {
    return Complex(
        real * c.real - imag * c.imag,
        real * c.imag + imag * c.real
    );
}

Complex Complex::operator/(Complex& c) {
    double denom = c.real * c.real + c.imag * c.imag;
    return Complex(
        (real * c.real + imag * c.imag) / denom,
        (imag * c.real - real * c.imag) / denom
    );
}
