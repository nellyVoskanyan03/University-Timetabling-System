cmake_minimum_required(VERSION 3.14)
project(UniversityTimetablingSystem)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable RTTI (by default it should be enabled, but let's make sure)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")

add_subdirectory(include)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(json/json)

target_link_libraries(UniversitySheduler PRIVATE nlohmann_json::nlohmann_json)

# Add executable
add_executable(
  UniversityTimetablingSystem
  src/UniversityTimetablingSystem.cpp
)

# Link libraries
target_link_libraries(UniversityTimetablingSystem UniversitySheduler)

# Ensure RTTI is enabled for GoogleTest
target_compile_options(UniversityTimetablingSystem PRIVATE -frtti)

# Enable testing and add tests


set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)
add_subdirectory(test/gtest/googletest)
target_compile_definitions(gtest
  PUBLIC
    GTEST_LANG_CXX20
    GTEST_HAS_TR1_TUPLE=0
)
add_executable(tests)
target_sources(tests
  PRIVATE
   test/TimetableTest.cpp
)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "${cxx_strict}")
target_link_libraries(tests PRIVATE gtest gtest_main nlohmann_json::nlohmann_json UniversitySheduler)

