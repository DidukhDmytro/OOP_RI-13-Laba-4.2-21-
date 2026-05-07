#pragma once
#include "Mammal.h"

class Animal : public Mammal
{
public:
    virtual string GetAnimalType() const = 0;
};