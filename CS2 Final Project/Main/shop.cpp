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
    std::cout << "--- Vehicles for Sale ---\n";
    for (int i = 0; i < SHOP_VEHICLE_COUNT; ++i) {
        const auto *v = vehicleCatalog[i];
        int price = 0;
        switch (i+1) {
            case 1: price = 100;  break;  // Buggy
            case 2: price = 1250; break;  // Truck
            case 3: price = 500;  break;  // Sedan
            case 4: price = 1000; break;  // SportsCar
        }
        std::cout << (i+1) << ") " << v->getName()
                  << " -- Price: " << price << "\n";
    }
}

void Shop::displayItems() const {
    std::cout << "--- Items for Sale ---\n";
    for (int i = 0; i < SHOP_ITEM_COUNT; ++i) {
        const auto *it = itemCatalog[i];
        int price = 0;
        switch (i+1) {
            case 1: price = 250; break; // RepairKit
            case 2: price = 200; break; // FuelCanister
            case 3: price = 300; break; // ArmorPatch
        }
        std::cout << (i+1) << ") " << it->getName()
                  << " -- Price: " << price << "\n";
    }
}

bool Shop::purchaseVehicle(int index, Player &player) {
    if (index < 1 || index > SHOP_VEHICLE_COUNT) return false;
    int price = 0;
    switch (index) {
        case 1: price = 100;  break;  // Buggy
        case 2: price = 1250; break;  // Truck
        case 3: price = 500;  break;  // Sedan
        case 4: price = 1000; break;  // SportsCar
    }
    if (player.getCurrency() >= price) {
        player.addCurrency(-price);
        Vehicle *v = nullptr;
        switch (index) {
            case 1: v = new Buggy();    break;
            case 2: v = new Truck();    break;
            case 3: v = new Sedan();    break;
            case 4: v = new SportsCar(); break;
        }
        if (v) {
            player.addOwnedVehicle(v);
            return true;
        }
    }
    return false;
}

bool Shop::purchaseItem(int index, Player &player) {
    if (index < 1 || index > SHOP_ITEM_COUNT) return false;
    int price = 0;
    switch (index) {
        case 1: price = 250; break; // RepairKit
        case 2: price = 200; break; // FuelCanister
        case 3: price = 300; break; // ArmorPatch
    }
    if (player.getCurrency() >= price && player.hasInventorySpace()) {
        player.addCurrency(-price);
        Item *it = nullptr;
        switch (index) {
            case 1: it = new RepairKit();    break;
            case 2: it = new FuelCanister(); break;
            case 3: it = new ArmorPatch();   break;
        }
        if (it) {
            player.addItem(it);
            return true;
        }
    }
    return false;
}