#include "Dog.h"
#include <iostream>

using namespace std;

void Dog::Description() const
{
    cout << "Dog: loyal domestic animal." << endl;
}

string Dog::GetType() const
{
    return "Dog";
}

string Dog::GetGroup() const
{
    return "Mammal";
}

string Dog::GetAnimalType() const
{
    return "Domestic animal";
}