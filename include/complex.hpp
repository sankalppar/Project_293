#include <iostream>

class complex_num
{
    long double real;
    long double im;
  public:
    complex_num(){}
    complex_num(long double R, long double I);
    complex_num operator+(complex_num z);
    complex_num operator*(complex_num z);
    complex_num operator/(complex_num z);
    complex_num operator-(complex_num z);
    complex_num square();
    long double modulus();
    long double real_part();
    long double imag();
    complex_num conjugate();
};
