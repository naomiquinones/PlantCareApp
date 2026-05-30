# Final Reflection

## Initial thoughts

- Creating the code to load the database took the bulk of my available time at the beginning of this project, so only the first feature is done as of the beginning of this doc.

- I'm planning to work on Feature 2 now. Hopefully, I'll finish implementing it by the time I'm done filling out this doc.

| Feature | Status |
| ------- | ------ |
| Preloaded plant database with care info from Kaggle stored in SQLite | Done |
| Create and manage a personalized collection of owned plants | In progress |
| Plant types selectable from preloaded dataset or created by the user | Stubbed |
| Track plant care events (watering, fertilizing, repotting, pruning) | Stubbed |
| View plants currently needing watering or fertilization | Stubbed |
| Receive warning messages for overdue plant care when the app starts | Stubbed |

## What I am building for this submission

Feature 2: Create and manage a personalized collection of owned plants.

- The user will be able to add a new plant by entering a name and selecting a plant type from the preloaded database. The plant will be saved to my_plants and added to the in-memory PlantCollection.

## What I am not building for this submission

Features 3–6 remain stubbed. The moisture sensor feature was cut
at the start of the project and remains out of scope.

## Prompts

### 1: Plan vs. Reality

Due to time constraints, I didn't get as far with this as I'd imagined. Working with the database turned out to be different, as C++ doesn't have as many libraries as I'd initially thought for this. I thought I would find a library that could read json and csv files, but I kept finding that Python was easier for this part, and since it wasn't the main part of my project, I ended up using Python for the initial manipulation to get the data from the Kaggle datasets into the database.

As for the actual C++ I used, I was able to use what I learned in class, and I also learned to use the SQLiteCpp library. This library is actually fairly straightforward in that, once I got used to its functions, and getting the parentheses correct when embedding the SQL queries, I could understand what commands I was using to connect to the database.

After working on Feature 2, the state of the project is:

| Feature | Status |
| ------- | ------ |
| Preloaded plant database with care info from Kaggle stored in SQLite | Done |
| Create and manage a personalized collection of owned plants | Almost done |
| Plant types selectable from preloaded dataset or created by the user | Stubbed |
| Track plant care events (watering, fertilizing, repotting, pruning) | Stubbed |
| View plants currently needing watering or fertilization | Stubbed |
| Receive warning messages for overdue plant care when the app starts | Stubbed |

I plan to continue working on this project. I also plan to research how to connect wires to an arduino without soldering so I can add the soil moisture sensor I originally thought of.

#2: Design Decisions I Would Change

I'd like to investigate more options for manipulating the initial datasets in C++ so the whole project uses C++.

If I redid this, or if I continue working on this, I might revisit the DatabaseHandler. The file is over 200 lines long, and while that might be tiny compared to professional projects, I'm already having trouble keeping track of what it does. Perhaps splitting its functions will be better, for example splitting the connection work into a submodule or something like that.

With the Plant, I'd like to redo how to get the watering frequency. Right now, I'll need to get the plant_type_id, then go to the collection and use the findPlantType method, then get the plantType's watering frequency. Perhaps using a pointer to the PlantType from within the Plant would be more straightforward, but I'm not sure about this.
