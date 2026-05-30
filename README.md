# PlantCareApp

Allows a plant owner to take better care of their plants

## Feature List

- Preloaded plant database with care information (watering, fertilizer, light, toxicity, etc.) stored in SQLite.
- Create and manage a personalized collection of owned plants.
- Add plants not included in the original database.
- Track plant care events (watering, fertilizing, repotting, pruning).
- View plants currently needing watering or fertilization.
- Receive warning messages for overdue plant care when the app starts.

## Current Status

**Implemented:**

- Database loading: plant types and plants load from SQLite at startup
- View all plants (menu option 2)

**Stubbed (not yet implemented):**

- Add a plant, update plant care, add custom plant type, view plants needing care, startup warnings

## Database Setup (one-time)

```bash
cd data && bash setup.sh
```

## How to Build

```bash
cmake -S . -B build
cmake --build build
```

## How to Run

```bash
./build/plantcareapp
```

## How to Test

```bash
ctest --test-dir build --verbose
```

## Author

Naomi Quinones - CIS 25 Final Project
