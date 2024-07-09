# CMakeList.txt : CMake project for University Timetabling System, include source and define
# project specific logic here.
#

# Add source to this project's executable.@
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable (CMakeTarget "src/UniversityTimetablingSystem.cpp"  "src/Course.cpp" "src/Instructor.cpp" "src/University.cpp" "include/Course.h" "include/Instructor.h" "include/University.h" "include/TimeSlot.h" "src/TimeSlot.cpp" "src/TimetableComponent.cpp" "include/TimetableComponent.h" "include/TimeSlotInstructorPair.h" "test/TimetableTest.cpp")

target_link_libraries(CMakeTarget PRIVATE nlohmann_json::nlohmann_json GTest::gtest_main)

include_directories(include)



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


include(googleTest)
gtest_discover_tests(CMakeTarget)
