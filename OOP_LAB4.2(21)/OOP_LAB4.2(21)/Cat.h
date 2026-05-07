#pragma once
#include "Animal.h"

class Cat : public Animal
{
public:
    void Description() const override;
    string GetType() const override;
    string GetGroup() const override;
    string GetAnimalType() const override;
};