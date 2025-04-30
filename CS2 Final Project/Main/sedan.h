#pragma once

#include "Vehicle.h"

class Player;

class Sedan : public Vehicle {
public:
    Sedan();
    void useSpecialAbility(EventType ev, Player &player, int &value) override;
};