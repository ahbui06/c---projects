// =============================
// File: Player.cpp
// =============================
#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
  : currency(100), runCount(0),
    ownedVehicleCount(0), inventoryCount(0)
{ }

Player::~Player() {
    for (int i = 0; i < ownedVehicleCount; ++i) delete ownedVehicles[i];
    for (int i = 0; i < inventoryCount; ++i) delete inventory[i];
}

int  Player::getCurrency() const   { return currency; }
void Player::addCurrency(int amt)  { currency += amt; }

int  Player::getRunCount() const   { return runCount; }
void Player::incrementRunCount()   { ++runCount; }

int Player::getInventoryCount() const {
    return inventoryCount;
}

void Player::printOwnedVehicles() const {
    cout << "Owned Vehicles:\n";
    if (ownedVehicleCount == 0) {
        cout << "  None\n";
    } else {
        for (int i = 0; i < ownedVehicleCount; ++i) {
            cout << "  " << (i+1) 
                      << ": " << ownedVehicles[i]->getName() 
                      << "\n";
        }
    }
}

void Player::printInventoryItems() const {
    std::cout << "Inventory Items:\n";
    if (inventoryCount == 0) {
        cout << "  None\n";
    } else {
        for (int i = 0; i < inventoryCount; ++i) {
            cout << "  " << (i+1) 
                      << ": " << inventory[i]->getName() 
                      << "\n";
        }
    }
}

bool Player::addOwnedVehicle(Vehicle* v) {
    if (ownedVehicleCount >= MAX_VEHICLES) return false;
    ownedVehicles[ownedVehicleCount++] = v;
    return true;
}

bool Player::removeOwnedVehicle(Vehicle* v) {
    for (int i = 0; i < ownedVehicleCount; ++i) {
        if (ownedVehicles[i] == v) {
            delete v;
            for (int j = i; j < ownedVehicleCount - 1; ++j)
                ownedVehicles[j] = ownedVehicles[j+1];
            --ownedVehicleCount;
            return true;
        }
    }
    return false;
}

bool Player::addItem(Item* i) {
    if (inventoryCount >= MAX_INVENTORY) return false;
    inventory[inventoryCount++] = i;
    return true;
}

bool Player::removeItem(Item* i) {
    for (int x = 0; x < inventoryCount; ++x) {
        if (inventory[x] == i) {
            delete i;
            for (int j = x; j < inventoryCount - 1; ++j)
                inventory[j] = inventory[j+1];
            --inventoryCount;
            return true;
        }
    }
    return false;
}

bool Player::hasInventorySpace() const {
    return inventoryCount < MAX_INVENTORY;
}

Vehicle* Player::chooseVehicle() const {
    // TODO: real selection logic
    // return (ownedVehicleCount>0 ? ownedVehicles[0] : nullptr);
}

Item* Player::chooseItem() const {
    // TODO: real selection logic
    // return (inventoryCount>0 ? inventory[0] : nullptr);
}

void Player::useItem(Item* item, Vehicle& v) {
    if (!item) return;
    item->use(v);
    removeItem(item);
}

bool Player::isGameOver(int cheapestVehicleCost) const {
    return currency < cheapestVehicleCost && ownedVehicleCount == 0;
}
