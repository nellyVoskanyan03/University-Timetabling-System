# CMakeList.txt : CMake project for University Timetabling System, include source and define
# project specific logic here.
#

# Add source to this project's executable.@
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable (CMakeTarget "src/UniversityTimetablingSystem.cpp" "include/UniversityTimetablingSystem.h" "src/Course.cpp" "src/Instructor.cpp" "src/University.cpp" "include/Course.h" "include/Instructor.h" "include/University.h" "include/TimeSlot.h" "src/TimeSlot.cpp" "src/TimetableComponent.cpp" "include/TimetableComponent.h" "include/TimeSlotInstructorPair.h")

target_link_libraries(CMakeTarget PRIVATE nlohmann_json::nlohmann_json)

include_directories(include)



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
