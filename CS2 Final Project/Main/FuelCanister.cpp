#include "FuelCanister.h"
#include "Vehicle.h"

FuelCanister::FuelCanister()
    : Item("FuelCanister")
{ }

void FuelCanister::use(Vehicle &v) {
    int newFuel = v.getFuel() + 25;
    if (newFuel > v.getMaxFuel())
        newFuel = v.getMaxFuel();
    v.setFuel(newFuel);
}