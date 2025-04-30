#pragma once

#include "Vehicle.h"

class Player;

class SportsCar : public Vehicle {
public:
    SportsCar();
    void useSpecialAbility(EventType ev, Player &player, int &value) override;
};
