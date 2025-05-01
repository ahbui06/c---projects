#include "Buggy.h"

Buggy::Buggy()
    : Vehicle("Buggy", 75, 75, 7, 3) {}

void Buggy::useSpecialAbility(EventType ev, Player &player, int &value) {
    setDurability(getDurability() + 5);
    setFuel(getFuel() + 8);
}