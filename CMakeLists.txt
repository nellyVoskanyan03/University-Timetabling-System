cmake_minimum_required(VERSION 3.14)
project(UniversityTimetablingSystem)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Fetch nlohmann/json
include(FetchContent)
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add executable
add_executable(
  UniversityTimetablingSystem
  src/UniversityTimetablingSystem.cpp
  src/Course.cpp
  src/Instructor.cpp
  src/University.cpp
  src/TimeSlot.cpp
  src/TimetableComponent.cpp
  test/TimetableTest.cpp
)

# Link libraries
target_link_libraries(
  UniversityTimetablingSystem
  PRIVATE
  nlohmann_json::nlohmann_json
  GTest::gtest_main
)


# Enable testing and add tests
enable_testing()
include(GoogleTest)
gtest_discover_tests(UniversityTimetablingSystem)