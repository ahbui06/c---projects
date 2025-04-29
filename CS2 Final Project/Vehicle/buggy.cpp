#include "Buggy.h"

Buggy::Buggy()
    : Vehicle("Buggy", 75, 75, 7, 3) {}

void Buggy::useSpecialAbility() {
    // Reduces rough terrain effects by 50% for this run
    setDurability(getDurability() + 5);
    setFuel(getFuel() + 8);
}