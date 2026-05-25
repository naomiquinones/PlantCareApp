#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <vector>
#include "sqlite3.h"
#include "Plant.h"
#include "PlantType.h"
#include "CareEvent.h"
#include "PlantCollection.h"

/**
 * DatabaseHandler manages the SQLite database connection.
 * Responsible for all reading and writing to plants.db.
 * Uses a raw sqlite3* pointer managed manually.
 */
class DatabaseHandler {
private:
    sqlite3* db;
    std::string dbPath;

    bool execute(const std::string& sql);

public:
    DatabaseHandler(const std::string& dbPath);
    ~DatabaseHandler();

    bool open();
    void close();
    bool isOpen() const;

    bool initializeDatabase();

    bool loadPlantTypes(PlantCollection& collection);
    PlantType* getPlantType(const std::string& latinName);

    bool loadPlants(PlantCollection& collection);
    bool savePlant(const Plant& plant);
    bool updatePlant(const Plant& plant);
    bool deletePlant(int id);

    bool logCareEvent(const Plant& plant, const std::string& eventType);
    std::vector<CareEvent> getCareHistory(int plantId);
};

#endif