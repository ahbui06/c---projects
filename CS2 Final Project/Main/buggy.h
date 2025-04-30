#pragma once

#include "Vehicle.h"

class Buggy : public Vehicle {
public:
    Buggy();
    void useSpecialAbility(EventType ev, Player &player, int &value) override;
};