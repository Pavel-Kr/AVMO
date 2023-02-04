#include "fraction.h"

int gcd(int a, int b) { //мнд
    int r1 = abs(max(a, b));
    int r2 = abs(min(a, b));
    while (r2 != 0)
    {
        int r = r1 % r2;
        r1 = r2;
        r2 = r;
        //cout << r1 << " > ";
    }
    //cout << endl;
    return r1;
}

int lcm(int a, int b) { //мнй
    return abs(a * b) / gcd(a, b);
}

Fraction::Fraction(int num, int den) {
    if (den == 0) throw "Denominator is zero!";
    numer = num;
    denom = den;
    if (denom < 0) {
        numer *= -1;
        denom *= -1;
    }
    this->normalize();
}
Fraction::Fraction(int num) : Fraction(num, 1) {}

void Fraction::print() {
    cout << numer;
    if (denom != 1) {
        cout << '/' << denom;
    }
}
void Fraction::normalize() {
    int nod = gcd(numer, denom);
    numer /= nod;
    denom /= nod;
}
Fraction Fraction::operator *(Fraction frac) {
    int num = this->numer * frac.numer;
    int den = this->denom * frac.denom;
    Fraction res(num, den);
    return res;
}
Fraction Fraction::operator /(Fraction frac) {
    Fraction inv(frac.denom, frac.numer);
    return *this * inv;
}
Fraction Fraction::operator +(Fraction frac) {
    int den = lcm(this->denom, frac.denom);
    int num = this->numer * (den / this->denom) + frac.numer * (den / frac.denom);
    Fraction res(num, den);
    return res;
}
Fraction Fraction::operator -(Fraction frac) {
    Fraction frac1(-frac.numer, frac.denom);
    return *this + frac1;
}
Fraction Fraction::operator *(int num) {
    Fraction res(this->numer * num, this->denom);
    return res;
}
Fraction Fraction::operator /(int num) {
    Fraction res(this->numer, this->denom * num);
    return res;
}
Fraction Fraction::operator +(int num) {
    Fraction res(this->numer + num * this->denom, this->denom);
    return res;
}
Fraction Fraction::operator -(int num) {
    Fraction res(this->numer - num * this->denom, this->denom);
    return res;
}

void Fraction::operator/=(Fraction frac)
{
    Fraction tmp = *this / frac;
    this->numer = tmp.numer;
    this->denom = tmp.denom;
}

void Fraction::operator*=(Fraction frac)
{
    Fraction tmp = *this * frac;
    this->numer = tmp.numer;
    this->denom = tmp.denom;
}

void Fraction::operator-=(Fraction frac)
{
    Fraction tmp = *this - frac;
    this->numer = tmp.numer;
    this->denom = tmp.denom;
}

bool Fraction::operator<(Fraction frac)
{
    int den = lcm(this->denom, frac.denom);
    int num1 = this->numer * (den / this->denom);
    int num2 = frac.numer * (den / frac.denom);;
    return num1 < num2;
}

bool Fraction::operator==(Fraction frac)
{
    return this->numer == frac.numer && this->denom == frac.denom;
}

bool Fraction::isZero()
{
    return this->numer == 0;
}

Fraction abs(Fraction frac)
{
    return Fraction(abs(frac.numer), frac.denom);
}

Fraction operator-(Fraction frac)
{
    return Fraction(-frac.numer, frac.denom);
}
