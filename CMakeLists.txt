cmake_minimum_required(VERSION 3.19)
project(PlantCareApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing
enable_testing()

# Find SQLite
find_package(SQLite3 REQUIRED)

# Create a library from your plant care logic
add_library(plant_lib
    src/Plant.cpp
    src/PlantType.cpp
    src/PlantCollection.cpp
    src/CareEvent.cpp
    src/DatabaseHandler.cpp
)

# Tell the compiler where to find header files
target_include_directories(plant_lib PUBLIC include)

# Link SQLite to the library
target_link_libraries(plant_lib SQLite::SQLite3)

# Create the main executable
add_executable(plantcareapp src/main.cpp)
target_link_libraries(plantcareapp plant_lib)

# Create the test executable
add_executable(run_tests tests/test_main.cpp)
target_link_libraries(run_tests plant_lib)

# Register tests with CTest
add_test(NAME PlantTests COMMAND run_tests)
