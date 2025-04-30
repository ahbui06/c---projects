#include "Vehicle.h"
#include "Player.h"
#include "Buggy.h"
#include "Truck.h"
#include "Sedan.h"
#include "SportsCar.h"
#include "FuelCanister.h"
#include "RepairKit.h"
#include <cstdlib>

using namespace std;

// Generates a random event and applies its effects
void generateRandomEvent(Vehicle &vehicle, Player &player) {
    // pick one of 8 event types
    int idx = rand() % 8;
    EventType ev = static_cast<EventType>(idx);

    switch (ev) {
        case EventType::AbandonedFuelCache: {
            // +1 FuelCanister if space, then -10 fuel
            if (player.getInventoryCount() < vehicle.getCargoCapacity()) {
                player.addItem(new FuelCanister());
            }
            vehicle.consumeFuel(10);
            break;
        }
        case EventType::SmoothRoad: {
            // nothing happens, -10 fuel
            vehicle.consumeFuel(10);
            break;
        }
        case EventType::DownhillStretch: {
            // nothing happens, -5 fuel
            vehicle.consumeFuel(5);
            break;
        }
        case EventType::FriendlyTravelers: {
            // +1 RepairKit if space, then -10 fuel
            if (player.getInventoryCount() < vehicle.getCargoCapacity()) {
                player.addItem(new RepairKit());
            }
            vehicle.consumeFuel(10);
            break;
        }
        case EventType::BanditAmbush: {
            // -30 durability, -10 fuel
            vehicle.applyDamage(30);
            vehicle.consumeFuel(10);
            break;
        }
        case EventType::Obstacle: {
            // -15 durability, -10 fuel
            vehicle.applyDamage(15);
            vehicle.consumeFuel(10);
            break;
        }
        case EventType::Sandstorm: {
            // -20 fuel
            vehicle.consumeFuel(20);
            break;
        }
        case EventType::Roadblock: {
            // -10 durability, -15 fuel
            vehicle.applyDamage(10);
            vehicle.consumeFuel(15);
            break;
        }
    }
}