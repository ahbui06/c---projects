#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle(const string &name, int durability, int fuel, int speed, int cargoCapacity) : 
    name(name),
    durability(durability),
    fuel(fuel),
    speed(speed),
    cargoCapacity(cargoCapacity)
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

void Vehicle::useSpecialAbility() {}

bool Vehicle::isDestroyed() const {
    return durability <= 0;
}

bool Vehicle::isOutOfFuel() const {
    return fuel <= 0;
}