#pragma once
#include <string>

using namespace std;

class Player;

enum class EventType {
    AbandonedFuelCache,
    SmoothRoad,
    DownhillStretch,
    FriendlyTravelers,
    BanditAmbush,
    Obstacle,
    Sandstorm,
    Roadblock
};

class Vehicle {
    public:
        Vehicle(const string &name, int durability, int fuel, int speed, int maxCargo);
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

        int getMaxDurability() const;
        int getMaxFuel() const;
        int getMaxCargoCapacity() const;
        void incrementCargo();
        bool canTakeOneMore() const;

        bool equipArmorPatch();
        bool hasArmorPatchEquipped() const;
        void useEquippedArmorPatch();
        int  getEquippedArmorPatches() const;
        static int getMaxEquippedArmor() { return MAX_EQUIPPED_ARMOR; }

        void applyDamage(int amount);
        void consumeFuel(int amount);

        virtual void useSpecialAbility(EventType ev, Player &player, int &value);

        bool isDestroyed() const;
        bool isOutOfFuel() const;
    private:
        string name;
        int durability;
        int fuel;
        int speed;
        int cargoCapacity;
        int maxDurability;
        int maxFuel;
        int maxCargoCapacity;
        int equippedArmorPatches;
        static constexpr int MAX_EQUIPPED_ARMOR = 3;
};