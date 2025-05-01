// Main.cpp
#include "Player.h"
#include "Shop.h"
#include "Vehicle.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

// forward declaration of the event generator
void generateRandomEvent(Vehicle &vehicle, Player &player);

using namespace std;

int main() {
    // 1) Seed RNG
    srand(static_cast<unsigned>(time(nullptr)));

    // 2) Create player and shopp
    Player player;
    Shop   shop;

    // 3) Main menu
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
            break;  // start fresh
        }
        else if (menuChoice == 2) {
            // TODO: implement loadSavedGame(player);
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

    // 4) Game loop
    while (true) {
        // --- Ensure the player has a vehicle ---
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

        // --- Before‐run menu ---
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
                 << "Enter choice: ";
            int preChoice;
            cin >> preChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (preChoice == 1) {
                // Shop flow
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
                // Inventory flow
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
                // Start the run
                break;
            }
            else if (preChoice == 4) {
                // TODO: implement saveGame(player);
                cout << "Game saved (placeholder).\n";
            }
            else if (preChoice == 5) {
                cout << "Exiting game. Goodbye!\n";
                return 0;
            }
            else {
                cout << "Invalid choice. Please enter 1–5.\n";
            }
        }

        // --- Record starting stats ---
        int startDurability = current->getDurability();
        int startFuel       = current->getFuel();

        // --- Run random events ---
        int numEvents = rand() % 5 + 1;  // between 1 and 10
        for (int i = 0; i < numEvents; ++i) {
            // 1) Fire the event
            generateRandomEvent(*current, player);

            // 2) Show stats after the event
            cout << "  [After event " << (i+1) << "] "
                << "Durability: " << current->getDurability()
                << ", Fuel: "      << current->getFuel() << "\n";

            // 3) Allow mid‐run item use
            if (player.getInventoryCount() > 0) {
                cout << "Use an item? (1=yes, 0=no): ";
                int useIt; 
                cin >> useIt; 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (useIt == 1) {
                    Item* it = player.chooseItem();
                    player.useItem(it, *current);

                    // 4) Show stats again if they used an item
                    cout << "    [After using item] "
                        << "Durability: " << current->getDurability()
                        << ", Fuel: "      << current->getFuel() << "\n";
                }
            }

    // 5) Stop early if vehicle is gone
    if (current->isDestroyed() || current->isOutOfFuel())
        break;
}

        // --- Post‐run resolution ---
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

        // --- Game-over check ---
        const int CHEAPEST = 100;  // match your cheapest vehicle price
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
                player = Player();      // re-initialize currency, runs, inventory, vehicles
                cout << "\n*** Starting a new game! ***\n\n";
                continue;               // jump back to the top of the game loop
            } else {
                cout << "Thanks for playing!\n";
                break;                  // exit main game loop and end program
            }
        }
    }
    return 0;
}
