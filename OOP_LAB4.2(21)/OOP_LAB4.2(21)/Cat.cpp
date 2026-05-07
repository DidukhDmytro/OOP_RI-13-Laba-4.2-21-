#include "Cat.h"
#include <iostream>

using namespace std;

void Cat::Description() const
{
    cout << "Cat: independent domestic animal." << endl;
}

string Cat::GetType() const
{
    return "Cat";
}

string Cat::GetGroup() const
{
    return "Mammal";
}

string Cat::GetAnimalType() const
{
    return "Domestic animal";
}