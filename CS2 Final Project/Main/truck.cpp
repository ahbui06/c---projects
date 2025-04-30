#include "Truck.h"

Truck::Truck()
    : Vehicle("Truck", 125, 125, 3, 5) {}

void Truck::useSpecialAbility(EventType ev, Player &player, int &value) {
    // Reduces bandit ambush damage by 50% for this run
    setDurability(getDurability() + 15);
    setFuel(getFuel() + 5);
}