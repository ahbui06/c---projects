// Main.cpp
#include "Player.h"
#include "Shop.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateRandomEvent(Vehicle &vehicle, Player &player);

int main() {
    // Seed the RNG once
    srand(static_cast<unsigned>(time(nullptr)));

    // Create player and shop
    Player player;
    Shop   shop;

    // Main menu before starting or loading a game
    while (true) {
        cout << "=== Welcome to Wasteland Runners! ===\n";
        cout << "1) Start New Game\n";
        cout << "2) Load Saved Game\n";
        cout << "3) Exit\n";
        cout << "Enter choice: ";

        int menuChoice;
        cin >> menuChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (menuChoice == 1) {
            // Start a fresh game
            break;
        }
        else if (menuChoice == 2) {
            // TODO: implement loadSavedGame(player);
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

    // Begin game loop
    while (true) {
        // Ensure the player has at least one vehicle
        Vehicle* current = player.chooseVehicle();
        if (!current) {
            cout << "\nNo vehicles owned. Visit shop:\n";
            shop.displayVehicles();
            cout << "Select vehicle to purchase (1-" << SHOP_VEHICLE_COUNT << "): ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            shop.purchaseVehicle(choice, player);
            continue;
        }

        // Before-run menu
        while (true) {
            cout << "\n--- Ready for your next run? ---\n"
                 << "1) Visit Shop\n"
                 << "2) Open Inventory\n"
                 << "3) Start Run\n"
                 << "Enter choice: ";
            int preChoice;
            cin >> preChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (preChoice == 1) {
                // Shop flow
                shop.displayVehicles();
                cout << "Buy vehicle (1-" << SHOP_VEHICLE_COUNT << ") or 0 to skip: ";
                int vix; cin >> vix;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (vix > 0) shop.purchaseVehicle(vix, player);

                shop.displayItems();
                cout << "Buy item (1-" << SHOP_ITEM_COUNT << ") or 0 to skip: ";
                int iix; cin >> iix;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (iix > 0) shop.purchaseItem(iix, player);
            }
            else if (preChoice == 2) {
                // Inventory flow
                cout << "\n--- Inventory ---\n";
                player.printInventoryItems();
                if (player.getInventoryCount() > 0) {
                    cout << "Use an item now? (1=yes, 0=no): ";
                    int useIt; cin >> useIt;
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
            else {
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            }
        }

        // Run random events
        int numEvents = rand() % 10 + 1;  // between 1 and 10
        for (int i = 0; i < numEvents; ++i) {
            generateRandomEvent(*current, player);

            // Allow mid-run item use
            if (player.getInventoryCount() > 0) {
                cout << "Use an item? (1=yes, 0=no): ";
                int useIt; cin >> useIt;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (useIt == 1) {
                    Item* it = player.chooseItem();
                    player.useItem(it, *current);
                }
            }

            if (current->isDestroyed() || current->isOutOfFuel())
                break;
        }

        // Post-run resolution
        if (!current->isDestroyed() && !current->isOutOfFuel()) {
            int reward = 100; // TODO: replace with computeReward(current)
            player.addCurrency(reward);
            cout << "Run successful! Earned " << reward << " currency.\n";
        } else {
            cout << "Your vehicle was lost!\n";
            player.removeOwnedVehicle(current);
        }
        player.incrementRunCount();

        // Game-over check
        const int CHEAPEST = 100; // match your cheapest vehicle price
        if (player.isGameOver(CHEAPEST)) {
            cout << "\nGame Over! You survived "
                 << player.getRunCount() << " runs.\n";
            break;
        }
    }

    return 0;
}
