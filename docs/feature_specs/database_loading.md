# Load Plants

## Problem statement

Currently, plants are hardcoded in `main.cpp`. After this feature,
the application will load `PlantType` records from `plant_types`
and user plants from `my_plants` into memory at startup so the user
can view their saved plants without manually creating them in code.

## Types involved

### PlantType

- Created from rows in `plant_types`
- Reads: `id`, `latin_name`, `watering_frequency_days`,
  `fertilizer_frequency_days`, light requirements, toxicity,
  and other plant metadata

### Plant

- Created from rows in `my_plants`
- Reads: `common_name`, `scientific_name`,
  `plant_type_id`, `last_watered`,
  `last_fertilized`, `pot_size`,
  `rootbound`, `notes`,
  `watering_frequency_days_override`,
  `fertilizer_frequency_days_override`

### PlantCollection

- Stores loaded objects in memory
- Uses `addPlant()` and `addPlantType()`

### DatabaseHandler

- Opens/closes SQLite connection
- Queries `plant_types` and `my_plants`
- Creates objects and adds them to the collection

## Public interface

```cpp
bool DatabaseHandler::open();

void DatabaseHandler::close();

bool DatabaseHandler::loadPlantTypes(
    PlantCollection& collection
);

bool DatabaseHandler::loadPlants(
    PlantCollection& collection
);
```

## Inputs and outputs

### User input

- No direct user input.
- Feature runs automatically at program startup.

### Program output

- If loading succeeds, plants are available in
  "View all plants".
- If the database cannot be opened, print an
  error message.
- If `my_plants` is empty, no plants are displayed,
  but the program still runs normally.

### Function behavior

- `open()` returns `true` on successful connection.
- `loadPlantTypes(collection)` populates the
  collection with `PlantType*`.
- `loadPlants(collection)` populates the collection
  with `Plant*`.
- `close()` shuts down the connection.

## Edge cases

1. Database file is missing, unreadable, or not a valid SQLite database.
2. Missing tables (plant_types, my_plants) because `setup.sh` was not run or only partially completed.
3. `plant_types` is empty.
4. `my_plants` is empty (new user with no saved plants).
5. `loadPlantTypes()` or `loadPlants()` is called before `open()`.
6. `open()` or `close()` is called multiple times.
7. A `plant_type_id` in `my_plants` does not match a row in `plant_types`.
8. A database row contains `NULL` values where strings or numbers are expected.
9. `loadPlantTypes()` or `loadPlants()` is called more than once, potentially creating duplicate in-memory objects.

## Three test cases

### 1. Normal operation

Open a database with known rows in `plant_types` and `my_plants`.

Assert:

- `open()` returns true
- `loadPlantTypes()` returns true
- `loadPlants()` returns true
- `collection.getPlantTypeCount()` matches expected number of rows in `plant_types`
- `collection.getCount()` matches expected number of rows in `my_plants`
- At least one known plant name (e.g., "Snake Plant") exists in the loaded plants
- loaded plant "Snake Plant" has correct scientific name "Dracaena trifasciata"

### 2. Edge case

Attempt to open a database path that does not exist.

Assert:

- `open()` returns false
- program does not crash

### 3. Boundary condition

Use a database where `my_plants` is empty.

Assert:

- `open()` succeeds
- `loadPlants()` returns true
- plant count is 0
- application still runs normally

## Design decisions

- Loading behavior: the main function creates a fresh PlantCollection at startup, replacing existing in-memory data rather than appending, to avoid duplicate objects on repeated loads.
- Invalid or missing `plant_type_id` values will not stop loading. Plants with missing types will still be loaded and may display a warning.
- NULL or missing database values will not crash the loader; default-initialized values will be used where necessary.
- The loader should prioritize successfully loading valid rows even if some rows cannot be fully processed.
