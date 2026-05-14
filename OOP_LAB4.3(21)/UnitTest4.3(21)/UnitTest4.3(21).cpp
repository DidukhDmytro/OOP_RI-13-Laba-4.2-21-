#include "pch.h"
#include "CppUnitTest.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

class Array
{
protected:
    static const int MAX_SIZE = 100;
    unsigned char arr[MAX_SIZE];
    int size;

public:
    Array(int n = 0, unsigned char value = 0)
    {
        size = n;

        for (int i = 0; i < size; i++)
            arr[i] = value;
    }

    virtual ~Array() {}

    bool rangeCheck(int index) const
    {
        return index >= 0 && index < size;
    }

    unsigned char& operator[](int index)
    {
        return arr[index];
    }

    int getSize() const
    {
        return size;
    }

    virtual Array* add(const Array& other) const
    {
        int n = size < other.size ? size : other.size;
        Array* result = new Array(n);

        for (int i = 0; i < n; i++)
            result->arr[i] = arr[i] + other.arr[i];

        return result;
    }
};

class Fraction : public Array
{
private:
    int fracDigits;
    char sign;

public:
    Fraction(string number = "0.0") : Array()
    {
        sign = '+';
        size = 0;
        fracDigits = 0;

        if (number[0] == '-')
        {
            sign = '-';
            number.erase(0, 1);
        }

        int pointPos = number.find('.');

        for (int i = 0; i < number.length(); i++)
        {
            if (number[i] == '.')
                continue;

            arr[size++] = number[i] - '0';

            if (pointPos != string::npos && i > pointPos)
                fracDigits++;
        }
    }

    Fraction(const unsigned char* digits, int n, int frac, char s) : Array()
    {
        size = n;
        fracDigits = frac;
        sign = s;

        for (int i = 0; i < size; i++)
            arr[i] = digits[i];
    }

    Array* add(const Array& other) const override
    {
        const Fraction& b = dynamic_cast<const Fraction&>(other);

        unsigned char a1[MAX_SIZE] = {};
        unsigned char b1[MAX_SIZE] = {};
        unsigned char res[MAX_SIZE] = {};

        int maxFrac = fracDigits > b.fracDigits ? fracDigits : b.fracDigits;

        int intA = size - fracDigits;
        int intB = b.size - b.fracDigits;
        int maxInt = intA > intB ? intA : intB;

        int total = maxInt + maxFrac;

        for (int i = 0; i < size; i++)
            a1[maxInt - intA + i] = arr[i];

        for (int i = 0; i < b.size; i++)
            b1[maxInt - intB + i] = b.arr[i];

        int carry = 0;

        for (int i = total - 1; i >= 0; i--)
        {
            int sum = a1[i] + b1[i] + carry;
            res[i] = sum % 10;
            carry = sum / 10;
        }

        if (carry > 0)
        {
            unsigned char finalRes[MAX_SIZE] = {};
            finalRes[0] = carry;

            for (int i = 0; i < total; i++)
                finalRes[i + 1] = res[i];

            return new Fraction(finalRes, total + 1, maxFrac, '+');
        }

        return new Fraction(res, total, maxFrac, '+');
    }
};

class BitString : public Array
{
public:
    BitString(string bits = "") : Array()
    {
        size = bits.length();

        for (int i = 0; i < size; i++)
            arr[i] = bits[i] == '1' ? 1 : 0;
    }

    BitString(const unsigned char* bits, int n) : Array()
    {
        size = n;

        for (int i = 0; i < size; i++)
            arr[i] = bits[i];
    }

    Array* add(const Array& other) const override
    {
        const BitString& b = dynamic_cast<const BitString&>(other);

        unsigned char res[MAX_SIZE] = {};
        int maxSize = size > b.size ? size : b.size;

        int carry = 0;

        for (int i = 0; i < maxSize; i++)
        {
            int aBit = 0;
            int bBit = 0;

            if (size - 1 - i >= 0)
                aBit = arr[size - 1 - i];

            if (b.size - 1 - i >= 0)
                bBit = b.arr[b.size - 1 - i];

            int sum = aBit + bBit + carry;
            res[maxSize - 1 - i] = sum % 2;
            carry = sum / 2;
        }

        if (carry == 1)
        {
            unsigned char finalRes[MAX_SIZE] = {};
            finalRes[0] = 1;

            for (int i = 0; i < maxSize; i++)
                finalRes[i + 1] = res[i];

            return new BitString(finalRes, maxSize + 1);
        }

        return new BitString(res, maxSize);
    }

    BitString And(const BitString& b) const
    {
        unsigned char res[MAX_SIZE] = {};
        int n = size < b.size ? size : b.size;

        for (int i = 0; i < n; i++)
            res[i] = arr[i] & b.arr[i];

        return BitString(res, n);
    }

    BitString Or(const BitString& b) const
    {
        unsigned char res[MAX_SIZE] = {};
        int n = size < b.size ? size : b.size;

        for (int i = 0; i < n; i++)
            res[i] = arr[i] | b.arr[i];

        return BitString(res, n);
    }

    BitString Xor(const BitString& b) const
    {
        unsigned char res[MAX_SIZE] = {};
        int n = size < b.size ? size : b.size;

        for (int i = 0; i < n; i++)
            res[i] = arr[i] ^ b.arr[i];

        return BitString(res, n);
    }

    BitString Not() const
    {
        unsigned char res[MAX_SIZE] = {};

        for (int i = 0; i < size; i++)
            res[i] = arr[i] == 0 ? 1 : 0;

        return BitString(res, size);
    }

    BitString shiftLeft(int k) const
    {
        unsigned char res[MAX_SIZE] = {};

        for (int i = 0; i < size - k; i++)
            res[i] = arr[i + k];

        for (int i = size - k; i < size; i++)
            res[i] = 0;

        return BitString(res, size);
    }

    BitString shiftRight(int k) const
    {
        unsigned char res[MAX_SIZE] = {};

        for (int i = size - 1; i >= k; i--)
            res[i] = arr[i - k];

        for (int i = 0; i < k; i++)
            res[i] = 0;

        return BitString(res, size);
    }
};

namespace UnitTestLab
{
    TEST_CLASS(UnitTestLab)
    {
    public:

        TEST_METHOD(TestArrayRangeCheck)
        {
            Array a(5, 1);

            Assert::IsTrue(a.rangeCheck(0));
            Assert::IsTrue(a.rangeCheck(4));
            Assert::IsFalse(a.rangeCheck(5));
            Assert::IsFalse(a.rangeCheck(-1));
        }

        TEST_METHOD(TestArrayIndexOperator)
        {
            Array a(3, 7);

            Assert::AreEqual(7, (int)a[0]);
            Assert::AreEqual(7, (int)a[1]);
            Assert::AreEqual(7, (int)a[2]);
        }

        TEST_METHOD(TestArrayAdd)
        {
            Array a(3, 2);
            Array b(3, 5);

            Array* result = a.add(b);

            Assert::AreEqual(7, (int)(*result)[0]);
            Assert::AreEqual(7, (int)(*result)[1]);
            Assert::AreEqual(7, (int)(*result)[2]);

            delete result;
        }

        TEST_METHOD(TestFractionAdd)
        {
            Fraction f1("123.45");
            Fraction f2("76.55");

            Array* result = f1.add(f2);

            Assert::AreEqual(2, (int)(*result)[0]);
            Assert::AreEqual(0, (int)(*result)[1]);
            Assert::AreEqual(0, (int)(*result)[2]);
            Assert::AreEqual(0, (int)(*result)[3]);
            Assert::AreEqual(0, (int)(*result)[4]);

            delete result;
        }

        TEST_METHOD(TestBitStringAdd)
        {
            BitString b1("1011");
            BitString b2("0011");

            Array* result = b1.add(b2);

            Assert::AreEqual(1, (int)(*result)[0]);
            Assert::AreEqual(1, (int)(*result)[1]);
            Assert::AreEqual(1, (int)(*result)[2]);
            Assert::AreEqual(0, (int)(*result)[3]);

            delete result;
        }

        TEST_METHOD(TestBitStringAnd)
        {
            BitString b1("1011");
            BitString b2("0011");

            BitString result = b1.And(b2);

            Assert::AreEqual(0, (int)result[0]);
            Assert::AreEqual(0, (int)result[1]);
            Assert::AreEqual(1, (int)result[2]);
            Assert::AreEqual(1, (int)result[3]);
        }

        TEST_METHOD(TestBitStringOr)
        {
            BitString b1("1011");
            BitString b2("0011");

            BitString result = b1.Or(b2);

            Assert::AreEqual(1, (int)result[0]);
            Assert::AreEqual(0, (int)result[1]);
            Assert::AreEqual(1, (int)result[2]);
            Assert::AreEqual(1, (int)result[3]);
        }

        TEST_METHOD(TestBitStringXor)
        {
            BitString b1("1011");
            BitString b2("0011");

            BitString result = b1.Xor(b2);

            Assert::AreEqual(1, (int)result[0]);
            Assert::AreEqual(0, (int)result[1]);
            Assert::AreEqual(0, (int)result[2]);
            Assert::AreEqual(0, (int)result[3]);
        }

        TEST_METHOD(TestBitStringNot)
        {
            BitString b1("1011");

            BitString result = b1.Not();

            Assert::AreEqual(0, (int)result[0]);
            Assert::AreEqual(1, (int)result[1]);
            Assert::AreEqual(0, (int)result[2]);
            Assert::AreEqual(0, (int)result[3]);
        }

        TEST_METHOD(TestBitStringShiftLeft)
        {
            BitString b1("1011");

            BitString result = b1.shiftLeft(2);

            Assert::AreEqual(1, (int)result[0]);
            Assert::AreEqual(1, (int)result[1]);
            Assert::AreEqual(0, (int)result[2]);
            Assert::AreEqual(0, (int)result[3]);
        }

        TEST_METHOD(TestBitStringShiftRight)
        {
            BitString b1("1011");

            BitString result = b1.shiftRight(2);

            Assert::AreEqual(0, (int)result[0]);
            Assert::AreEqual(0, (int)result[1]);
            Assert::AreEqual(1, (int)result[2]);
            Assert::AreEqual(0, (int)result[3]);
        }
    };
}