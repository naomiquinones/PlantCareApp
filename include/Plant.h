#ifndef PLANT_H
#define PLANT_H

#include <string>

/**
 * Plant represents a specific plant owned by the user.
 * Maps to the my_plants table in the database.
 * Tracks care history and links to a PlantType for species data.
 */
class Plant {
private:
    int id;
    std::string commonName;
    std::string scientificName;
    int plantTypeId;
    std::string lastWatered;
    std::string lastFertilized;
    std::string potSize;
    bool rootbound;
    std::string notes;
    int wateringFrequencyDaysOverride;
    int fertilizerFrequencyDaysOverride;

public:
    Plant();
    Plant(const std::string& commonName, const std::string& scientificName);

    int getId() const;
    std::string getCommonName() const;
    std::string getScientificName() const;
    int getPlantTypeId() const;
    std::string getLastWatered() const;
    std::string getLastFertilized() const;
    std::string getPotSize() const;
    bool isRootbound() const;
    std::string getNotes() const;
    int getWateringFrequencyDaysOverride() const;
    int getFertilizerFrequencyDaysOverride() const;

    void setId(int id);
    void setCommonName(const std::string& name);
    void setScientificName(const std::string& name);
    void setPlantTypeId(int typeId);
    void setLastWatered(const std::string& date);
    void setLastFertilized(const std::string& date);
    void setPotSize(const std::string& size);
    void setRootbound(bool rootbound);
    void setNotes(const std::string& notes);
    void setWateringFrequencyDaysOverride(int days);
    void setFertilizerFrequencyDaysOverride(int days);

    bool needsWater(int speciesWateringDays) const;
    bool needsFertilizer(int speciesFertilizerDays) const;
    int daysSinceWatered() const;
    int daysSinceFertilized() const;

    void display() const;
};

#endif