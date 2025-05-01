// Events.cpp
#include "Vehicle.h"
#include "Player.h"
#include "Buggy.h"
#include "Truck.h"
#include "Sedan.h"
#include "SportsCar.h"
#include "FuelCanister.h"
#include "RepairKit.h"
#include <iostream>
#include <cstdlib>

using namespace std;

static const char* EVENT_NAMES[] = {
    "Abandoned Fuel Cache",
    "Smooth Road",
    "Downhill Stretch",
    "Friendly Travelers",
    "Bandit Ambush",
    "Obstacle",
    "Sandstorm",
    "Roadblock"
};

void generateRandomEvent(Vehicle &vehicle, Player &player) {
    int idx = rand() % 8;  
    EventType ev = static_cast<EventType>(idx);

    // Print the event name
    cout << "\n-- Event: " << EVENT_NAMES[idx] << " --\n";

    switch (ev) {
        case EventType::AbandonedFuelCache:
            cout << "You found an abandoned fuel cache!\n";
            if (player.getInventoryCount() < vehicle.getCargoCapacity()) {
                player.addItem(new FuelCanister());
                cout << "  (+1 Fuel Canister added to inventory)\n";
            }
            vehicle.consumeFuel(10);
            break;

        case EventType::SmoothRoad:
            cout << "The road is smooth - easy cruising.\n";
            if (auto sc = dynamic_cast<SportsCar*>(&vehicle)) {
                sc->useSpecialAbility(ev, player, idx);
                cout << "  (SportsCar bonus applied)\n";
            }
            vehicle.consumeFuel(10);
            break;

        case EventType::DownhillStretch:
            cout << "A long downhill stretch!\n";
            vehicle.consumeFuel(5);
            break;

        case EventType::FriendlyTravelers:
            cout << "You meet friendly travelers.\n";
            if (player.getInventoryCount() < vehicle.getCargoCapacity()) {
                player.addItem(new RepairKit());
                cout << "  (+1 RepairKit added to inventory)\n";
            } else {
                cout << "  (Your inventory is full - no RepairKit gained)\n";
            }
            vehicle.consumeFuel(10);
            break;

        case EventType::BanditAmbush:
            cout << "Bandits ambush you!\n";
            if (vehicle.hasArmorPatchEquipped()) {
                vehicle.useEquippedArmorPatch();
                cout << "  An armor patch breaks - no damage taken!\n";
            } else {
                vehicle.applyDamage(30);
                cout << "  Vehicle takes 30 damage.\n";
            }
            vehicle.consumeFuel(10);
            break;

        case EventType::Obstacle:
            cout << "You hit an obstacle.\n";
            if (vehicle.hasArmorPatchEquipped()) {
                vehicle.useEquippedArmorPatch();
                cout << "  An armor patch breaks - no damage taken!\n";
            } else {
                vehicle.applyDamage(15);
                cout << "  Vehicle takes 15 damage.\n";
            }
            vehicle.consumeFuel(10);
            break;

        case EventType::Sandstorm:
            cout << "A fierce sandstorm batters you.\n";
            vehicle.consumeFuel(20);
            break;

        case EventType::Roadblock:
            cout << "A roadblock damages you.\n";
            if (vehicle.hasArmorPatchEquipped()) {
                vehicle.useEquippedArmorPatch();
                cout << "  An armor patch breaks - no damage taken!\n";
            } else {
                vehicle.applyDamage(10);
                cout << "  Vehicle takes 10 damage.\n";
            }
            vehicle.consumeFuel(15);
            break;
    }
}
