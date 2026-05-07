#pragma once
#include "Bird.h"

class Crow : public Bird
{
public:
    void Description() const override;
    string GetType() const override;
    string GetGroup() const override;
};