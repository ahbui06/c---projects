#pragma once

#include "Vehicle.h"

class Player;

class Sedan : public Vehicle {
public:
    Sedan();
    void useSpecialAbility(Player &player) override;
};