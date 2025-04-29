#pragma once

#include "Vehicle.h"

class SportsCar : public Vehicle {
public:
    SportsCar();
    void useSpecialAbility() override;
};
