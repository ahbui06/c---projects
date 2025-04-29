#include "Truck.h"

Truck::Truck()
    : Vehicle("Truck", 125, 125, 3, 5) {}

void Truck::useSpecialAbility() {
    // Reduces bandit ambush damage by 50% for this run
    setDurability(getDurability() + 15);
    setFuel(getFuel() + 5);
}