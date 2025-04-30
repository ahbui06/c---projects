// =============================
// File: Player.h
// =============================
#pragma once

#include "Vehicle.h"
#include "Item.h"

static const int MAX_VEHICLES   = 4;
static const int MAX_INVENTORY  = 20;

class Player {
public:
    Player();
    ~Player();

    int  getCurrency() const;
    void addCurrency(int amount);

    int  getRunCount() const;
    void incrementRunCount();

    void printOwnedVehicles() const;
    void printInventoryItems() const;

    int getInventoryCount() const;

    bool addOwnedVehicle(Vehicle* v);
    bool removeOwnedVehicle(Vehicle* v);

    bool addItem(Item* i);
    bool removeItem(Item* i);
    bool hasInventorySpace() const;

    Vehicle* chooseVehicle() const;
    Item*    chooseItem()   const;

    void useItem(Item* item, Vehicle& v);

    bool isGameOver(int cheapestVehicleCost) const;

private:
    int currency;
    int runCount;

    Vehicle* ownedVehicles[MAX_VEHICLES];
    int      ownedVehicleCount;

    Item*    inventory[MAX_INVENTORY];
    int      inventoryCount;
};
