import csv
import sqlite3

conn = sqlite3.connect('data/plants.db')
cursor = conn.cursor()

def clean_num(val):
    if val is None:
        return None
    v = val.strip()
    if v == '':
        return None
    # strip percent signs and commas
    v = v.replace('%', '').replace(',', '')
    try:
        if '.' in v:
            return float(v)
        return int(v)
    except ValueError:
        try:
            return float(v)
        except Exception:
            return None

rows = []
with open('data/Indoor_Plant_Health_and_Growth_Factors.csv', encoding='utf-8') as f:
    reader = csv.DictReader(f)
    for row in reader:
        rows.append((
            row.get('Plant_ID'),
            clean_num(row.get('Height_cm')),
            clean_num(row.get('Leaf_Count')),
            clean_num(row.get('New_Growth_Count')),
            row.get('Health_Notes'),
            clean_num(row.get('Watering_Amount_ml')),
            clean_num(row.get('Watering_Frequency_days')),
            row.get('Sunlight_Exposure'),
            clean_num(row.get('Room_Temperature_C')),
            clean_num(row.get('Humidity_%')),
            row.get('Fertilizer_Type'),
            clean_num(row.get('Fertilizer_Amount_ml')),
            row.get('Pest_Presence'),
            row.get('Pest_Severity'),
            clean_num(row.get('Soil_Moisture_%')),
            row.get('Soil_Type'),
            clean_num(row.get('Health_Score'))
        ))

cursor.executemany('''
    INSERT INTO factors (
        Plant_ID, Height_cm, Leaf_Count, New_Growth_Count, Health_Notes,
        Watering_Amount_ml, Watering_Frequency_days, Sunlight_Exposure,
        Room_Temperature_C, Humidity_pct, Fertilizer_Type, Fertilizer_Amount_ml,
        Pest_Presence, Pest_Severity, Soil_Moisture_pct, Soil_Type, Health_Score
    ) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)
''', rows)

conn.commit()
print(f'Imported {cursor.rowcount} rows into factors')
conn.close()