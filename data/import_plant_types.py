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

    # Insert into plant_types
    cursor.execute('''
        INSERT OR IGNORE INTO plant_types 
        (latin_name, family, category, origin, climate, 
         temp_min_c, temp_max_c, ideal_light, tolerated_light, 
         watering, diseases)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    ''', (latin, family, category, origin, climate,
          tempmin, tempmax, ideal_light, tolerated_light,
          watering, diseases))

    # Get the id of the plant_type we just inserted
    plant_type_id = cursor.lastrowid

    # Insert pests into plant_pests
    insects = plant.get('insects', [])
    if isinstance(insects, list):
        for insect in insects:
            if insect and insect != 'N/A':
                cursor.execute('''
                    INSERT INTO plant_pests (plant_type_id, pest)
                    VALUES (?, ?)
                ''', (plant_type_id, insect))

    # Insert uses into plant_uses
    uses = plant.get('use', [])
    if isinstance(uses, list):
        for use in uses:
            if use:
                cursor.execute('''
                    INSERT INTO plant_uses (plant_type_id, use)
                    VALUES (?, ?)
                ''', (plant_type_id, use))

conn.commit()

# Verify
cursor.execute('SELECT COUNT(*) FROM plant_types')
print(f'plant_types: {cursor.fetchone()[0]} records')

cursor.execute('SELECT COUNT(*) FROM plant_pests')
print(f'plant_pests: {cursor.fetchone()[0]} records')

cursor.execute('SELECT COUNT(*) FROM plant_uses')
print(f'plant_uses: {cursor.fetchone()[0]} records')

conn.close()