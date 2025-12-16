#ifndef _COMPLEXH
#define _COMPLEXH

#include <iostream>

class Complex {
public:
    Complex();
    Complex(double re, double im);
    ~Complex();

    double getReal(void);
    double getImaginary(void);

    void setReal(double re);
    void setImaginary(double im);

    Complex operator+(Complex& theComplex);
    Complex operator-(Complex& theComplex);
    Complex operator*(Complex& theComplex);
    Complex operator/(Complex& theComplex);

private:
    double real;
    double imag;
};

#endif
