#pragma once
#include "Array.h"
#include <string>
using namespace std;

class BitString : public Array
{
public:
    BitString(string bits = "");
    BitString(const unsigned char* bits, int n);

    Array* add(const Array& other) const override;

    BitString And(const BitString& b) const;
    BitString Or(const BitString& b) const;
    BitString Xor(const BitString& b) const;
    BitString Not() const;

    BitString shiftLeft(int k) const;
    BitString shiftRight(int k) const;

    void print() const override;
};