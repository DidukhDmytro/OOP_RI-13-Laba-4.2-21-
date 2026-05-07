#include "Human.h"
#include <iostream>

using namespace std;

void Human::Description() const
{
    cout << "Human: a mammal that can think, speak and work." << endl;
}

string Human::GetType() const
{
    return "Human";
}

string Human::GetGroup() const
{
    return "Mammal";
}