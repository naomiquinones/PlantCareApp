#include <iostream>
#include <cassert>
#include "SQLiteCpp/SQLiteCpp.h"
#include "Plant.h"
#include "PlantCollection.h"
#include "PlantType.h"
#include "CareEvent.h"
#include "DatabaseHandler.h"

using namespace std;

void test_plant_initialization() {
    // TODO: Create a Plant and verify initial state
    // Plant p("My Pothos", "Epipremnum aureum");
    // assert(p.getCommonName() == "My Pothos");
    // assert(p.getScientificName() == "Epipremnum aureum");
    cout << "test_plant_initialization: TODO\n";
}

void test_plant_needs_water() {
    // TODO: Test needsWater() with a known last watered date
    // Plant p("My Pothos", "Epipremnum aureum");
    // p.setLastWatered("2026-05-01");
    // assert(p.needsWater(7) == true);  // more than 7 days ago
    cout << "test_plant_needs_water: TODO\n";
}

void test_plant_needs_fertilizer() {
    // TODO: Test needsFertilizer() with a known last fertilized date
    cout << "test_plant_needs_fertilizer: TODO\n";
}

void test_planttype_initialization() {
    // TODO: Create a PlantType and verify initial state
    // PlantType pt(1, "Epipremnum aureum");
    // assert(pt.getId() == 1);
    // assert(pt.getLatinName() == "Epipremnum aureum");
    cout << "test_planttype_initialization: TODO\n";
}

void test_careevent_initialization() {
    // TODO: Create a CareEvent and verify initial state
    // CareEvent e(1, "water", "2026-05-20");
    // assert(e.getPlantId() == 1);
    // assert(e.getEventType() == "water");
    cout << "test_careevent_initialization: TODO\n";
}

void test_add_plants_normal() {
    cout << "test_add_plants_normal\n";

    PlantCollection collection;

    Plant* p1 = new Plant();
    p1->setCommonName("Snake Plant");

    Plant* p2 = new Plant();
    p2->setCommonName("Pothos");

    collection.addPlant(p1);
    collection.addPlant(p2);

    assert(collection.getCount() == 2);
}

void test_empty_collection() {
    cout << "test_empty_collection\n";

    PlantCollection collection;

    assert(collection.getCount() == 0);
}

void test_single_plant() {
    cout << "test_single_plant\n";

    PlantCollection collection;

    Plant* p1 = new Plant();
    p1->setCommonName("Monstera");

    collection.addPlant(p1);

    assert(collection.getCount() == 1);
}

void test_database_loading() {
    cout << "test_database_loading\n";

    remove("test_plants.db");


    SQLite::Database setupDb(
        "test_plants.db",
        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE
    );
    std::cout << "Test plants database opened or created successfully.\n";

    setupDb.exec("CREATE TABLE plant_types (id INTEGER PRIMARY KEY, latin_name TEXT, common_names TEXT, family TEXT, category TEXT, origin TEXT, climate TEXT, temp_min_c REAL, temp_max_c REAL, ideal_light TEXT, tolerated_light TEXT, watering TEXT, watering_frequency_days INTEGER, fertilizer_frequency_days INTEGER, fertilizer_instructions TEXT, toxic_to_people INTEGER DEFAULT 0, toxic_to_pets INTEGER DEFAULT 0, diseases TEXT)");
    cout << "Plant types table created.\n";

    setupDb.exec("CREATE TABLE my_plants (id INTEGER PRIMARY KEY, common_name TEXT, scientific_name TEXT, plant_type_id INTEGER, last_watered TEXT, last_fertilized TEXT, pot_size TEXT, rootbound INTEGER, notes TEXT, watering_frequency_days_override INTEGER, fertilizer_frequency_days_override INTEGER)");
    cout << "My plants table created.\n";

    setupDb.exec("INSERT INTO plant_types (id, latin_name, common_names, watering_frequency_days, fertilizer_frequency_days) VALUES (1, 'Dracaena trifasciata', 'Snake Plant', 14, 30)");

    setupDb.exec("INSERT INTO my_plants (id, common_name, scientific_name, plant_type_id, last_watered, last_fertilized, pot_size, rootbound, notes, watering_frequency_days_override, fertilizer_frequency_days_override) VALUES (1, 'Snake Plant', 'Dracaena trifasciata', 1, '2026-05-01', '2026-05-01', 'Medium', 0, '', 0, 0)");

    setupDb.exec("INSERT INTO my_plants (id, common_name, scientific_name, plant_type_id, last_watered, last_fertilized, pot_size, rootbound, notes, watering_frequency_days_override, fertilizer_frequency_days_override) VALUES (2, 'Pothos', 'Epipremnum aureum', 1, '2026-05-01', '2026-05-01', 'Small', 1, '', 0, 0)");

    cout << "Test data inserted.\n";

    PlantCollection collection;

    assert(collection.getCount() == 0);

    DatabaseHandler testDb("test_plants.db");
    assert(testDb.open());
    assert(testDb.loadPlantTypes(collection));
    assert(testDb.loadPlants(collection));
    assert(collection.getCount() == 2);

    assert(collection.getPlantTypeCount() == 1);
    assert(collection.getCount() == 2);
    remove("test_plants.db");
}

void test_database_missing_file() {
    cout << "test_database_missing_file\n";

    remove("nonexistent.db");

    DatabaseHandler handler("nonexistent.db");
    assert(!handler.open());
    assert(!handler.isOpen());
}

void test_database_empty_plants() {
    cout << "test_database_empty_plants\n";

    remove("test_empty.db");

    SQLite::Database setupDb("test_empty.db",
        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    setupDb.exec("CREATE TABLE plant_types (id INTEGER PRIMARY KEY, latin_name TEXT, common_names TEXT, family TEXT, category TEXT, origin TEXT, climate TEXT, temp_min_c REAL, temp_max_c REAL, ideal_light TEXT, tolerated_light TEXT, watering TEXT, watering_frequency_days INTEGER, fertilizer_frequency_days INTEGER, fertilizer_instructions TEXT, toxic_to_people INTEGER DEFAULT 0, toxic_to_pets INTEGER DEFAULT 0, diseases TEXT)");

    setupDb.exec("CREATE TABLE my_plants (id INTEGER PRIMARY KEY, common_name TEXT, scientific_name TEXT, plant_type_id INTEGER, last_watered TEXT, last_fertilized TEXT, pot_size TEXT, rootbound INTEGER, notes TEXT, watering_frequency_days_override INTEGER, fertilizer_frequency_days_override INTEGER)");

    PlantCollection collection;
    DatabaseHandler handler("test_empty.db");
    assert(handler.open());
    assert(handler.loadPlantTypes(collection));
    assert(handler.loadPlants(collection));
    assert(collection.getCount() == 0);
    assert(collection.getPlantTypeCount() == 0);

    remove("test_empty.db");
}

void test_save_plant() {
    cout << "test_save_plant\n";

    remove("test_save.db");

    SQLite::Database setupDb("test_save.db",
        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    setupDb.exec("CREATE TABLE plant_types (id INTEGER PRIMARY KEY, latin_name TEXT, common_names TEXT, family TEXT, category TEXT, origin TEXT, climate TEXT, temp_min_c REAL, temp_max_c REAL, ideal_light TEXT, tolerated_light TEXT, watering TEXT, watering_frequency_days INTEGER, fertilizer_frequency_days INTEGER, fertilizer_instructions TEXT, toxic_to_people INTEGER DEFAULT 0, toxic_to_pets INTEGER DEFAULT 0, diseases TEXT)");

    setupDb.exec("CREATE TABLE my_plants (id INTEGER PRIMARY KEY, common_name TEXT, scientific_name TEXT, plant_type_id INTEGER, last_watered TEXT, last_fertilized TEXT, pot_size TEXT, rootbound INTEGER, notes TEXT, watering_frequency_days_override INTEGER, fertilizer_frequency_days_override INTEGER)");

    Plant* plant = new Plant("Snake Plant", "Dracaena trifasciata");

    Plant* plant2 = new Plant();
    plant2->setCommonName("Pothos");
    plant2->setScientificName("Epipremnum aureum");

    PlantCollection collection;
    // collection.addPlant(plant);
    // collection.addPlant(plant2);

    DatabaseHandler handler("test_save.db");
    assert(handler.open());
    assert(handler.savePlant(*plant));
    assert(plant->getId() == 1);

    assert(handler.savePlant(*plant2));
    assert(plant2->getId() == 2);

    assert(handler.loadPlants(collection));
    assert(collection.getCount() == 2);

    assert(collection.findPlantByName("Snake Plant") != nullptr);
    assert(collection.findPlantByName("Pothos") != nullptr);

    remove("test_save.db");

}

int main() {
    cout << "Running tests...\n\n";

    test_plant_initialization();
    test_plant_needs_water();
    test_plant_needs_fertilizer();
    test_planttype_initialization();
    test_careevent_initialization();

    test_add_plants_normal();
    test_empty_collection();
    test_single_plant();
    test_database_loading();
    test_database_missing_file();
    test_database_empty_plants();

    test_save_plant();

    cout << "\nAll tests completed.\n";
    return 0;
}