#include "PlantCollection.h"
#include <iostream>
using namespace std;

PlantCollection::PlantCollection() {}
PlantCollection::~PlantCollection() {
    for (Plant* p : plants) delete p;
    for (PlantType* pt : plantTypes) delete pt;
}
void PlantCollection::addPlant(Plant* plant) {}
bool PlantCollection::removePlant(int id) { return false; }
Plant* PlantCollection::findPlant(int id) const { return nullptr; }
Plant* PlantCollection::findPlantByName(const string& name) const { return nullptr; }
void PlantCollection::addPlantType(PlantType* plantType) {}
PlantType* PlantCollection::findPlantType(int id) const { return nullptr; }
vector<Plant*> PlantCollection::getPlantsNeedingWater() const { return {}; }
vector<Plant*> PlantCollection::getPlantsNeedingFertilizer() const { return {}; }
vector<Plant*> PlantCollection::getOverduePlants(int daysThreshold) const { return {}; }
void PlantCollection::displayAll() const { cout << "[PlantCollection::displayAll] not yet implemented\n"; }
void PlantCollection::displayPlantsNeedingCare() const { cout << "[PlantCollection::displayPlantsNeedingCare] not yet implemented\n"; }
int PlantCollection::getCount() const { return 0; }
bool PlantCollection::isEmpty() const { return true; }
int PlantCollection::getEffectiveWateringDays(const Plant& plant) const { return 0; }
int PlantCollection::getEffectiveFertilizerDays(const Plant& plant) const { return 0; }
