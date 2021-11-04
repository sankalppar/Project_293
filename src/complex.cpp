#include <complex.hpp>

complex_num::complex_num(long double R, long double I)
{
    this->real = R;
    this->im = I;
}

complex_num complex_num::operator+(complex_num z)
{
    complex_num res;
    res.real = z.real + this->real;
    res.im = z.im + this->im;
    return res;
}

complex_num complex_num::operator*(complex_num z)
{
    complex_num res;
    res.real = z.real*this->real - z.im*this->im;
    res.im = z.real*this->im + this->real*z.im;
    return res;
}

complex_num complex_num::operator-(complex_num z)
{
    complex_num res;
    res.real = this->real - z.real;
    res.im = this->im - z.im;
    return res;
}

complex_num complex_num::operator/(complex_num z)
{
    complex_num res;
    res.real = z.real*this->real + z.im*this->im;
    res.im = this->im*z.real - z.im*this->real;
    res.real = res.real / (z.im*z.im + z.real*z.real);
    res.im = res.im / (z.im*z.im + z.real*z.real);
    return res;
}

complex_num complex_num::square()
{
    complex_num res;
    res.real = this->real*this->real - this->im*this->im;
    res.im = 2 * this->real *this->im;
    return res;
}

long double complex_num::modulus()
{
    long double res;
    res = this->real * this->real + this->im * this->im;
    return res;
}

long double complex_num::real_part()
{
    long double res;
    res = this->real;
    return res;
}

long double complex_num::imag()
{
    long double res;
    res = this->im;
    return res;
}

complex_num complex_num::conjugate()
{
    complex_num res;
    res.real = this->real;
    res.im = -this->im;
    return res;
}
