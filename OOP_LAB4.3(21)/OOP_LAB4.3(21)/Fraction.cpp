#include "Fraction.h"

Fraction::Fraction(string number) : Array()
{
    sign = '+';

    if (number[0] == '-')
    {
        sign = '-';
        number.erase(0, 1);
    }

    int pointPos = number.find('.');
    fracDigits = 0;
    size = 0;

    for (int i = 0; i < number.length(); i++)
    {
        if (number[i] == '.')
            continue;

        arr[size++] = number[i] - '0';

        if (pointPos != string::npos && i > pointPos)
            fracDigits++;
    }
}

Fraction::Fraction(const unsigned char* digits, int n, int frac, char s) : Array()
{
    size = n;
    fracDigits = frac;
    sign = s;

    for (int i = 0; i < size; i++)
        arr[i] = digits[i];
}

Array* Fraction::add(const Array& other) const
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

void Fraction::print() const
{
    cout << "Fraction: ";

    if (sign == '-')
        cout << "-";

    for (int i = 0; i < size; i++)
    {
        if (i == size - fracDigits)
            cout << ".";

        cout << (int)arr[i];
    }

    cout << endl;
}