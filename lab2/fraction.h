#pragma once
#include <iostream>
using namespace std;

class Fraction {
    int numer;
    int denom;
public:
    Fraction(int num, int den);
    Fraction(int num);
    void print();
    void normalize();
    Fraction operator *(Fraction frac);
    Fraction operator /(Fraction frac);
    Fraction operator +(Fraction frac);
    Fraction operator -(Fraction frac);
    Fraction operator *(int num);
    Fraction operator /(int num);
    Fraction operator +(int num);
    Fraction operator -(int num);
    void operator /=(Fraction frac);
    void operator *=(Fraction frac);
    void operator -=(Fraction frac);
    bool operator <(Fraction frac);
    bool operator ==(Fraction frac);
    friend Fraction abs(Fraction frac);
    friend Fraction operator -(Fraction frac);
    bool isZero();
};

Fraction abs(Fraction frac);
Fraction operator -(Fraction frac);