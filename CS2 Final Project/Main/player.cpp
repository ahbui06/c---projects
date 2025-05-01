
#include "Player.h"
#include <iostream>
#include <limits>

using namespace std;

Player::Player()
  : currency(100), runCount(0),
    ownedVehicleCount(0), inventoryCount(0)
{ }

Player::~Player() {
    for (int i = 0; i < ownedVehicleCount; ++i) delete ownedVehicles[i];
    for (int i = 0; i < inventoryCount; ++i) delete inventory[i];
}

int Player::getCurrency() const   { return currency; }
void Player::addCurrency(int amt)  { currency += amt; }

int Player::getRunCount() const   { return runCount; }
void Player::incrementRunCount()   { ++runCount; }

void Player::setCurrency(int c) {
    currency = c;
}

void Player::setRunCount(int r) {
    runCount = r;
}

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
    cout << "Inventory Items:\n";
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

int Player::getOwnedVehicleCount() const {
    return ownedVehicleCount;
}

Vehicle* Player::getOwnedVehicle(int index) const {
    return ownedVehicles[index];
}

Item* Player::getInventoryItem(int index) const {
    return inventory[index];
  }

bool Player::addItem(Item* i, Vehicle &v) {
    if (!hasInventorySpace(v.getMaxCargoCapacity())) return false;
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


Vehicle* Player::chooseVehicle() const {
    printOwnedVehicles();
    if (ownedVehicleCount == 0) 
        return nullptr;

    int choice = 0;
    cout << "Choose vehicle to equip (1-" << ownedVehicleCount << "): ";
    while (!(cin >> choice) || choice < 1 || choice > ownedVehicleCount) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //basically clears anything that isnt 1-4 in the buffer.. used pretty much everywhere lol... reason why no endl;
        cout << "Invalid. Enter a number between 1 and " 
             << ownedVehicleCount << ": ";
    }
    return ownedVehicles[choice - 1];
}

Item* Player::chooseItem() const {
    printInventoryItems();
    if (inventoryCount == 0) 
        return nullptr;

    int choice = 0;
    cout << "Choose item to use (1-" << inventoryCount << "): ";
    while (!(cin >> choice) || choice < 1 || choice > inventoryCount) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //basically clears anything that isnt 1-4 in the buffer
        cout << "Invalid. Enter a number between 1 and " 
             << inventoryCount << ": ";
    }
    return inventory[choice - 1];
}

void Player::useItem(Item* item, Vehicle& v) {
    if (!item) return;
    item->use(v);
    removeItem(item);
}

bool Player::isGameOver(int cheapestVehicleCost) const {
    return currency < cheapestVehicleCost && ownedVehicleCount == 0;
}

void Player::clearAllVehicles() {
    while (ownedVehicleCount > 0) {
        delete ownedVehicles[--ownedVehicleCount];
    }
}

void Player::clearAllItems() {
    while (inventoryCount > 0) {
        delete inventory[--inventoryCount];
    }
}
