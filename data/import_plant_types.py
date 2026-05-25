import json
import sqlite3

with open('data/house_plants.json') as f:
    data = json.load(f)

conn = sqlite3.connect('data/plants.db')
cursor = conn.cursor()

for plant in data:
    latin = plant.get('latin', '')
    family = plant.get('family', '')
    category = plant.get('category', '')
    origin = plant.get('origin', '')
    climate = plant.get('climate', '')

    # Extract celsius from nested temp objects
    tempmin = plant.get('tempmin', {}).get('celsius', None)
    tempmax = plant.get('tempmax', {}).get('celsius', None)

    ideal_light = plant.get('ideallight', '')
    tolerated_light = plant.get('toleratedlight', '')
    watering = plant.get('watering', '')

    # common names as comma-separated string
    common = plant.get('common', [])
    common_str = ', '.join(common) if isinstance(common, list) else common

    diseases = plant.get('diseases', '')
    if isinstance(diseases, list):
        diseases = ', '.join(diseases)

    # optional numeric frequencies / toxicity / fertilizer instructions
    watering_freq = plant.get('watering_frequency_days', None)
    fertilizer_freq = plant.get('fertilizer_frequency_days', None)
    fertilizer_instructions = plant.get('fertilizer', '')
    toxic_field = plant.get('toxic') or plant.get('toxicity') or {}
    toxic_to_people = 0
    toxic_to_pets = 0
    if isinstance(toxic_field, dict):
        toxic_to_people = 1 if toxic_field.get('people') else 0
        toxic_to_pets = 1 if toxic_field.get('pets') else 0
    elif isinstance(toxic_field, str):
        tf = toxic_field.lower()
        toxic_to_people = 1 if 'people' in tf or 'human' in tf or 'toxic' in tf else 0
        toxic_to_pets = 1 if 'pet' in tf or 'dog' in tf or 'cat' in tf else 0

    # Insert into plant_types
    cursor.execute('''
        INSERT OR IGNORE INTO plant_types 
        (latin_name, common_names, family, category, origin, climate, 
         temp_min_c, temp_max_c, ideal_light, tolerated_light, 
         watering, watering_frequency_days, fertilizer_frequency_days,
         fertilizer_instructions, toxic_to_people, toxic_to_pets, diseases)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    ''', (latin, common_str, family, category, origin, climate,
          tempmin, tempmax, ideal_light, tolerated_light,
          watering, watering_freq, fertilizer_freq,
          fertilizer_instructions, toxic_to_people, toxic_to_pets, diseases))

conn.commit()

# Verify
cursor.execute('SELECT COUNT(*) FROM plant_types')
print(f'plant_types: {cursor.fetchone()[0]} records')

conn.close()