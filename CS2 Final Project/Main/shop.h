#pragma once

#include "Vehicle.h"
#include "Item.h"

class Player;

static const int SHOP_VEHICLE_COUNT = 4;
static const int SHOP_ITEM_COUNT = 3;

class Shop {
public:
    Shop();
    ~Shop();

    void displayVehicles() const;
    void displayItems() const;

    bool purchaseVehicle(int index, Player &player);
    bool purchaseItem(int index, Player &player);

    const Vehicle* getVehicle(int index) const;
    const Item* getItem(int index) const;

private:
    Vehicle* vehicleCatalog[SHOP_VEHICLE_COUNT];
    Item* itemCatalog[SHOP_ITEM_COUNT];
};