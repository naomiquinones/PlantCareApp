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

These were increased after discussion with AI:

1. Database file does not exist.
2. Database file exists but is unreadable or not a valid SQLite database.
3. Required tables do not exist because `setup.sh` was not run or only partially completed.
4. `plant_types` is empty.
5. `my_plants` is empty (new user with no saved plants).
6. `loadPlantTypes()` or `loadPlants()` is called before `open()`.
7. `open()` or `close()` is called multiple times.
8. A `plant_type_id` in `my_plants` does not match a row in `plant_types`.
9. A database row contains `NULL` values where strings or numbers are expected.
10. `loadPlantTypes()` or `loadPlants()` is called more than once, potentially creating duplicate in-memory objects.

## Three test cases

### 1. Normal operation

Open a database with known rows in `plant_types`
and `my_plants`.

Assert:

- `open()` returns true
- `loadPlantTypes()` returns true
- `loadPlants()` returns true
- collection contains expected counts
- loaded plant names match expected values

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

Discussed the following with the AI:

- Loading behavior: `loadPlantTypes()` and `loadPlants()` append to the existing `PlantCollection` rather than clearing it. The caller is responsible for avoiding duplicate loads.
- Invalid or missing `plant_type_id` values will not stop loading. Plants with missing types will still be loaded and may display a warning.
- `NULL` database values will load as sensible defaults (empty strings, `0`, or `false`) instead of crashing.
- Invalid date strings will be loaded as-is. Date validation will be handled later when date calculations are implemented.
- If one database row is malformed, the loader should continue loading other valid rows whenever possible.
