add_library(UniversitySheduler
  Course.cpp
  Instructor.cpp
  University.cpp
  TimeSlot.cpp
  TimetableComponent.cpp
  Course.h
  Instructor.h
  University.h
  TimeSlot.h
  TimetableComponent.h
)

target_link_libraries(UniversitySheduler nlohmann_json::nlohmann_json)