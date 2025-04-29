#include "ArmorPatch.h"
#include "Vehicle.h"

ArmorPatch::ArmorPatch()
    : Item("ArmorPatch")
{ }

void ArmorPatch::use(Vehicle &v) {
    v.setDurability(v.getDurability() + 25);
}