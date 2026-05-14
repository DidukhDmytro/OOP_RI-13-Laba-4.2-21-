#pragma once
#include <iostream>
using namespace std;

class Array
{
protected:
    static const int MAX_SIZE = 100;
    unsigned char arr[MAX_SIZE];
    int size;

public:
    Array(int n = 0, unsigned char value = 0);
    virtual ~Array();

    bool rangeCheck(int index) const;

    unsigned char& operator[](int index);

    int getSize() const;

    virtual Array* add(const Array& other) const;
    virtual void print() const;
};