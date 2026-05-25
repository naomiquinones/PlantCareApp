#ifndef PLANTTYPE_H
#define PLANTTYPE_H

#include <string>
using namespace std;

/**
 * PlantType represents a plant species with its care requirements.
 * Maps to the plant_types table in the database.
 * Contains reference data shared across all plants of the same species.
 */
class PlantType {
private:
    int id;
    string latinName;
    string family;
    string category;
    string origin;
    string climate;
    double tempMinC;
    double tempMaxC;
    string idealLight;
    string toleratedLight;
    string watering;
    string diseases;

public:
    PlantType();
    PlantType(int id, const string& latinName);

    int getId() const;
    string getLatinName() const;
    string getFamily() const;
    string getCategory() const;
    string getOrigin() const;
    string getClimate() const;
    double getTempMinC() const;
    double getTempMaxC() const;
    string getIdealLight() const;
    string getToleratedLight() const;
    string getWatering() const;
    string getDiseases() const;

    void setId(int id);
    void setLatinName(const string& name);
    void setFamily(const string& family);
    void setCategory(const string& category);
    void setOrigin(const string& origin);
    void setClimate(const string& climate);
    void setTempMinC(double temp);
    void setTempMaxC(double temp);
    void setIdealLight(const string& light);
    void setToleratedLight(const string& light);
    void setWatering(const string& watering);
    void setDiseases(const string& diseases);

    void display() const;
};

#endif