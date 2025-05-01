
#pragma once

#include "Vehicle.h"
#include "Item.h"

static const int MAX_VEHICLES   = 4;
static const int MAX_INVENTORY  = 5;

class Player {
public:
    Player();
    ~Player();

    int getCurrency() const;
    void addCurrency(int amount);

    int getRunCount() const;
    void incrementRunCount();

    void setCurrency(int c);
    void setRunCount(int r);

    void printOwnedVehicles() const;
    void printInventoryItems() const;

    int getInventoryCount() const;

    bool addOwnedVehicle(Vehicle* v);
    bool removeOwnedVehicle(Vehicle* v);
    int getOwnedVehicleCount() const;

    Vehicle* getOwnedVehicle(int index) const;
    Item* getInventoryItem(int index) const;


    bool addItem(Item* i, Vehicle &v);
    bool removeItem(Item* i);
    bool hasInventorySpace(int vehicleMaxCargo) const {
        return inventoryCount < vehicleMaxCargo;
    }    

    Vehicle* chooseVehicle() const;
    Item* chooseItem() const;

    void useItem(Item* item, Vehicle& v);

    bool isGameOver(int cheapestVehicleCost) const;

    void clearAllVehicles();
    void clearAllItems();

private:
    int currency;
    int runCount;

    Vehicle* ownedVehicles[MAX_VEHICLES];
    int ownedVehicleCount;

    Item* inventory[MAX_INVENTORY];
    int inventoryCount;
};
