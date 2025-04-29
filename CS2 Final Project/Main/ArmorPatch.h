#pragma once

#include "Item.h"

class ArmorPatch : public Item {
public:
    ArmorPatch();
    void use(Vehicle &v) override;
};