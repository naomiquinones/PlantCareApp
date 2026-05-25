#!/usr/bin/env python3
"""
Migration helper for PlantCareApp SQLite schema.

This script will:
- Add missing columns to `plant_types` and `my_plants` if they don't exist.
- Migrate the `factors` table to use numeric types and normalized column names
  (e.g. `Humidity_%` -> `Humidity_pct`) by creating a new table, copying
  converted data, and replacing the old table.

Run: python3 data/migrate_schema.py
"""

import sqlite3
import sys

DB_PATH = 'data/plants.db'


def has_column(cursor, table, column):
    cursor.execute("PRAGMA table_info('%s')" % table)
    cols = [r[1] for r in cursor.fetchall()]
    return column in cols


def add_column_if_missing(cursor, table, column_def):
    # column_def is like "col_name TYPE DEFAULT 0"
    col_name = column_def.split()[0]
    if not has_column(cursor, table, col_name):
        print(f"Adding column {col_name} to {table}")
        cursor.execute(f"ALTER TABLE {table} ADD COLUMN {column_def}")
    else:
        print(f"Column {col_name} already exists on {table}")


def migrate_factors(cursor):
    # If the target column name already exists, skip migration
    if not has_column(cursor, 'factors', 'Plant_ID'):
        print('No factors table found; skipping factors migration')
        return

    if has_column(cursor, 'factors', 'Humidity_pct'):
        print('factors table already migrated (Humidity_pct exists)')
        return

    print('Migrating factors table to normalize types and column names...')

    cursor.execute('''
    CREATE TABLE IF NOT EXISTS factors_new (
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
    )
    ''')

    # Copy data with casting; handle old column names like "Humidity_%" and "Soil_Moisture_%"
    copy_sql = '''
    INSERT INTO factors_new (
        Plant_ID, Height_cm, Leaf_Count, New_Growth_Count, Health_Notes,
        Watering_Amount_ml, Watering_Frequency_days, Sunlight_Exposure,
        Room_Temperature_C, Humidity_pct, Fertilizer_Type, Fertilizer_Amount_ml,
        Pest_Presence, Pest_Severity, Soil_Moisture_pct, Soil_Type, Health_Score
    )
    SELECT
        Plant_ID,
        CAST(NULLIF(Height_cm, '') AS REAL),
        CAST(NULLIF(Leaf_Count, '') AS INTEGER),
        CAST(NULLIF(New_Growth_Count, '') AS INTEGER),
        Health_Notes,
        CAST(NULLIF(Watering_Amount_ml, '') AS REAL),
        CAST(NULLIF(Watering_Frequency_days, '') AS INTEGER),
        Sunlight_Exposure,
        CAST(NULLIF(Room_Temperature_C, '') AS REAL),
        CAST(NULLIF(REPLACE("Humidity_%", '%', ''), '') AS REAL),
        Fertilizer_Type,
        CAST(NULLIF(Fertilizer_Amount_ml, '') AS REAL),
        Pest_Presence,
        Pest_Severity,
        CAST(NULLIF(REPLACE("Soil_Moisture_%", '%', ''), '') AS REAL),
        Soil_Type,
        CAST(NULLIF(Health_Score, '') AS REAL)
    FROM factors
    '''

    cursor.execute(copy_sql)

    # Replace old table
    cursor.execute('DROP TABLE factors')
    cursor.execute('ALTER TABLE factors_new RENAME TO factors')
    print('factors table migrated')


def main():
    conn = sqlite3.connect(DB_PATH)
    cur = conn.cursor()

    try:
        # Add recommended columns to plant_types
        add_column_if_missing(cur, 'plant_types', 'common_names TEXT')
        add_column_if_missing(cur, 'plant_types', 'watering_frequency_days INTEGER')
        add_column_if_missing(cur, 'plant_types', 'fertilizer_frequency_days INTEGER')
        add_column_if_missing(cur, 'plant_types', 'fertilizer_instructions TEXT')
        add_column_if_missing(cur, 'plant_types', 'toxic_to_people INTEGER DEFAULT 0')
        add_column_if_missing(cur, 'plant_types', 'toxic_to_pets INTEGER DEFAULT 0')

        # Add recommended columns to my_plants
        add_column_if_missing(cur, 'my_plants', 'plant_type_id INTEGER')
        add_column_if_missing(cur, 'my_plants', 'pot_size TEXT')
        add_column_if_missing(cur, 'my_plants', 'rootbound INTEGER DEFAULT 0')
        add_column_if_missing(cur, 'my_plants', 'notes TEXT')
        add_column_if_missing(cur, 'my_plants', 'watering_frequency_days_override INTEGER')
        add_column_if_missing(cur, 'my_plants', 'fertilizer_frequency_days_override INTEGER')

        migrate_factors(cur)

        conn.commit()
        print('Migration completed successfully.')
    except Exception as e:
        print('Migration failed:', e)
        conn.rollback()
        sys.exit(1)
    finally:
        conn.close()


if __name__ == '__main__':
    main()
