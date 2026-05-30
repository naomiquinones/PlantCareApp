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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string commonName;
            cout << "Enter the plant's common name: ";
            getline(cin, commonName);

            string scientificName;
            cout << "Enter the plant's scientific name: ";
            getline(cin, scientificName);

            string lastWatered;
            cout << "Enter the date the plant was last watered (YYYY-MM-DD). If never watered, or you don't know, leave blank: ";
            getline(cin, lastWatered);

            string lastFertilized;
            cout << "Enter the date the plant was last fertilized (YYYY-MM-DD). If never fertilized, or you don't know, leave blank: ";
            getline(cin, lastFertilized);

            string potSize;
            cout << "Enter the size of the pot the plant is in (Small, Medium, Large). If you don't know, leave blank: ";
            getline(cin, potSize);

            string rootboundStr;
            cout << "Is the plant rootbound? (y/n): ";
            getline(cin, rootboundStr);
            bool rootbound = (rootboundStr == "y" || rootboundStr == "Y");

            string notes;
            cout << "Enter any notes about the plant: ";
            getline(cin, notes);

            Plant* newPlant = new Plant();
            newPlant->setCommonName(commonName);
            newPlant->setScientificName(scientificName);
            newPlant->setLastWatered(lastWatered);
            newPlant->setLastFertilized(lastFertilized);
            newPlant->setPotSize(potSize);
            newPlant->setRootbound(rootbound);
            newPlant->setNotes(notes);

            // TODO: Let user select or create a plant type
            cout << "\nAvailable plant types:\n";
            vector<PlantType*> plantTypes = collection.getAllPlantTypes();
            for (PlantType* pType : plantTypes) {
                if (pType) {
                    cout << pType->getId() << ". " << pType->getCommonNames() << " (" << pType->getLatinName() << ")\n";
                }
            }

            int plantTypeId;
            cout << "Enter plant type ID (0 if unknown): ";
            if (!(cin >> plantTypeId)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                plantTypeId = 0;
            }
            newPlant->setPlantTypeId(plantTypeId);

            // TODO: Create Plant object and save to database
            if (!db.savePlant(*newPlant)) {
                cout << "Failed to save plant to database.\n";
            }
            collection.addPlant(newPlant);
            cout << "Plant added.\n";
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