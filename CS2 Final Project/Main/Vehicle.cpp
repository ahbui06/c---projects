#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(const string &name, int durability, int fuel, int speed, int maxCargoCapacity) : 
    name(name),
    durability(durability),
    fuel(fuel),
    speed(speed),
    cargoCapacity(0),
    maxDurability(durability),
    maxFuel(fuel),
    maxCargoCapacity(cargoCapacity),
    equippedArmorPatches(0)
{}

Vehicle::~Vehicle() { }

const string& Vehicle::getName() const {
    return name;
}

void Vehicle::setName(const string &n) {
    name = n;
}

int Vehicle::getDurability() const {
    return durability;
}

void Vehicle::setDurability(int d) {
    durability = d;
}

int Vehicle::getFuel() const {
    return fuel;
}

void Vehicle::setFuel(int f) {
    fuel = f;
}

int Vehicle::getSpeed() const {
    return speed;
}

void Vehicle::setSpeed(int s) {
    speed = s;
}

int Vehicle::getCargoCapacity() const {
    return cargoCapacity;
}

void Vehicle::setCargoCapacity(int c) {
    cargoCapacity = c;
}

int Vehicle::getMaxDurability() const {
    return maxDurability;
}

int Vehicle::getMaxFuel() const {
    return maxFuel;
}

int Vehicle::getMaxCargoCapacity() const {
    return maxCargoCapacity;
}

void Vehicle::incrementCargo() {
    if (cargoCapacity < maxCargoCapacity) {
        ++cargoCapacity;
    }
}

bool Vehicle::equipArmorPatch() {
    if (equippedArmorPatches < MAX_EQUIPPED_ARMOR) {
        ++equippedArmorPatches;
        return true;
    }
    return false;
}

bool Vehicle::hasArmorPatchEquipped() const {
    return equippedArmorPatches > 0;
}

void Vehicle::useEquippedArmorPatch() {
    if (equippedArmorPatches > 0) 
        --equippedArmorPatches;
}

int Vehicle::getEquippedArmorPatches() const {
    return equippedArmorPatches;
}

void Vehicle::applyDamage(int amount) {
    if((durability - amount) <= 0) {
        durability = 0;
    } else {
        durability -= amount;
    }
}

void Vehicle::consumeFuel(int amount) {
    if((fuel - amount) <= 0) {
        fuel = 0;
    } else {
        fuel -= amount;
    }
}

void Vehicle::useSpecialAbility(EventType ev, Player &player, int &value) {}

bool Vehicle::isDestroyed() const {
    return durability <= 0;
}

bool Vehicle::isOutOfFuel() const {
    return fuel <= 0;
}