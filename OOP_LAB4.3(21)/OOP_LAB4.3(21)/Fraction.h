#pragma once
#include "Array.h"
#include <string>
using namespace std;

class Fraction : public Array
{
private:
    int fracDigits;
    char sign;

public:
    Fraction(string number = "0.0");
    Fraction(const unsigned char* digits, int n, int frac, char s);

    Array* add(const Array& other) const override;
    void print() const override;
};