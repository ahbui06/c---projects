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
    cout << "\n--- Vehicles for Sale ---\n";
    cout << "1) Buggy     -- Price: 100\n"
         << "2) Truck     -- Price: 1250\n"
         << "3) Sedan     -- Price: 500\n"
         << "4) SportsCar -- Price: 1000\n";
}

void Shop::displayItems() const {
    cout << "\n--- Items for Sale ---\n";
    cout << "1) RepairKit    -- Price: 100\n"
         << "2) FuelCanister -- Price: 50\n"
         << "3) ArmorPatch   -- Price: 150\n";
}

bool Shop::purchaseVehicle(int index, Player &player) {
    if (index < 1 || index > SHOP_VEHICLE_COUNT) {
        cout << "Invalid vehicle choice.\n";
        return false;
    }
    int price = 0;
    switch (index) {
        case 1: price = 100;  break;  // Buggy
        case 2: price = 1250; break;  // Truck
        case 3: price = 500;  break;  // Sedan
        case 4: price = 1000; break;  // SportsCar
    }
    if (player.getCurrency() < price) {
        cout << "Not enough currency to buy that vehicle.\n";
        return false;
    }
    player.addCurrency(-price);
    Vehicle *v = nullptr;
    switch (index) {
      case 1: v = new Buggy();     break;
      case 2: v = new Truck();     break;
      case 3: v = new Sedan();     break;
      case 4: v = new SportsCar(); break;
    }
    player.addOwnedVehicle(v);
    cout << "Purchased " << v->getName() << " for " << price << " currency.\n";
    return true;
}

bool Shop::purchaseItem(int index, Player &player) {
    if (index < 1 || index > SHOP_ITEM_COUNT) {
        cout << "Invalid item choice.\n";
        return false;
    }
    Vehicle *current = player.chooseVehicle();
    if (!current) {
        cout << "You need a vehicle to carry items!\n";
        return false;
    }
    int cap = current->getMaxCargoCapacity();
    if (!player.hasInventorySpace(cap)) {
        cout << "Inventory is full for your "
             << current->getName() << " (max " << cap << ").\n";
        return false;
    }

    int price = 0;
    Item *it   = nullptr;
    switch (index) {
      case 1: price = 100; it = new RepairKit();    break;
      case 2: price = 50; it = new FuelCanister(); break;
      case 3: price = 150; it = new ArmorPatch();   break;
    }
    if (player.getCurrency() < price) {
        cout << "Not enough currency to buy that item.\n";
        delete it;
        return false;
    }

    player.addCurrency(-price);
    if (player.addItem(it, *current)) {
        current->incrementCargo();
    } else {
        delete it;  // drop it if no space
        cout << "No cargo space!\n";
    }
    // tell the vehicle you’re now carrying one more
    current->incrementCargo();

    cout << "Purchased " << it->getName()
         << " for " << price << " currency. "
         << "Cargo: " << current->getCargoCapacity()
         << " / " << cap << "\n";
    return true;
}