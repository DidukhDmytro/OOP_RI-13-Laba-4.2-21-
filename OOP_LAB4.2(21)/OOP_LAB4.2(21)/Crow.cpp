#include "Crow.h"
#include <iostream>

using namespace std;

void Crow::Description() const
{
    cout << "Crow: smart black bird." << endl;
}

string Crow::GetType() const
{
    return "Crow";
}

string Crow::GetGroup() const
{
    return "Bird";
}