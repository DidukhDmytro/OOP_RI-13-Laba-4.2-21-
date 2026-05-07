#pragma once
#include "IVertebrate.h"

class Bird : public IVertebrate
{
public:
    virtual string GetGroup() const = 0;
};