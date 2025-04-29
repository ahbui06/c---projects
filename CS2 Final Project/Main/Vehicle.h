#pragma once
#include <string>

using namespace std;

class Player;

class Vehicle {
    public:
        Vehicle(const string &name, int durability, int fuel, int speed, int cargoCapacity);
        virtual ~Vehicle();

        const string& getName() const;
        void setName(const string &name);

        int getDurability() const;
        void setDurability(int durability);

        int getFuel() const;
        void setFuel(int fuel);

        int getSpeed() const;
        void setSpeed(int speed);

        int getCargoCapacity() const;
        void setCargoCapacity(int cargoCapacity);

        void applyDamage(int amount);
        void consumeFuel(int amount);

        virtual void useSpecialAbility(Player &player);

        bool isDestroyed() const;
        bool isOutOfFuel() const;
    private:
        string name;
        int durability;
        int fuel;
        int speed;
        int cargoCapacity;
};