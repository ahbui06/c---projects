#include "ArmorPatch.h"
#include "Vehicle.h"
#include <iostream>

using namespace std;

ArmorPatch::ArmorPatch()
    : Item("ArmorPatch")
{ }

void ArmorPatch::use(Vehicle &v) {
    if (v.equipArmorPatch()) {
        cout << "Armor patch equipped ("
                  << v.getEquippedArmorPatches() << "/"
                  << Vehicle::getMaxEquippedArmor() << ")\n";
    } else {
        cout << "Cannot equip more than "
                  << Vehicle::getMaxEquippedArmor()
                  << " patches.\n";
    }
}