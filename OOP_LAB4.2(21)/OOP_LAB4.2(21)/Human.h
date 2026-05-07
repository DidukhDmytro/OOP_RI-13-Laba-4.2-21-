#pragma once
#include "Mammal.h"

class Human : public Mammal
{
public:
    void Description() const override;
    string GetType() const override;
    string GetGroup() const override;
};