# University Timetabling System
The University Timetabling System is designed to efficiently schedule courses for a university while assigning instructors based on their availability and expertise. The system aims to satisfy hard constraints and as many soft constraints as possible to generate an optimal timetable.

### Hard constraints:
- Each course must be scheduled exactly once in an available time slot and assigned to an instructor
- An instructor can only be assigned to a course if they are available during the corresponding time slot
- An instructor cannot be scheduled to teach more than one course in the same time slot

### Soft constraints:
- Courses should be scheduled in preferred time slots if possible
- Instructors should be assigned to their preferred courses if possible

See more details about the assignment by [this](https://docs.google.com/document/d/1iGzcBMqbpLfBhPh7xrKGplsiqojhlKjDzB4THlBh2ho/edit?usp=sharing) link.


## Installation and Setup
This is a **CMake** project.

To build this project, you can simply run folowing commands
 ```sh
cmake -S . -B build
cmake --build build
cd build/
./UniversityTimetablingSystem
```

## Algorithms used

Algorithm creates all possible schedules that satisfy all hard constraints and chooses the one that satisfy as many soft constraints as possible. The algorithm operates as follows:

