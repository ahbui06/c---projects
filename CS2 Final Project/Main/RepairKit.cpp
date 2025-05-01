#include "RepairKit.h"
#include "Vehicle.h"

RepairKit::RepairKit()
    : Item("RepairKit")
{ }

void RepairKit::use(Vehicle &v) {
    int newDur = v.getDurability() + 25;
    if (newDur > v.getMaxDurability())
        newDur = v.getMaxDurability();
    v.setDurability(newDur);
}