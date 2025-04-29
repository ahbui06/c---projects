#pragma once

#include "Vehicle.h"

class Player;

class SportsCar : public Vehicle {
public:
    SportsCar();
    void useSpecialAbility(Player& player) override;
};
