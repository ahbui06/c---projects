#pragma once

#include "Vehicle.h"

class Truck : public Vehicle {
public:
    Truck();
    void useSpecialAbility(EventType ev, Player &player, int &value) override;
};