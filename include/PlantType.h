#ifndef PLANTTYPE_H
#define PLANTTYPE_H

#include <string>

/**
 * PlantType represents a plant species with its care requirements.
 * Maps to the plant_types table in the database.
 * Contains reference data shared across all plants of the same species.
 */
class PlantType {
private:
    int id;
    std::string latinName;
    std::string commonNames;
    std::string family;
    std::string category;
    std::string origin;
    std::string climate;
    double tempMinC;
    double tempMaxC;
    std::string idealLight;
    std::string toleratedLight;
    std::string watering;
    int wateringFrequencyDays;
    int fertilizerFrequencyDays;
    std::string fertilizerInstructions;
    bool toxicToPeople;
    bool toxicToPets;
    std::string diseases;

public:
    PlantType();
    PlantType(int id, const std::string& latinName);

    int getId() const;
    std::string getLatinName() const;
    std::string getCommonNames() const;
    std::string getFamily() const;
    std::string getCategory() const;
    std::string getOrigin() const;
    std::string getClimate() const;
    double getTempMinC() const;
    double getTempMaxC() const;
    std::string getIdealLight() const;
    std::string getToleratedLight() const;
    std::string getWatering() const;
    int getWateringFrequencyDays() const;
    int getFertilizerFrequencyDays() const;
    std::string getFertilizerInstructions() const;
    bool isToxicToPeople() const;
    bool isToxicToPets() const;
    std::string getDiseases() const;

    void setId(int id);
    void setLatinName(const std::string& name);
    void setCommonNames(const std::string& commonNames);
    void setFamily(const std::string& family);
    void setCategory(const std::string& category);
    void setOrigin(const std::string& origin);
    void setClimate(const std::string& climate);
    void setTempMinC(double temp);
    void setTempMaxC(double temp);
    void setIdealLight(const std::string& light);
    void setToleratedLight(const std::string& light);
    void setWatering(const std::string& watering);
    void setWateringFrequencyDays(int days);
    void setFertilizerFrequencyDays(int days);
    void setFertilizerInstructions(const std::string& instructions);
    void setToxicToPeople(bool toxic);
    void setToxicToPets(bool toxic);
    void setDiseases(const std::string& diseases);

    void display() const;
};

#endif // PLANTTYPE_H