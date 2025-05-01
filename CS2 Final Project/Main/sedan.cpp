#include "Sedan.h"
#include "Player.h"
#include "RepairKit.h"
#include <iostream>

using namespace std;

Sedan::Sedan()
    : Vehicle("Sedan", 100, 100, 5, 4) {}

    void Sedan::useSpecialAbility(EventType ev, Player &player, int & ) {

        if (ev == EventType::FriendlyTravelers) {
            cout << "Sedan special ability! Attempting to pick up a RepairKit...\n";
            RepairKit* kit = new RepairKit();

            if (player.addItem(kit, *this)) {
                incrementCargo();
                cout << "  +1 RepairKit acquired! Cargo now "
                          << getCargoCapacity() << "/"
                          << getMaxCargoCapacity() << "\n";
            } else {
                delete kit;
                cout << "  But cargo is full ("
                          << getCargoCapacity() << "/"
                          << getMaxCargoCapacity() << ").\n";
            }
        }
    }