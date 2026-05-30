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

### 2: Design Decisions I Would Change

I'd like to investigate more options for manipulating the initial datasets in C++ so the whole project uses C++.

If I redid this, or if I continue working on this, I might revisit the DatabaseHandler. The file is over 200 lines long, and while that might be tiny compared to professional projects, I'm already having trouble keeping track of what it does. Perhaps splitting its functions will be better, for example splitting the connection work into a helper class or something like that.

With the Plant, I'd like to redo how to get the watering frequency. Right now, I'll need to get the plant_type_id, then go to the collection and use the findPlantType method, then get the plantType's watering frequency. Perhaps using a pointer to the PlantType from within the Plant would be more straightforward, but I'm not sure about this.

### 3: What I Learned

**Technical**: I learned to use SQLiteCpp, the library for connecting to the SQLite database. For example, in order to iterate over various rows, it's necessary to use a while loop with `query.executeStep()`, which returns true as long as there are more rows, allowing the code to set each of the Plant object's fields from the data pulled out of the table in the database.
**Design**: Separation of concerns: Originally, I was going to have DatabaseHandler methods report problems, but in the end, decided to have them return false and have the main.cpp print the error message. When testing, we need to be careful when we use try-catch blocks, as they will hide errors in our test
**Process**: I appreciated having the CMake file. While I was researching more about where the CMake file came from, I came across a Physics department's tutorial on it, and their descriptions complemented what we learned in class. I also learned that for Apple Silicon Macs, the version needs to be higher. I also learned that it is necessary to run the `cmake --build build` command before running ctest.

## 4: What's Left to Finish

1. **`Plant::daysSinceWatered()` and `Plant::daysSinceFertilized()`** — these are needed before any care tracking or reminders can work.

2. **`PlantCollection::getPlantsNeedingWater()` and `getPlantsNeedingFertilizer()`** — these power the "View plants needing care" menu option and the startup warnings.

3. **Feature 3: Add custom plant type** — users need to be able to add plant types not in the preloaded database.

4. **Feature 4: Track plant care events** — watering, fertilizing, repotting, and pruning need to be logged to `care_events` and update `last_watered`/`last_fertilized` on the plant.

5. **Feature 5: View plants needing care** — depends on items 1 and 2 above being complete.

6. **Feature 6: Startup warnings** — depends on items 1 and 2, displays overdue plants when the app starts.

7. **`PlantCollection::findPlant()` and `removePlant()`** — needed for full CRUD functionality.

8. **`DatabaseHandler::updatePlant()`, `deletePlant()`, `logCareEvent()`, and `getCareHistory()`** — needed to persist care events and plant changes to the database.

9. **Add the Arduino soil moisture sensor integration** — the original inspiration for the app; would allow the sensor to confirm or update watering records automatically.

## 5: Workflow Reflection

I'm accustomed to making PRs. However, reviewing my own PRs was different. GitHub wouldn't let me do anything but comment since I was the author and reviewer. I think I understand why they restrict authors to only commenting. However, it would be useful if someone wanted to track their work and put reminders for themselves in the request for changes. This is not a problem when working with someone else, as they can review and put in the approval or the RFC.

## 6: AI Use

I used AI quite a bit more than I had expected to. As I was doing the initial research, Google's Gemini popped up answers and suggestions, and multiple times I went into the conversation box with it. I was able to click on the relevant links it showed to get more information, and this changed the way I research things. However, I'm not convinced that it is so helpful, as sometimes it gave answers that I didn't believe, and further research in the related links showed that it actually got its answers wrong.

I also tried ChatGPT, Claude, and GitHub Copilot, but found that they would often suggest changes that didn't make sense, or seemed out of scope. However, I found a GitHub page about Karpathy rules (I believe Karpathy is a big name in AI) that I pasted in to each AI tool I used. The rules were:

- Think before coding. State assumptions explicitly. If multiple interpretations
exist, present them — don't pick silently. If something is unclear, stop and ask.

- Simplicity first. Minimum code that solves the problem. No speculative features,
no abstractions for single-use code, no "flexibility" that wasn't requested. If 200
lines could be 50, rewrite it.

- Surgical changes. Touch only what was asked. Don't "improve" adjacent code or
refactor things that aren't broken. Match existing style. Remove imports/variables
made unused by YOUR changes only — don't clean up pre-existing dead code unless asked.

- Goal-driven execution. Define success criteria before coding. For multi-step
tasks, state a brief plan with verifiable checkpoints.

I'm not sure I noticed too much difference but it could have been due to my lack of knowledge on how best to use these tools.
