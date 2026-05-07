#pragma once
#include "IVertebrate.h"

class Mammal : public IVertebrate
{
public:
    virtual string GetGroup() const = 0;
};