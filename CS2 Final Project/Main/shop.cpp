#include "Shop.h"
#include "Buggy.h"
#include "Truck.h"
#include "Sedan.h"
#include "SportsCar.h"
#include "RepairKit.h"
#include "FuelCanister.h"
#include "ArmorPatch.h"
#include "Player.h"
#include <iostream>

using namespace std;

Shop::Shop() {
    vehicleCatalog[0] = new Buggy();
    vehicleCatalog[1] = new Truck();
    vehicleCatalog[2] = new Sedan();
    vehicleCatalog[3] = new SportsCar();

    itemCatalog[0] = new RepairKit();
    itemCatalog[1] = new FuelCanister();
    itemCatalog[2] = new ArmorPatch();
}

Shop::~Shop() {
    for (int i = 0; i < SHOP_VEHICLE_COUNT; ++i)
        delete vehicleCatalog[i];
    for (int i = 0; i < SHOP_ITEM_COUNT; ++i)
        delete itemCatalog[i];
}

void Shop::displayVehicles() const {
    cout << "--- Vehicles for Sale ---";
    for (int i = 0; i < SHOP_VEHICLE_COUNT; ++i) {
        const auto *v = vehicleCatalog[i];
        std::cout << (i+1) << ") " << v->getName()
                  << " -- Price: " << 50 << "";
    }
}

void Shop::displayItems() const {
    cout << "--- Items for Sale ---";
    for (int i = 0; i < SHOP_ITEM_COUNT; ++i) {
        const auto *it = itemCatalog[i];
        cout << (i+1) << ") " << it->getName()
                  << " -- Price: " << 25 << "";
    }
}

bool Shop::purchaseVehicle(int index, Player &player) {
    if (index < 1 || index > SHOP_VEHICLE_COUNT) return false;
    Vehicle *prototype = vehicleCatalog[index-1];
    int price = 50; // TODO: use getPrice()
    if (player.getCurrency() >= price) {
        player.addCurrency(-price);
        // Clone the prototype (shallow copy)
        player.addOwnedVehicle(new Vehicle(*prototype));
        return true;
    }
    return false;
}

bool Shop::purchaseItem(int index, Player &player) {
    if (index < 1 || index > SHOP_ITEM_COUNT) return false;
    Item *prototype = itemCatalog[index-1];
    int price = 25; // TODO: use getPrice()
    if (player.getCurrency() >= price && player.hasInventorySpace()) {
        player.addCurrency(-price);
        // Clone the prototype (shallow copy)
        player.addItem(new Item(*prototype));
        return true;
    }
    return false;
}