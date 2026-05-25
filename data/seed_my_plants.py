# Development only — seed file for testing
# Do not include in production setup
# Run manually: python3 data/seed_my_plants.py

import sqlite3

conn = sqlite3.connect('data/plants.db')
cursor = conn.cursor()

# Clear existing data first
cursor.execute('DELETE FROM my_plants')

plants = [
    (1, 'Neon Pothos', 'Epipremnum aureum', '2026-05-20', '2026-05-20'),
    (2, 'Marble Queen Pothos', 'Epipremnum aureum', '2026-05-20', '2026-05-20'),
    (3, 'Green Pothos', 'Epipremnum aureum', '2026-05-20', '2026-05-20'),
    (4, "Burro's Tail", 'Sedum morganianum', '2026-05-20', '2026-05-20'),
    (5, 'Kalanchoe', 'Kalanchoe blossfeldiana', '2026-05-20', '2026-05-20'),
    (6, 'Succulents', 'Various', '2026-05-20', '2026-05-20'),
    (7, 'Areca Palm', 'Dypsis lutescens', '2026-05-19', '2026-05-19'),
    (8, 'Neanthe Bella Palm', 'Chamaedorea elegans', '2026-05-19', '2026-05-19'),
    (9, 'Bromeliad', 'Aechmea fasciata', '2026-05-20', '2026-05-20'),
    (10, 'String of Pearls', 'Senecio rowleyanus', '2026-05-20', '2026-05-20'),
    (11, 'Polka Dot Plant', 'Hypoestes phyllostachya', '2026-05-20', '2026-05-20'),
    (12, 'Tradescantia Nanouk', 'Tradescantia fluminensis', '2026-05-20', '2026-05-20'),
    (13, 'Callisia Pink Panther', 'Callisia repens', '2026-05-20', '2026-05-20'),
    (14, 'Maranta Leuconeura', 'Maranta leuconeura erythroneura', '2026-05-20', '2026-05-20'),
    (15, 'Dracaena Tricolor', 'Dracaena marginata', '2026-05-20', '2026-05-20'),
    (16, 'Spider Plant', 'Chlorophytum comosum', '2026-05-20', '2026-05-20'),
    (17, 'Orchid', 'Phalaenopsis X', '2026-05-20', '2026-05-20'),
    (18, 'Air Plants', 'Tillandsia', '2026-05-20', '2026-05-20'),
]

cursor.executemany('''
    INSERT INTO my_plants (id, common_name, scientific_name, last_watered, last_fertilized)
    VALUES (?, ?, ?, ?, ?)
''', plants)

conn.commit()
print(f'Seeded {len(plants)} plants into my_plants')
conn.close()