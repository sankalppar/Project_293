/*
    Class : complex_num
    Written By : Sankalp Parashar
    Header file for complex.cpp containing declarations for standard operators
    on complex numbers so that they can be used easily in mandelbrot.cpp
*/

#ifndef COMPLEX_NUM
#define COMPLEX_NUM

#include <iostream>

class complex_num
{
    long double real;
    long double im;
  public:
    complex_num(){}
    complex_num(long double R, long double I);

    //Operator overloading on standard binary operations for complex numbers
    complex_num operator+(complex_num z);
    complex_num operator*(complex_num z);
    complex_num operator/(complex_num z);
    complex_num operator-(complex_num z);

    //Common unary operations on complex numbers
    complex_num square();
    long double modulus();
    long double real_part();
    long double imag();
    complex_num conjugate();
};

#endif
