#include "SportsCar.h"
#include "Player.h"

SportsCar::SportsCar()
    : Vehicle("SportsCar", 65, 50, 10, 2) {}

void SportsCar::useSpecialAbility(EventType ev, Player &player, int &value) {
    player.addCurrency(50);
}
