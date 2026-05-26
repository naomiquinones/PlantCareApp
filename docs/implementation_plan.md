# Implementation Plan

## Feature 1: Preloaded Plant Database

**Trigger**: Program startup (first run)

On startup, the program checks whether the SQLite database is available and opens it through `DatabaseHandler`. Plant species data from the Kaggle dataset is preloaded during setup and stored in the `plant_types` table. This provides a built-in reference of plant care information such as watering frequency, light requirements, and toxicity.

## Feature 2: Create and Manage Personal Plant Collection

**Trigger**: User selects "Add a plant" from main menu

Prompts the user for a plant nickname, then displays available plant types from the plant_types table. A Plant object is created and linked to the selected PlantType. The plant is stored in the my_plants table and added to the in-memory PlantCollection.

## Feature 3: Add Custom Plant Type

**Trigger**: User selects "Add custom plant type" from main menu

Prompts the user to enter plant species information including name, watering frequency, fertilizer frequency, light requirements, and toxicity. A new PlantType object is created and saved to the plant_types table so it can be used when adding future plants.

## Feature 4: Track Plant Care Events

**Trigger**: User selects a plant care action (water, fertilize, repot, prune) from the "Update plant records" submenu

When a care action is selected, the program creates a `CareEvent` record in the `care_events` table to maintain a history of plant care activities. Watering and fertilizing actions also update the plant’s `last_watered` or `last_fertilized` date in `my_plants`, while pruning and repotting are recorded for future reference.

## Feature 5: View Plants Needing Care

**Trigger**: User selects "View plants needing water/fertilizer" from main menu

PlantCollection checks each plant’s last watered and last fertilized dates and compares them to the appropriate watering and fertilizer schedule.

The program uses the plant’s personal override values if set; otherwise it falls back to the associated `PlantType` defaults.

Plants that exceed their recommended care interval are displayed as needing attention.

## Feature 6: Startup Warnings for Overdue Care

**Trigger**: Program startup, after database loads

After loading data from the database, the program checks all plants for overdue care. If any plant is more than 3 days overdue based on its watering or fertilizing schedule (including override logic where applicable), a warning message is displayed listing each plant and how long it has been overdue.
