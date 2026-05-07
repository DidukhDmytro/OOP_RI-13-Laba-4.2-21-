#pragma once
#include "Animal.h"

class Dog : public Animal
{
public:
    void Description() const override;
    string GetType() const override;
    string GetGroup() const override;
    string GetAnimalType() const override;
};