cmake_minimum_required(VERSION 3.19)
project(PlantCareApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing
enable_testing()

# Fetch SQLiteCpp
include(FetchContent)
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG        3.3.3
)
FetchContent_MakeAvailable(SQLiteCpp)

# Create a library from your plant care logic
add_library(plant_logic
    src/Plant.cpp
    src/PlantType.cpp
    src/PlantCollection.cpp
    src/CareEvent.cpp
    src/DatabaseHandler.cpp
)

# Tell the compiler where to find header files
target_include_directories(plant_logic PUBLIC include)

# Link SQLiteCpp to the library
target_link_libraries(plant_logic SQLiteCpp)

# Create the main executable
add_executable(plantcareapp src/main.cpp)
target_link_libraries(plantcareapp plant_logic)

# Create the test executable
add_executable(run_tests tests/test_main.cpp)
target_link_libraries(run_tests plant_logic)

# Register tests with CTest
add_test(NAME PlantTests COMMAND run_tests)