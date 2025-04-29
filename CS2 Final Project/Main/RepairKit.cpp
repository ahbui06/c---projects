#include "RepairKit.h"
#include "Vehicle.h"

RepairKit::RepairKit()
    : Item("RepairKit")
{ }

void RepairKit::use(Vehicle &v) {
    v.applyDamage(-25);
}