#include "SportsCar.h"
#include "Player.h"

SportsCar::SportsCar()
    : Vehicle("SportsCar", 65, 50, 10, 2) {}

void SportsCar::useSpecialAbility(Player& player) {
    // Increases currency earned from smooth road events by 50% for this run
    player.addCurrency(50);
    // make sure to add the Player &player paramter to all the other special ability functions for base class and all other dervied classes
}
