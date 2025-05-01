#include "Truck.h"

Truck::Truck()
    : Vehicle("Truck", 125, 125, 3, 5) {}

void Truck::useSpecialAbility(EventType ev, Player &player, int &value) {
    setDurability(getDurability() + 15);
    setFuel(getFuel() + 5);
}