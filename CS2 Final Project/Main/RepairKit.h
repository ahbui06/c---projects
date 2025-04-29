#pragma once

#include "Item.h"

class RepairKit : public Item {
public:
    RepairKit();
    void use(Vehicle &v) override;
};