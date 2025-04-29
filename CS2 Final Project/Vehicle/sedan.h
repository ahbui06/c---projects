#pragma once

#include "Vehicle.h"

class Sedan : public Vehicle {
public:
    Sedan();
    void useSpecialAbility() override;
};