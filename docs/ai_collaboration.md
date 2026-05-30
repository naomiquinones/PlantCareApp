# AI Collaboration Log

## Tools used

- Claude (claude.ai) for design, spec review, and implementation guidance
- GitHub Copilot Chat in VS Code for code suggestions
- ChatGPT for additional planning and comparison with Copilot and Claude
- Gemini for additional search, reference and examples

## A prompt that worked well

- "I've started the initial draft of the feature spec. Please evaluate it for thoroughness, accuracy, and adherence to the instructions." + initial draft text.
- Why it worked: Giving the schema and header files as context meant the AI could give specific answers tied to the actual codebase.

## A prompt that did not work

- Prompt: Asking the AI to review whether the CREATE TABLE SQL was correct
- What went wrong: The AI incorrectly identified missing C++ parentheses when the real problem was a missing SQL closing parenthesis inside the string. The AI was looking at the wrong layer of the code.
- How I recovered: Removed the try/catch block from the test so exceptions propagated visibly, rebuilt the project, and ran the tests to get the actual SQLite error message.

## Code I rejected

- The AI suggested using findPlantType() inside loadPlants() to verify plant type references during loading.
- I rejected it because the spec already says missing plant_type_id values are not fatal, and adding the lookup would complicate loadPlants() without any benefit at this stage. Type resolution can happen later during display.

## What I'd do differently next time

- Always rebuild with `cmake --build build` before running ctest. Running old compiled code caused tests to appear to pass when the source had errors, which wasted time debugging the wrong thing.

## Fresh-conversation review

- Used ChatGPT in a fresh conversation to review the PR diff.
- ChatGPT suggested many changes, several of which seemed out of scope for this feature.
- Asked Claude to evaluate the high-priority fixes ChatGPT identified.
- Claude agreed that `findPlantByName()` and `findPlant()` should be implemented, and that the test assertions should verify actual plant data, not just counts.
- Claude disagreed that `open()` needed to be made idempotent, since the spec explicitly defines returning false when already open.
- Decided to defer `findPlantByName()`, `findPlant()`, and the stronger test assertions to a future feature, since they are not required to make database loading work correctly for this PR.
- Did not apply the `unique_ptr` refactor or memory leak suggestions, as they are out of scope for this assignment.
