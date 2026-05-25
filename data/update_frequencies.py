# Watering and fertilizer frequency values (in days) for key species.
# These values are not present in the source Kaggle dataset (house_plants.json)
# and have been researched separately based on general horticultural guidelines.
# This script is called by setup.sh after import_plant_types.py.
import sqlite3

conn = sqlite3.connect('data/plants.db')
cursor = conn.cursor()

# Watering and fertilizer frequencies in days
# Values are approximate based on general horticultural guidelines
frequencies = [
    ('Epipremnum aureum', 7, 30),
    ('Sedum morganianum', 14, 60),
    ('Kalanchoe blossfeldiana', 7, 14),
    ('Dypsis lutescens', 7, 30),
    ('Chamaedorea elegans', 7, 30),
    ('Aechmea fasciata', 7, 30),
    ('Senecio rowleyanus', 14, 60),
    ('Hypoestes phyllostachya', 5, 14),
    ('Tradescantia fluminensis', 5, 14),
    ('Callisia repens', 5, 14),
    ('Maranta leuconeura erythroneura', 5, 30),
    ('Maranta leuconeura', 5, 30),
    ('Maranta leuconeura kerchoveana', 5, 30),
    ('Dracaena marginata', 10, 30),
    ('Chlorophytum comosum', 7, 30),
    ('Phalaenopsis X', 7, 14),
    ('Tillandsia ionantha', 3, 30),
    ('Tillandsia cyanea', 3, 30),
    ('Tillandsia Creation', 3, 30),
]

for latin_name, watering_days, fertilizer_days in frequencies:
    cursor.execute('''
        UPDATE plant_types 
        SET watering_frequency_days = ?,
            fertilizer_frequency_days = ?
        WHERE latin_name = ?
    ''', (watering_days, fertilizer_days, latin_name))
    if cursor.rowcount > 0:
        print(f'Updated: {latin_name}')
    else:
        print(f'Not found: {latin_name}')

# Manually insert species not in the Kaggle dataset
manual_species = [
    ('Kalanchoe blossfeldiana', 7, 14),
    ('Senecio rowleyanus', 14, 60),
    ('Hypoestes phyllostachya', 5, 14),
    ('Tradescantia fluminensis', 5, 14),
    ('Callisia repens', 5, 14),
    ('Tillandsia ionantha', 3, 30),
]

for latin_name, watering_days, fertilizer_days in manual_species:
    cursor.execute('''
        INSERT OR IGNORE INTO plant_types (latin_name, watering_frequency_days, fertilizer_frequency_days)
        VALUES (?, ?, ?)
    ''', (latin_name, watering_days, fertilizer_days))
    cursor.execute('''
        UPDATE plant_types 
        SET watering_frequency_days = ?,
            fertilizer_frequency_days = ?
        WHERE latin_name = ?
    ''', (watering_days, fertilizer_days, latin_name))
    print(f'Inserted/updated: {latin_name}')

conn.commit()
conn.close()