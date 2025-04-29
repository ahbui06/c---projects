#include "Sedan.h"
#include "Player.h"
#include "RepairKit.h"

Sedan::Sedan()
    : Vehicle("Sedan", 100, 100, 5, 4) {}

void Sedan::useSpecialAbility(Player &player) {
    // +1 RepairKit on friendly traveler events
    int currentLoad = player.getInventoryCount();
    int maxCap = getCargoCapacity();
    if (currentLoad < maxCap) {
        player.addItem(new RepairKit());
        // increase the vehicle's cargo capacity by 1
        setCargoCapacity(maxCap + 1);
    }
}