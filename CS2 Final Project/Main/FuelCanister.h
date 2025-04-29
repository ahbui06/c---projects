#pragma once

#include "Item.h"

class FuelCanister : public Item {
public:
    FuelCanister();
    void use(Vehicle &v) override;
};
