#include "FuelCanister.h"
#include "Vehicle.h"

FuelCanister::FuelCanister()
    : Item("FuelCanister")
{ }

void FuelCanister::use(Vehicle &v) {
    v.consumeFuel(-25);
}