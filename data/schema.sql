-- PlantCareApp Database Schema
-- Run this first to initialize the database

-- Reference tables (populated by import scripts)
CREATE TABLE IF NOT EXISTS plant_types (
    id INTEGER PRIMARY KEY,
    latin_name TEXT UNIQUE,
    common_names TEXT,
    family TEXT,
    category TEXT,
    origin TEXT,
    climate TEXT,
    temp_min_c REAL,
    temp_max_c REAL,
    ideal_light TEXT,
    tolerated_light TEXT,
    watering TEXT,
    watering_frequency_days INTEGER,
    fertilizer_frequency_days INTEGER,
    fertilizer_instructions TEXT,
    toxic_to_people INTEGER DEFAULT 0,
    toxic_to_pets INTEGER DEFAULT 0,
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
    Height_cm REAL,
    Leaf_Count INTEGER,
    New_Growth_Count INTEGER,
    Health_Notes TEXT,
    Watering_Amount_ml REAL,
    Watering_Frequency_days INTEGER,
    Sunlight_Exposure TEXT,
    Room_Temperature_C REAL,
    Humidity_pct REAL,
    Fertilizer_Type TEXT,
    Fertilizer_Amount_ml REAL,
    Pest_Presence TEXT,
    Pest_Severity TEXT,
    Soil_Moisture_pct REAL,
    Soil_Type TEXT,
    Health_Score REAL
);

-- User data (personal collection)
CREATE TABLE IF NOT EXISTS my_plants (
    id INTEGER PRIMARY KEY,
    common_name TEXT,
    scientific_name TEXT,
    plant_type_id INTEGER REFERENCES plant_types(id),
    last_watered TEXT,
    last_fertilized TEXT,
    pot_size TEXT,
    rootbound INTEGER DEFAULT 0,
    notes TEXT,
    watering_frequency_days_override INTEGER,
    fertilizer_frequency_days_override INTEGER
);

-- Care history
CREATE TABLE IF NOT EXISTS care_events (
    id INTEGER PRIMARY KEY,
    plant_id INTEGER REFERENCES my_plants(id),
    event_type TEXT,
    event_date TEXT,
    notes TEXT
);