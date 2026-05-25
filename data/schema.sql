-- PlantCareApp Database Schema
-- Run this first to initialize the database

-- Reference tables (populated by import scripts)
CREATE TABLE IF NOT EXISTS plant_types (
    id INTEGER PRIMARY KEY,
    latin_name TEXT UNIQUE,
    family TEXT,
    category TEXT,
    origin TEXT,
    climate TEXT,
    temp_min_c REAL,
    temp_max_c REAL,
    ideal_light TEXT,
    tolerated_light TEXT,
    watering TEXT,
    diseases TEXT
);

CREATE TABLE IF NOT EXISTS plant_pests (
    id INTEGER PRIMARY KEY,
    plant_type_id INTEGER REFERENCES plant_types(id),
    pest TEXT
);

CREATE TABLE IF NOT EXISTS plant_uses (
    id INTEGER PRIMARY KEY,
    plant_type_id INTEGER REFERENCES plant_types(id),
    use TEXT
);

-- Kaggle observation data
CREATE TABLE IF NOT EXISTS factors (
    Plant_ID TEXT,
    Height_cm TEXT,
    Leaf_Count TEXT,
    New_Growth_Count TEXT,
    Health_Notes TEXT,
    Watering_Amount_ml TEXT,
    Watering_Frequency_days TEXT,
    Sunlight_Exposure TEXT,
    Room_Temperature_C TEXT,
    "Humidity_%" TEXT,
    Fertilizer_Type TEXT,
    Fertilizer_Amount_ml TEXT,
    Pest_Presence TEXT,
    Pest_Severity TEXT,
    "Soil_Moisture_%" TEXT,
    Soil_Type TEXT,
    Health_Score TEXT
);

-- User data (personal collection)
CREATE TABLE IF NOT EXISTS my_plants (
    id INTEGER PRIMARY KEY,
    common_name TEXT,
    scientific_name TEXT,
    last_watered TEXT,
    last_fertilized TEXT
);

-- Care history
CREATE TABLE IF NOT EXISTS care_events (
    id INTEGER PRIMARY KEY,
    plant_id INTEGER REFERENCES my_plants(id),
    event_type TEXT,
    event_date TEXT,
    notes TEXT
);