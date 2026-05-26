#include "Plant.h"
#include <iostream>
#include <iomanip>

using namespace std;

Plant::Plant()
    : id(0), commonName(""), scientificName(""), plantTypeId(0),
      lastWatered(""), lastFertilized(""), potSize(""),
      rootbound(false), notes(""),
      wateringFrequencyDaysOverride(0), fertilizerFrequencyDaysOverride(0) {}

Plant::Plant(const string& commonName, const string& scientificName)
    : id(0), commonName(commonName), scientificName(scientificName),
      plantTypeId(0), lastWatered(""), lastFertilized(""), potSize(""),
      rootbound(false), notes(""),
      wateringFrequencyDaysOverride(0), fertilizerFrequencyDaysOverride(0) {}

// Getters
int Plant::getId() const { return id; }
string Plant::getCommonName() const { return commonName; }
string Plant::getScientificName() const { return scientificName; }
int Plant::getPlantTypeId() const { return plantTypeId; }
string Plant::getLastWatered() const { return lastWatered; }
string Plant::getLastFertilized() const { return lastFertilized; }
string Plant::getPotSize() const { return potSize; }
bool Plant::isRootbound() const { return rootbound; }
string Plant::getNotes() const { return notes; }
int Plant::getWateringFrequencyDaysOverride() const { return wateringFrequencyDaysOverride; }
int Plant::getFertilizerFrequencyDaysOverride() const { return fertilizerFrequencyDaysOverride; }

// Setters
void Plant::setId(int id) { this->id = id; }
void Plant::setCommonName(const string& name) { this->commonName = name; }
void Plant::setScientificName(const string& name) { this->scientificName = name; }
void Plant::setPlantTypeId(int typeId) { this->plantTypeId = typeId; }
void Plant::setLastWatered(const string& date) { this->lastWatered = date; }
void Plant::setLastFertilized(const string& date) { this->lastFertilized = date; }
void Plant::setPotSize(const string& size) { this->potSize = size; }
void Plant::setRootbound(bool rootbound) { this->rootbound = rootbound; }
void Plant::setNotes(const string& notes) { this->notes = notes; }
void Plant::setWateringFrequencyDaysOverride(int days) { this->wateringFrequencyDaysOverride = days; }
void Plant::setFertilizerFrequencyDaysOverride(int days) { this->fertilizerFrequencyDaysOverride = days; }

// Care status
bool Plant::needsWater(int speciesWateringDays) const {
    // TODO: Implement date comparison
    return false;
}

bool Plant::needsFertilizer(int speciesFertilizerDays) const {
    // TODO: Implement date comparison
    return false;
}

int Plant::daysSinceWatered() const {
    // TODO: Implement date calculation
    return 0;
}

int Plant::daysSinceFertilized() const {
    // TODO: Implement date calculation
    return 0;
}

void Plant::display() const {
    cout << "------------------------\n";

    cout << left << setw(16) << "Name:" << commonName << "\n";

    cout << left << setw(16) << "Species:" << scientificName << "\n";

    cout << left << setw(16) << "Last watered:" << (lastWatered.empty() ? "Never" : lastWatered) << "\n";

    cout << left << setw(16) << "Last fertilized:" << (lastFertilized.empty() ? "Never" : lastFertilized) << "\n";

    cout << left << setw(16) << "Pot size:" << (potSize.empty() ? "Unknown" : potSize) << "\n";

    cout << left << setw(16) << "Rootbound:" << (rootbound ? "Yes" : "No") << "\n";

    if (!notes.empty()) {
        cout << left << setw(16) << "Notes:" << notes << "\n";
    }

    cout << "------------------------\n";
}