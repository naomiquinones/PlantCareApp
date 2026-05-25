#include <iostream>
#include <cassert>
#include "Plant.h"
#include "PlantType.h"
#include "CareEvent.h"

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

int main() {
    cout << "Running tests...\n\n";

    test_plant_initialization();
    test_plant_needs_water();
    test_plant_needs_fertilizer();
    test_planttype_initialization();
    test_careevent_initialization();

    cout << "\nAll tests completed.\n";
    return 0;
}