#include "Player.h"
#include <iostream>

Player::Player()
    : currency(100), runCount(0), ownedVehicleCount(0), inventoryCount(0)
{ }

Player::~Player() {
    for (int i = 0; i < ownedVehicleCount; ++i)
        delete ownedVehicles[i];
    for (int i = 0; i < inventoryCount; ++i)
        delete inventory[i];
}

int Player::getCurrency() const {
    return currency;
}

void Player::addCurrency(int amount) {
    currency += amount;
}

int Player::getRunCount() const {
    return runCount;
}

void Player::incrementRunCount() {
    ++runCount;
}

int Player::getOwnedVehicleCount() const {
    return ownedVehicleCount;
}

Vehicle* Player::getOwnedVehicle(int index) const {
    if (index >= 0 && index < ownedVehicleCount)
        return ownedVehicles[index];
    return nullptr;
}

bool Player::addOwnedVehicle(Vehicle* v) {
    if (ownedVehicleCount >= MAX_VEHICLES) return false;
    ownedVehicles[ownedVehicleCount++] = v;
    return true;
}

bool Player::removeOwnedVehicle(Vehicle* v) {
    for (int i = 0; i < ownedVehicleCount; ++i) {
        if (ownedVehicles[i] == v) {
            delete ownedVehicles[i];
            for (int j = i; j < ownedVehicleCount - 1; ++j)
                ownedVehicles[j] = ownedVehicles[j + 1];
            --ownedVehicleCount;
            return true;
        }
    }
    return false;
}

int Player::getInventoryCount() const {
    return inventoryCount;
}

Item* Player::getInventoryItem(int index) const {
    if (index >= 0 && index < inventoryCount)
        return inventory[index];
    return nullptr;
}

bool Player::addItem(Item* item) {
    if (inventoryCount >= MAX_INVENTORY) return false;
    inventory[inventoryCount++] = item;
    return true;
}

bool Player::removeItem(Item* item) {
    for (int i = 0; i < inventoryCount; ++i) {
        if (inventory[i] == item) {
            delete inventory[i];
            for (int j = i; j < inventoryCount - 1; ++j)
                inventory[j] = inventory[j + 1];
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
    if (ownedVehicleCount == 0) return nullptr;
    return ownedVehicles[0];
}

Item* Player::chooseItem() const {
    if (inventoryCount == 0) return nullptr;
    return inventory[0];
}

void Player::useItem(Item* item, Vehicle& vehicle) {
    if (!item) return;
    item->use(vehicle);
    removeItem(item);
}

bool Player::isGameOver(int cheapestVehicleCost) const {
    return currency < cheapestVehicleCost && ownedVehicleCount == 0;
}