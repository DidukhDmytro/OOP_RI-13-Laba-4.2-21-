#include "BitString.h"

BitString::BitString(string bits) : Array()
{
    size = bits.length();

    if (size > MAX_SIZE)
        size = MAX_SIZE;

    for (int i = 0; i < size; i++)
        arr[i] = bits[i] == '1' ? 1 : 0;
}

BitString::BitString(const unsigned char* bits, int n) : Array()
{
    size = n;

    for (int i = 0; i < size; i++)
        arr[i] = bits[i];
}

Array* BitString::add(const Array& other) const
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

BitString BitString::And(const BitString& b) const
{
    unsigned char res[MAX_SIZE] = {};
    int n = size < b.size ? size : b.size;

    for (int i = 0; i < n; i++)
        res[i] = arr[i] & b.arr[i];

    return BitString(res, n);
}

BitString BitString::Or(const BitString& b) const
{
    unsigned char res[MAX_SIZE] = {};
    int n = size < b.size ? size : b.size;

    for (int i = 0; i < n; i++)
        res[i] = arr[i] | b.arr[i];

    return BitString(res, n);
}

BitString BitString::Xor(const BitString& b) const
{
    unsigned char res[MAX_SIZE] = {};
    int n = size < b.size ? size : b.size;

    for (int i = 0; i < n; i++)
        res[i] = arr[i] ^ b.arr[i];

    return BitString(res, n);
}

BitString BitString::Not() const
{
    unsigned char res[MAX_SIZE] = {};

    for (int i = 0; i < size; i++)
        res[i] = arr[i] == 0 ? 1 : 0;

    return BitString(res, size);
}

BitString BitString::shiftLeft(int k) const
{
    unsigned char res[MAX_SIZE] = {};

    if (k >= size)
        return BitString(res, size);

    for (int i = 0; i < size - k; i++)
        res[i] = arr[i + k];

    for (int i = size - k; i < size; i++)
        res[i] = 0;

    return BitString(res, size);
}

BitString BitString::shiftRight(int k) const
{
    unsigned char res[MAX_SIZE] = {};

    if (k >= size)
        return BitString(res, size);

    for (int i = size - 1; i >= k; i--)
        res[i] = arr[i - k];

    for (int i = 0; i < k; i++)
        res[i] = 0;

    return BitString(res, size);
}

void BitString::print() const
{
    cout << "BitString: ";

    for (int i = 0; i < size; i++)
        cout << (int)arr[i];

    cout << endl;
}