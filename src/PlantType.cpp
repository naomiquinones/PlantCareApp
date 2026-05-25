#include "PlantType.h"
#include <iostream>
using namespace std;

PlantType::PlantType() : id(0), latinName(""), commonNames(""), family(""), category(""),
    origin(""), climate(""), tempMinC(0.0), tempMaxC(0.0), idealLight(""), toleratedLight(""),
    watering(""), wateringFrequencyDays(0), fertilizerFrequencyDays(0),
    fertilizerInstructions(""), toxicToPeople(false), toxicToPets(false), diseases("") {}
PlantType::PlantType(int id, const string& latinName) : id(id), latinName(latinName),
    commonNames(""), family(""), category(""), origin(""), climate(""), tempMinC(0.0),
    tempMaxC(0.0), idealLight(""), toleratedLight(""), watering(""), wateringFrequencyDays(0),
    fertilizerFrequencyDays(0), fertilizerInstructions(""), toxicToPeople(false),
    toxicToPets(false), diseases("") {}
int PlantType::getId() const { return id; }
string PlantType::getLatinName() const { return latinName; }
string PlantType::getCommonNames() const { return commonNames; }
string PlantType::getFamily() const { return family; }
string PlantType::getCategory() const { return category; }
string PlantType::getOrigin() const { return origin; }
string PlantType::getClimate() const { return climate; }
double PlantType::getTempMinC() const { return tempMinC; }
double PlantType::getTempMaxC() const { return tempMaxC; }
string PlantType::getIdealLight() const { return idealLight; }
string PlantType::getToleratedLight() const { return toleratedLight; }
string PlantType::getWatering() const { return watering; }
int PlantType::getWateringFrequencyDays() const { return wateringFrequencyDays; }
int PlantType::getFertilizerFrequencyDays() const { return fertilizerFrequencyDays; }
string PlantType::getFertilizerInstructions() const { return fertilizerInstructions; }
bool PlantType::isToxicToPeople() const { return toxicToPeople; }
bool PlantType::isToxicToPets() const { return toxicToPets; }
string PlantType::getDiseases() const { return diseases; }
void PlantType::setId(int id) { this->id = id; }
void PlantType::setLatinName(const string& name) { this->latinName = name; }
void PlantType::setCommonNames(const string& commonNames) { this->commonNames = commonNames; }
void PlantType::setFamily(const string& family) { this->family = family; }
void PlantType::setCategory(const string& category) { this->category = category; }
void PlantType::setOrigin(const string& origin) { this->origin = origin; }
void PlantType::setClimate(const string& climate) { this->climate = climate; }
void PlantType::setTempMinC(double temp) { this->tempMinC = temp; }
void PlantType::setTempMaxC(double temp) { this->tempMaxC = temp; }
void PlantType::setIdealLight(const string& light) { this->idealLight = light; }
void PlantType::setToleratedLight(const string& light) { this->toleratedLight = light; }
void PlantType::setWatering(const string& watering) { this->watering = watering; }
void PlantType::setWateringFrequencyDays(int days) { this->wateringFrequencyDays = days; }
void PlantType::setFertilizerFrequencyDays(int days) { this->fertilizerFrequencyDays = days; }
void PlantType::setFertilizerInstructions(const string& instructions) { this->fertilizerInstructions = instructions; }
void PlantType::setToxicToPeople(bool toxic) { this->toxicToPeople = toxic; }
void PlantType::setToxicToPets(bool toxic) { this->toxicToPets = toxic; }
void PlantType::setDiseases(const string& diseases) { this->diseases = diseases; }
void PlantType::display() const { cout << "[PlantType::display] not yet implemented\n"; }
