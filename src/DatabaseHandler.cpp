#include "DatabaseHandler.h"
#include <iostream>
using namespace std;

DatabaseHandler::DatabaseHandler(const string& dbPath) : db(nullptr), dbPath(dbPath) {}
DatabaseHandler::~DatabaseHandler() { close(); }
bool DatabaseHandler::open() {
	if (db) {
		return false;
	}

	try {
		db = new SQLite::Database(dbPath, SQLite::OPEN_READWRITE);
		return true;
	} catch (const SQLite::Exception&) {
		db = nullptr;
		return false;
	}
}

void DatabaseHandler::close() {
	if (db) {
		delete db;
		db = nullptr;
	}
}
bool DatabaseHandler::isOpen() const { return db != nullptr; }
bool DatabaseHandler::execute(const string& sql) { return false; }
bool DatabaseHandler::initializeDatabase() { return false; }
bool DatabaseHandler::loadPlantTypes(PlantCollection& collection) {
	if (!db) {
		return false;
	}

	try {
		SQLite::Statement query(*db,
			"SELECT id, latin_name, common_names, family, category, origin, climate, "
			"temp_min_c, temp_max_c, ideal_light, tolerated_light, watering, "
			"watering_frequency_days, fertilizer_frequency_days, fertilizer_instructions, "
			"toxic_to_people, toxic_to_pets, diseases FROM plant_types");

		while (query.executeStep()) {
			PlantType* plantType = new PlantType();

			const auto& idColumn = query.getColumn(0);
			if (!idColumn.isNull()) {
				plantType->setId(idColumn.getInt());
			}

			const auto& latinNameColumn = query.getColumn(1);
			plantType->setLatinName(latinNameColumn.isNull() ? "" : latinNameColumn.getText());

			const auto& commonNamesColumn = query.getColumn(2);
			plantType->setCommonNames(commonNamesColumn.isNull() ? "" : commonNamesColumn.getText());

			const auto& familyColumn = query.getColumn(3);
			plantType->setFamily(familyColumn.isNull() ? "" : familyColumn.getText());

			const auto& categoryColumn = query.getColumn(4);
			plantType->setCategory(categoryColumn.isNull() ? "" : categoryColumn.getText());

			const auto& originColumn = query.getColumn(5);
			plantType->setOrigin(originColumn.isNull() ? "" : originColumn.getText());

			const auto& climateColumn = query.getColumn(6);
			plantType->setClimate(climateColumn.isNull() ? "" : climateColumn.getText());

			const auto& tempMinColumn = query.getColumn(7);
			if (!tempMinColumn.isNull()) {
				plantType->setTempMinC(tempMinColumn.getDouble());
			}

			const auto& tempMaxColumn = query.getColumn(8);
			if (!tempMaxColumn.isNull()) {
				plantType->setTempMaxC(tempMaxColumn.getDouble());
			}

			const auto& idealLightColumn = query.getColumn(9);
			plantType->setIdealLight(idealLightColumn.isNull() ? "" : idealLightColumn.getText());

			const auto& toleratedLightColumn = query.getColumn(10);
			plantType->setToleratedLight(toleratedLightColumn.isNull() ? "" : toleratedLightColumn.getText());

			const auto& wateringColumn = query.getColumn(11);
			plantType->setWatering(wateringColumn.isNull() ? "" : wateringColumn.getText());

			const auto& wateringFrequencyColumn = query.getColumn(12);
			if (!wateringFrequencyColumn.isNull()) {
				plantType->setWateringFrequencyDays(wateringFrequencyColumn.getInt());
			}

			const auto& fertilizerFrequencyColumn = query.getColumn(13);
			if (!fertilizerFrequencyColumn.isNull()) {
				plantType->setFertilizerFrequencyDays(fertilizerFrequencyColumn.getInt());
			}

			const auto& fertilizerInstructionsColumn = query.getColumn(14);
			plantType->setFertilizerInstructions(fertilizerInstructionsColumn.isNull() ? "" : fertilizerInstructionsColumn.getText());

			const auto& toxicToPeopleColumn = query.getColumn(15);
			if (!toxicToPeopleColumn.isNull()) {
				plantType->setToxicToPeople(toxicToPeopleColumn.getInt() != 0);
			}

			const auto& toxicToPetsColumn = query.getColumn(16);
			if (!toxicToPetsColumn.isNull()) {
				plantType->setToxicToPets(toxicToPetsColumn.getInt() != 0);
			}

			const auto& diseasesColumn = query.getColumn(17);
			plantType->setDiseases(diseasesColumn.isNull() ? "" : diseasesColumn.getText());

			collection.addPlantType(plantType);
		}

		return true;
	} catch (const SQLite::Exception&) {
		return false;
	}
}
PlantType* DatabaseHandler::getPlantType(const string& latinName) { return nullptr; }
bool DatabaseHandler::loadPlants(PlantCollection& collection) {
	if (!db) {
		return false;
	}

	try {
		SQLite::Statement query(*db,
			"SELECT id, common_name, scientific_name, plant_type_id, last_watered, "
			"last_fertilized, pot_size, rootbound, notes, "
			"watering_frequency_days_override, fertilizer_frequency_days_override "
			"FROM my_plants");

		while (query.executeStep()) {
			Plant* plant = new Plant();

			const auto& idColumn = query.getColumn(0);
			if (!idColumn.isNull()) {
				plant->setId(idColumn.getInt());
			}

			const auto& commonNameColumn = query.getColumn(1);
			plant->setCommonName(commonNameColumn.isNull() ? "" : commonNameColumn.getText());

			const auto& scientificNameColumn = query.getColumn(2);
			plant->setScientificName(scientificNameColumn.isNull() ? "" : scientificNameColumn.getText());

			const auto& plantTypeIdColumn = query.getColumn(3);
			if (!plantTypeIdColumn.isNull()) {
				plant->setPlantTypeId(plantTypeIdColumn.getInt());
			}

			const auto& lastWateredColumn = query.getColumn(4);
			plant->setLastWatered(lastWateredColumn.isNull() ? "" : lastWateredColumn.getText());

			const auto& lastFertilizedColumn = query.getColumn(5);
			plant->setLastFertilized(lastFertilizedColumn.isNull() ? "" : lastFertilizedColumn.getText());

			const auto& potSizeColumn = query.getColumn(6);
			plant->setPotSize(potSizeColumn.isNull() ? "" : potSizeColumn.getText());

			const auto& rootboundColumn = query.getColumn(7);
			if (!rootboundColumn.isNull()) {
				plant->setRootbound(rootboundColumn.getInt() != 0);
			}

			const auto& notesColumn = query.getColumn(8);
			plant->setNotes(notesColumn.isNull() ? "" : notesColumn.getText());

			const auto& wateringOverrideColumn = query.getColumn(9);
			if (!wateringOverrideColumn.isNull()) {
				plant->setWateringFrequencyDaysOverride(wateringOverrideColumn.getInt());
			}

			const auto& fertilizerOverrideColumn = query.getColumn(10);
			if (!fertilizerOverrideColumn.isNull()) {
				plant->setFertilizerFrequencyDaysOverride(fertilizerOverrideColumn.getInt());
			}

			collection.addPlant(plant);
		}

		return true;
	} catch (const SQLite::Exception&) {
		return false;
	}
}

bool DatabaseHandler::savePlant(Plant& plant) {
	if (!db) return false;
	try {
		SQLite::Statement query(*db,
			"INSERT INTO my_plants (common_name, scientific_name, plant_type_id, last_watered, last_fertilized, pot_size, rootbound, notes, watering_frequency_days_override, fertilizer_frequency_days_override) "
			"VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
		query.bind(1, plant.getCommonName());
		query.bind(2, plant.getScientificName());
		query.bind(3, plant.getPlantTypeId());
		query.bind(4, plant.getLastWatered());
		query.bind(5, plant.getLastFertilized());
		query.bind(6, plant.getPotSize());
		query.bind(7, plant.isRootbound() ? 1 : 0);
		query.bind(8, plant.getNotes());
		query.bind(9, plant.getWateringFrequencyDaysOverride());
		query.bind(10, plant.getFertilizerFrequencyDaysOverride());
		query.exec();
		plant.setId(static_cast<int>(db->getLastInsertRowid()));
		return true;
		return true;
	} catch (const SQLite::Exception&) {
		return false;
	}
}

bool DatabaseHandler::savePlantType(const PlantType& plantType) { return false; }
bool DatabaseHandler::updatePlant(const Plant& plant) { return false; }
bool DatabaseHandler::deletePlant(int id) { return false; }
bool DatabaseHandler::logCareEvent(const Plant& plant, const string& eventType) { return false; }
vector<CareEvent> DatabaseHandler::getCareHistory(int plantId) { return {}; }
