#include <iostream>
#include <typeinfo>
#include "Array.h"
#include "Fraction.h"
#include "BitString.h"

using namespace std;

int main()
{
    cout << "Fraction" << endl;

    Fraction f1("123.45");
    Fraction f2("76.55");

    f1.print();
    f2.print();

    Array* fResult = f1.add(f2);

    cout << "Result of Fraction addition: ";
    fResult->print();

    cout << endl;


    cout << "BitString" << endl;

    BitString b1("101101");
    BitString b2("001011");

    b1.print();
    b2.print();

    Array* bResult = b1.add(b2);

    cout << "Binary addition: ";
    bResult->print();

    cout << "AND: ";
    b1.And(b2).print();

    cout << "OR: ";
    b1.Or(b2).print();

    cout << "XOR: ";
    b1.Xor(b2).print();

    cout << "NOT b1: ";
    b1.Not().print();

    cout << "Shift left b1 by 2: ";
    b1.shiftLeft(2).print();

    cout << "Shift right b1 by 2: ";
    b1.shiftRight(2).print();

    cout << endl;


    cout << "Polymorphism" << endl;

    Array* objects[3];

    objects[0] = new Array(5, 1);
    objects[1] = new Fraction("12.34");
    objects[2] = new BitString("10101");

    for (int i = 0; i < 3; i++)
    {
        cout << "Real type: " << typeid(*objects[i]).name() << endl;
        objects[i]->print();
        cout << endl;
    }

    delete fResult;
    delete bResult;

    for (int i = 0; i < 3; i++)
        delete objects[i];

    return 0;
}