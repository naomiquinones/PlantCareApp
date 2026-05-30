#include <iostream>
#include <string>
#include <limits>
#include "PlantCollection.h"
#include "DatabaseHandler.h"

using namespace std;

void displayMenu();

int main() {
    DatabaseHandler db("data/plants.db");
    PlantCollection collection;
    if (!db.open()) {
        cout << "Unable to open database.\n";
    } else {
        if (!db.loadPlantTypes(collection)) {
            cout << "Failed to load plant types.\n";
        }
        if (!db.loadPlants(collection)) {
            cout << "Failed to load plants.\n";
        }
    }

    // TODO: Check for plants needing care
    // TODO: Display startup warnings for overdue plants

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            // TODO: Display plants needing water/fertilizer
        } else if (choice == 2) {
            collection.displayAll();
        } else if (choice == 3) {
            // TODO: Get plant details from user
            // TODO: Let user select or create a plant type
            // TODO: Create Plant object and save to database
        } else if (choice == 4) {
            // TODO: Get plant name from user
            // TODO: Find plant in collection
            // TODO: Show update submenu (water, fertilize, repot, prune)
            // TODO: Log care event and update plant record
        } else if (choice == 5) {
            // TODO: Get plant type details from user
            // TODO: Save custom plant type to database
        } else if (choice == 6) {
            running = false;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    db.close();
    return 0;
}

void displayMenu() {
    cout << "\n=== Plant Care App ===\n";
    cout << "1. View plants needing care\n";
    cout << "2. View all plants\n";
    cout << "3. Add a plant\n";
    cout << "4. Update plant care\n";
    cout << "5. Add custom plant type\n";
    cout << "6. Exit\n";
    cout << "Choice: ";
}