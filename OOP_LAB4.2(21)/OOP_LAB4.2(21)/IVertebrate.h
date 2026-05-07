#pragma once
#include <string>

using namespace std;

class IVertebrate
{
public:
    virtual void Description() const = 0;
    virtual string GetType() const = 0;

    virtual ~IVertebrate() {}
};