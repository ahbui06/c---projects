
#include "Player.h"
#include "Shop.h"
#include "Vehicle.h"
#include "Buggy.h"
#include "Truck.h"
#include "Sedan.h"
#include "SportsCar.h"
#include "RepairKit.h"
#include "FuelCanister.h"
#include "ArmorPatch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <fstream>
#include <string>

void generateRandomEvent(Vehicle &vehicle, Player &player);

using namespace std;

void loadGame(Player &player,
    const string &filename = "save.txt")
{
    ifstream in(filename);
    if (!in.is_open()) {
        cout << "Error: could not open `" << filename << "` for reading\n";
        return;
    }

    player.clearAllItems();
    player.clearAllVehicles();

    int currency, runs;
    in >> currency >> runs;
    player.setCurrency(currency);
    player.setRunCount(runs);

    int numV;
    in >> numV;
    for (int i = 0; i < numV; ++i) {
    string name;
    int dur, fuel;
    in >> name >> dur >> fuel;

    Vehicle* v = nullptr;
    if (name == "Buggy")       v = new Buggy();
    else if (name == "Truck")  v = new Truck();
    else if (name == "Sedan")  v = new Sedan();
    else if (name == "SportsCar") v = new SportsCar();

    if (v) {
        v->setDurability(dur);
        v->setFuel(fuel);
        player.addOwnedVehicle(v);
        }
    }

    int numI;
    in >> numI;
    for (int i = 0; i < numI; ++i) {
        string iname;
        in >> iname;

        Item* it = nullptr;
        if      (iname == "RepairKit")    it = new RepairKit();
        else if (iname == "FuelCanister") it = new FuelCanister();
        else if (iname == "ArmorPatch")   it = new ArmorPatch();

        if (it) {
            Vehicle* v = player.getOwnedVehicle(0);
            if (player.addItem(it, *v)) {
                v->incrementCargo();
            } else {
                delete it;
            }
        }
    }

    cout << "Game loaded from " << filename
        << " (Currency: " << player.getCurrency()
        << ", Runs: "   << player.getRunCount() << ")\n";
}

void saveGame(const Player &player,
    const string &filename = "save.txt")
{
    ofstream out(filename);
    if (!out.is_open()) {
        cout << "Error: could not open `" << filename << "` for writing\n";
        return;
    }

    out << player.getCurrency() << ' '
    << player.getRunCount()  << '\n';

    int vc = player.getOwnedVehicleCount();
    out << vc << '\n';
    for (int i = 0; i < vc; ++i) {
        Vehicle *v = player.getOwnedVehicle(i);
        out << v->getName()       << ' '
        << v->getDurability() << ' '
        << v->getFuel()       << '\n';
    }

    int ic = player.getInventoryCount();
    out << ic << '\n';
    for (int i = 0; i < ic; ++i) {
        Item *it = player.getInventoryItem(i);
        out << it->getName() << '\n';
    }
}

int main() {

    srand(static_cast<unsigned>(time(nullptr)));

    Player player;
    Shop   shop;

    while (true) {
        cout << "=== Welcome to Wasteland Runners! ===\n"
             << "1) Start New Game\n"
             << "2) Load Saved Game\n"
             << "3) Exit\n"
             << "Enter choice: ";
        int menuChoice;
        cin >> menuChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (menuChoice == 1) {
            break;
        }
        else if (menuChoice == 2) {
            loadGame(player);
            cout << "Load saved game (placeholder).\n";
            break;
        }
        else if (menuChoice == 3) {
            cout << "Goodbye!\n";
            return 0;
        }
        else {
            cout << "Invalid choice. Please enter 1, 2, or 3.\n\n";
        }
    }

    while (true) {

        Vehicle* current = player.chooseVehicle();
        if (!current) {
            cout << "\nNo vehicles owned. Visit shop:\n";
            cout << "\nCurrency: " << player.getCurrency() << "\n";
            shop.displayVehicles();
            cout << "Select vehicle to purchase (1-" << SHOP_VEHICLE_COUNT << "): ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            shop.purchaseVehicle(choice, player);
            continue;
        }

        while (true) {
            cout << "\nCurrency: " << player.getCurrency() << "\n";
            cout << "Equipped: " << current->getName()
                << " | Durability: " << current->getDurability()
                << " / " << current->getMaxDurability()
                << " | Fuel: "       << current->getFuel()
                << " / " << current->getMaxFuel()
                << "\n";
            cout << "\nCurrency: " << player.getCurrency() << "\n";
            cout << "\n--- Ready for your next run? ---\n"
                 << "1) Visit Shop\n"
                 << "2) Open Inventory\n"
                 << "3) Start Run\n"
                 << "4) Save Game\n"
                 << "5) Exit Game\n"
                 << "6) Equip Vehicle\n"
                 << "Enter choice: ";
            int preChoice;
            cin >> preChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (preChoice == 1) {

                shop.displayVehicles();
                cout << "Buy vehicle (1-" << SHOP_VEHICLE_COUNT << ") or 0 to skip: ";
                int vix; 
                cin >> vix; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (vix > 0) shop.purchaseVehicle(vix, player);

                shop.displayItems();
                cout << "Buy item (1-" << SHOP_ITEM_COUNT << ") or 0 to skip: ";
                int iix; 
                cin >> iix; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (iix > 0) shop.purchaseItem(iix, player);
            }
            else if (preChoice == 2) {

                cout << "\n--- Inventory ---\n";
                player.printInventoryItems();
                if (player.getInventoryCount() > 0) {
                    cout << "Use an item now? (1=yes, 0=no): ";
                    int useIt; 
                    cin >> useIt; 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (useIt == 1) {
                        Item* it = player.chooseItem();
                        player.useItem(it, *current);
                    }
                }
            }
            else if (preChoice == 3) {
                break;
            }
            else if (preChoice == 4) {
                saveGame(player);
                cout << "Game saved to save.txt.\n";
            }
            else if (preChoice == 5) {
                cout << "Exiting game. Goodbye!\n";
                return 0;
            }
            else if (preChoice == 6) {
                int count = player.getOwnedVehicleCount();
                if (count == 0) {
                    cout << "You don’t own any vehicles yet!\n";
                } else {
                    cout << "\n--- Equip a Vehicle ---\n";
                    player.printOwnedVehicles();
                    cout << "Select (1-" << count << "): ";
                    int vix;
                    cin >> vix;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (vix >= 1 && vix <= count) {
                        current = player.getOwnedVehicle(vix - 1);
                        cout << current->getName() << " equipped.\n";
                    } else {
                        cout << "Invalid selection.\n";
                    }
                }
            }
            else {
                cout << "Invalid choice. Please enter 1–5.\n";
            }
        }

        int startDurability = current->getDurability();
        int startFuel       = current->getFuel();

        int numEvents = rand() % 5 + 1; //max amnt of events is 5
        for (int i = 0; i < numEvents; ++i) {

            generateRandomEvent(*current, player);

            cout << "  [After event " << (i+1) << "] "
                << "Durability: " << current->getDurability()
                << ", Fuel: "      << current->getFuel() << "\n";

            if (player.getInventoryCount() > 0) {
                cout << "Use an item? (1=yes, 0=no): ";
                int useIt; 
                cin >> useIt; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (useIt == 1) {
                    Item* it = player.chooseItem();
                    player.useItem(it, *current);

                    cout << "    [After using item] "
                        << "Durability: " << current->getDurability()
                        << ", Fuel: "      << current->getFuel() << "\n";
                }
            }

    if (current->isDestroyed() || current->isOutOfFuel())
        break;
}

        int currDur   = current->getDurability();
        int currFuel  = current->getFuel();
        int maxDur    = current->getMaxDurability();
        int maxFuel   = current->getMaxFuel();

        cout << "\nRun complete!\n"
             << "Durability: " << currDur  << " / " << maxDur  << "\n"
             << "Fuel:       " << currFuel << " / " << maxFuel << "\n";

        if (!current->isDestroyed() && !current->isOutOfFuel()) {
            int reward = numEvents * 50;
            player.addCurrency(reward);
            cout << "Run successful! Earned " << reward << " currency.\n";
        } else {
            cout << "Your vehicle was lost!\n";
            player.removeOwnedVehicle(current);
        }
        player.incrementRunCount();

        const int CHEAPEST = 100;
        if (player.isGameOver(CHEAPEST)) {
            cout << "\nGame Over! You survived "
                << player.getRunCount() << " runs.\n"
                << "1) Quit\n"
                << "2) Start Again\n"
                << "Enter choice: ";
            int endChoice;
            cin >> endChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (endChoice == 2) {
                // Reset the player for a new game
                player = Player();      
                cout << "\n*** Starting a new game! ***\n\n";
                continue;               
            } else {
                cout << "Thanks for playing!\n";
                break;                  
            }
        }
    }
    return 0;
}
