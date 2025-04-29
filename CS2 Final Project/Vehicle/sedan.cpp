#include "Sedan.h"

Sedan::Sedan()
    : Vehicle("Sedan", 100, 100, 5, 4) {}

void Sedan::useSpecialAbility() {
    // +1 RepairKit on friendly traveler events
    // if (player.getInventory().size() < static_cast<size_t>(getCargoCapacity())) {
    //     player.addItem(new RepairKit());
    // }
}