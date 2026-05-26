# Initial Feature Test Cases

## Feature: Display

### Test 1: Normal Operation

- What it tests: Adding plants to a collection works
- Expected result: The correct number of plants is reported
- Result: Pass

### Test 2: Edge Case

- What it tests: Empty collection
- Expected result: There are no plants in the collection
- Result: Pass

### Test 3: Boundary Conditions

- What it tests: Adding a single plant
- Expected result: Plant count is 1
- Result: Pass

#### CTest Output

UpdateCTestConfiguration  from :/Users/naomiquinones/Documents/classes/2026 Spring/CIS25/PlantCareApp/build/DartConfiguration.tcl
Test project /Users/naomiquinones/Documents/classes/2026 Spring/CIS25/PlantCareApp/build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: PlantTests

1: Test command: /Users/naomiquinones/Documents/classes/2026\ Spring/CIS25/PlantCareApp/build/run_tests
1: Working Directory: /Users/naomiquinones/Documents/classes/2026 Spring/CIS25/PlantCareApp/build
1: Test timeout computed to be: 10000000
1: Running tests...
1:
1: test_plant_initialization: TODO
1: test_plant_needs_water: TODO
1: test_plant_needs_fertilizer: TODO
1: test_planttype_initialization: TODO
1: test_careevent_initialization: TODO
1: test_add_plants_normal
1: test_empty_collection
1: test_single_plant
1:
1: All tests completed.
1/1 Test #1: PlantTests .......................   Passed    0.37 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.38 sec
