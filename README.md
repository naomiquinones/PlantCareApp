# PlantCareApp
Allows a plant owner to take better care of their plants

## Feature List
- Preloaded plant database with care information (watering, fertilizer, light, toxicity, etc.) stored in SQLite.
- Create and manage a personalized collection of owned plants.
- Add plants not included in the original database.
- Track plant care events (watering, fertilizing, repotting, pruning).
- View plants currently needing watering or fertilization.
- Receive warning messages for overdue plant care when the app starts.

## How to Build
```
cmake -S . -B build
cmake --build build
```

## How to Run
```
./build/plantcareapp
```

## How to Test
```
ctest --test-dir build --verbose
```

## Author
Naomi Quinones - CIS 25 Final Project
