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

## Design decisions

Chosen approach:
`DatabaseHandler` will read existing SQLite data
created by `setup.sh` rather than creating the
database itself.

Reason:
The database schema and import process already
exist and were approved in the project plan.
This feature focuses on loading data into memory
for use by the application.

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

1. Database file doesn't exist
2. Tables don't exist (setup.sh was never run)
3. my_plants is empty (new user, no plants yet)
4. A plant references a plant_type_id that doesn't exist in plant_types

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
