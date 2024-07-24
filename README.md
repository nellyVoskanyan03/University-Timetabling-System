# University Timetabling System
The University Timetabling System is designed to efficiently schedule courses for a university while assigning instructors based on their availability and preferences. The system aims to satisfy hard constraints and as many soft constraints as possible to generate an optimal timetable. Unit tests are implemented using the Google Test (gtest) framework to ensure the correctness and reliability of the scheduling algorithms and constraints handling.

See the constraints and more details about the assignment by [this](https://docs.google.com/document/d/1iGzcBMqbpLfBhPh7xrKGplsiqojhlKjDzB4THlBh2ho/edit?usp=sharing) link.


## Installation and Setup
### Cloning the Repository
Use the following command to clone the repository and initialize its submodules (googleTest and nlohmann_json):
```sh
git clone --recurse-submodules https://github.com/nellyVoskanyan03/University-Timetabling-System.git
```
This is a **CMake** project. To build this project, you can simply run following commands

 ```sh
cmake -S . -B build
cmake --build build
cd build/
./UniversityTimetablingSystem
```

## Docker Setup

### Prerequisites
Ensure Docker is installed on your system.

### Building and running  the Docker Image
To build and run the Docker image for the University Timetabling System, run the following command in the root directory of the project:

```sh
docker build -t university-timetabling-system .

docker run --rm -it \
    -v /path/to/local/directory/target_file.json:/usr/src/app/result.json \
    university-timetabling-system
```
`-v /path/to/local/directory/target_file.json:/usr/src/app/result.json`: Mounts a specific local JSON file to the container’s /usr/src/app/result.json path. Replace /path/to/local/directory/target_file.json with the actual path to your JSON file which contains the university state. The generated timetable will be saved as result.json in the same mounted directory.

### Running Tests
The Docker container is configured to run unit tests before executing the main application. The run.sh script will:
- Execute the test suite.
- If all tests pass, it will run the main application.

## Algorithms used

Algorithm creates all possible schedules that satisfy all hard constraints and chooses the one that satisfy as many soft constraints as possible. The algorithm operates as follows:

1. Create Time Slot-Instructor Pairs:

The function starts by calling `makeTimeSlotInstructorPairs(instructors)`, which generates all possible pairs of time slots and instructors based on their availability.
Each pair is represented as a `TimeSlotInstructorPair` object that contains a time slot, an instructor, and a boolean flag indicating whether the pair is used.

2. Generate All Possible Timetables:

The function calls `makePossibleTimetables(timeSlotInstructorPairs, courses, currSchedule, possibleSchedules)`, which is a recursive function that generates all possible schedules using a backtracking algorithm. This function selects all possible combinations of size 𝐶 (number of courses) from the `timeSlotInstructorPairs` vector, assigns them to the courses, and stores the resulting schedules in the `possibleSchedules` vector.

3. Evaluate and Select the Best Schedule:

After generating all possible schedules, the function evaluates each schedule's fitness by calling the `fitness` function:
The fitness function calculates a fitness value based on how well the schedule matches instructors' preferred courses and courses' preferred time slots.
The function keeps track of the schedule with the highest fitness value.

4. Return the Best Schedule:

The best schedule found is assigned to the `timeTable` attribute of the `University` object.
The function returns this best schedule.

### Time Complexity

#### Definitions
 - *`I`* is te number of instructers
 - *`A`* is the average number of available time slots per instructor
 - *`N = I * A`* is the number of instructor time slot pairs
 - *`C`* is the number of courses.
 
 #### Complexity 
- Time Slot-Instructor Pairs Generation: *`O(I * A)`*
- Combination Generation: *`O(N! / C!(N-C)!)`*
- Fitness Evaluation per Combination: *`O(C)`*
- Total Complexity: *`O(C * N! / C!(N-C)!)`*
  
## Testing

This project uses Google Test, a popular C++ testing framework, for unit testing. The tests cover functionality related to the TimeSlot, Course, Instructor, and University classes, focusing on scheduling courses within specified time slots and instructor availability.

### Test Cases

#### University Class Tests

- **AddCourse**: Tests the addition of a `Course` to the `University` and confirms its presence in the list of courses.
- **AddInstructor**: Validates the addition of an `Instructor` to the `University` and ensures it is correctly stored.
- **AddTimeSlot**: Checks the addition of a `TimeSlot` to the `University` and verifies its inclusion in the list of time slots.
- **ScheduleBasic**: Tests the scheduling algorithm of the `University` class with predefined courses, instructors, and time slots, ensuring correct scheduling behavior.
- **ScheduleComplex**: Tests the scheduling algorithm with a more complex scenario involving multiple courses, instructors, and preferred time slots.
- **SaveAndLoadState**: Verifies the functionality to save the state of the `University` object to a file in JSON format and then load it back, ensuring consistency of data.

#### TimeSlot Class Tests

- **CreateTimeSlot**: Verifies the creation of a `TimeSlot` instance with specific day, start time, and end time attributes.

#### Course Class Tests

- **CreateCourse**: Ensures the correct initialization of a `Course` object with a given course name.
- **AddPreferredTimeSlot**: Tests the functionality to add preferred time slots to a `Course` and verifies the addition and retrieval of these time slots.

#### Instructor Class Tests

- **CreateInstructor**: Checks the initialization of an `Instructor` object with a specified name.
- **AddAvailability**: Tests the ability to add availability time slots to an `Instructor` and validates the process.
- **AddPreferredCourse**: Verifies that a `Course` can be added to an `Instructor`'s list of preferred courses.
