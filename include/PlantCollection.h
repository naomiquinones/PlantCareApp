#ifndef PLANTCOLLECTION_H
#define PLANTCOLLECTION_H

#include <vector>
#include <string>
#include "Plant.h"
#include "PlantType.h"

/**
 * PlantCollection manages the user's personal plant collection.
 * Holds Plant objects in memory and provides search and filtering.
 * Also holds PlantType objects for care data lookups.
 * Maps to the my_plants table in the database (via DatabaseHandler).
 */
class PlantCollection {
private:
    std::vector<Plant*> plants;
    std::vector<PlantType*> plantTypes;

    int getEffectiveWateringDays(const Plant& plant) const;
    int getEffectiveFertilizerDays(const Plant& plant) const;

public:
    PlantCollection();
    ~PlantCollection();

    void addPlant(Plant* plant);
    bool removePlant(int id);
    Plant* findPlant(int id) const;
    Plant* findPlantByName(const std::string& name) const;

    void addPlantType(PlantType* plantType);
    PlantType* findPlantType(int id) const;
    int getPlantTypeCount() const;
    std::vector<PlantType*> getAllPlantTypes() const;

    std::vector<Plant*> getPlantsNeedingWater() const;
    std::vector<Plant*> getPlantsNeedingFertilizer() const;
    std::vector<Plant*> getOverduePlants(int daysThreshold) const;

    void displayAll() const;
    void displayPlantsNeedingCare() const;

    int getCount() const;
    bool isEmpty() const;
};

#endif