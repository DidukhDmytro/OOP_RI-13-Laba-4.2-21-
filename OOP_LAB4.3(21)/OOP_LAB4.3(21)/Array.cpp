#include "Array.h"

Array::Array(int n, unsigned char value)
{
    if (n < 0 || n > MAX_SIZE)
        n = 0;

    size = n;

    for (int i = 0; i < size; i++)
        arr[i] = value;
}

Array::~Array() {}

bool Array::rangeCheck(int index) const
{
    return index >= 0 && index < size;
}

unsigned char& Array::operator[](int index)
{
    if (!rangeCheck(index))
    {
        cout << "Index error!" << endl;
        exit(1);
    }

    return arr[index];
}

int Array::getSize() const
{
    return size;
}

Array* Array::add(const Array& other) const
{
    int minSize = size < other.size ? size : other.size;
    Array* result = new Array(minSize);

    for (int i = 0; i < minSize; i++)
        result->arr[i] = arr[i] + other.arr[i];

    return result;
}

void Array::print() const
{
    cout << "Array: ";

    for (int i = 0; i < size; i++)
        cout << (int)arr[i] << " ";

    cout << endl;
}