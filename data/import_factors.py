import csv
import sqlite3

conn = sqlite3.connect('data/plants.db')
cursor = conn.cursor()

with open('data/Indoor_Plant_Health_and_Growth_Factors.csv', encoding='utf-8') as f:
    reader = csv.DictReader(f)
    rows = [(
        row['Plant_ID'],
        row['Height_cm'],
        row['Leaf_Count'],
        row['New_Growth_Count'],
        row['Health_Notes'],
        row['Watering_Amount_ml'],
        row['Watering_Frequency_days'],
        row['Sunlight_Exposure'],
        row['Room_Temperature_C'],
        row['Humidity_%'],
        row['Fertilizer_Type'],
        row['Fertilizer_Amount_ml'],
        row['Pest_Presence'],
        row['Pest_Severity'],
        row['Soil_Moisture_%'],
        row['Soil_Type'],
        row['Health_Score']
    ) for row in reader]

cursor.executemany('''
    INSERT INTO factors VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)
''', rows)

conn.commit()
print(f'Imported {cursor.rowcount} rows into factors')
conn.close()