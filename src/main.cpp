#include <iostream>
#include <string>
#include "PlantCollection.h"
#include "DatabaseHandler.h"

using namespace std;

void displayMenu();

int main() {
    DatabaseHandler db("data/plants.db");

    // TODO: Open database connection
    // TODO: Initialize database if first run
    // TODO: Load plant types into collection
    // TODO: Load plants into collection

    PlantCollection collection;

    Plant* plant1 = new Plant();
    plant1->setCommonName("Snake Plant");
    plant1->setScientificName("Dracaena trifasciata");
    plant1->setLastWatered("2026-05-20");
    plant1->setPotSize("8 inch");

    Plant* plant2 = new Plant();
    plant2->setCommonName("Pothos");
    plant2->setScientificName("Epipremnum aureum");
    plant2->setLastWatered("2026-05-23");
    plant2->setPotSize("6 inch");

    collection.addPlant(plant1);
    collection.addPlant(plant2);

    // TODO: Check for plants needing care
    // TODO: Display startup warnings for overdue plants

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;

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

    // TODO: Close database connection
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