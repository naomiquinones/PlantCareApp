# Development only — seed file for testing
# Do not include in production setup
# Run manually: python3 data/seed_my_plants.py

import sqlite3

conn = sqlite3.connect('data/plants.db')
cursor = conn.cursor()

# Clear existing data first
cursor.execute('DELETE FROM my_plants')

plants = [
    # id, common_name, scientific_name (latin), last_watered, last_fertilized, pot_size, rootbound, notes, watering_override, fertilizer_override
    (1, 'Neon Pothos', 'Epipremnum aureum', '2026-05-20', '2026-05-20', '6in', 0, 'Kitchen shelf', None, None),
    (2, 'Marble Queen Pothos', 'Epipremnum aureum', '2026-05-20', '2026-05-20', '6in', 0, 'Living room', None, None),
    (3, 'Green Pothos', 'Epipremnum aureum', '2026-05-20', '2026-05-20', '6in', 0, '', None, None),
    (4, "Burro's Tail", 'Sedum morganianum', '2026-05-20', '2026-05-20', '4in', 0, 'Hanging planter', None, None),
    (5, 'Kalanchoe', 'Kalanchoe blossfeldiana', '2026-05-20', '2026-05-20', '3in', 0, '', None, None),
    (6, 'Succulents', 'Various', '2026-05-20', '2026-05-20', 'mixed', 0, 'Mixed pot', None, None),
    (7, 'Areca Palm', 'Dypsis lutescens', '2026-05-19', '2026-05-19', '10in', 0, 'Corner', None, None),
    (8, 'Neanthe Bella Palm', 'Chamaedorea elegans', '2026-05-19', '2026-05-19', '8in', 0, '', None, None),
    (9, 'Bromeliad', 'Aechmea fasciata', '2026-05-20', '2026-05-20', '5in', 0, '', None, None),
    (10, 'String of Pearls', 'Senecio rowleyanus', '2026-05-20', '2026-05-20', '3in', 0, 'Bright window', None, None),
    (11, 'Polka Dot Plant', 'Hypoestes phyllostachya', '2026-05-20', '2026-05-20', '4in', 0, '', None, None),
    (12, 'Tradescantia Nanouk', 'Tradescantia fluminensis', '2026-05-20', '2026-05-20', '4in', 0, '', None, None),
    (13, 'Callisia Pink Panther', 'Callisia repens', '2026-05-20', '2026-05-20', '4in', 0, '', None, None),
    (14, 'Maranta Leuconeura', 'Maranta leuconeura erythroneura', '2026-05-20', '2026-05-20', '5in', 0, '', None, None),
    (15, 'Dracaena Tricolor', 'Dracaena marginata', '2026-05-20', '2026-05-20', '8in', 0, '', None, None),
    (16, 'Spider Plant', 'Chlorophytum comosum', '2026-05-20', '2026-05-20', '6in', 0, '', None, None),
    (17, 'Orchid', 'Phalaenopsis X', '2026-05-20', '2026-05-20', '4in', 0, '', None, None),
    (18, 'Air Plants', 'Tillandsia', '2026-05-20', '2026-05-20', 'n/a', 0, 'Mounted', None, None),
]

for p in plants:
    (pid, common_name, scientific_name, last_watered, last_fertilized, pot_size, rootbound, notes, water_override, fert_override) = p

    # Try to find plant_type_id by latin_name
    plant_type_id = None
    if scientific_name and scientific_name.lower() != 'various' and scientific_name.lower() != 'n/a':
        cursor.execute('SELECT id FROM plant_types WHERE latin_name = ?', (scientific_name,))
        row = cursor.fetchone()
        if row:
            plant_type_id = row[0]

    cursor.execute('''
        INSERT OR REPLACE INTO my_plants (
            id, common_name, scientific_name, plant_type_id, last_watered, last_fertilized,
            pot_size, rootbound, notes, watering_frequency_days_override, fertilizer_frequency_days_override
        ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    ''', (
        pid, common_name, scientific_name, plant_type_id, last_watered, last_fertilized,
        pot_size, rootbound, notes, water_override, fert_override
    ))

conn.commit()
print(f'Seeded {len(plants)} plants into my_plants')
conn.close()