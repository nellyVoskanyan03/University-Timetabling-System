# University Timetabling System

## Introduction

The University Timetabling System is designed to efficiently schedule courses for a university while assigning instructors based on their availability and expertise. The system aims to satisfy both hard and soft constraints to generate an optimal timetable.

## Features

- Schedule courses and assign instructors
- Save and load the state of the system
- Evaluate schedules based on hard and soft constraints

## Class Structure

### TimeSlot

Represents a time slot for scheduling courses.

| Attribute   | Type         | Description                        |
|-------------|--------------|------------------------------------|
| `day`       | `std::string`| The day of the week                |
| `startTime` | `std::string`| The start time of the time slot    |
| `endTime`   | `std::string`| The end time of the time slot      |

### Course

Represents a course that needs to be scheduled.

| Attribute               | Type                    | Description                         |
|-------------------------|-------------------------|-------------------------------------|
| `courseName`            | `std::string`           | The name of the course              |
| `preferredTimeSlots`    | `std::vector<TimeSlot>` | Preferred time slots for the course |

### Instructor

Represents an instructor who can teach courses and has specific availability.

| Attribute             | Type                    | Description                              |
|-----------------------|-------------------------|------------------------------------------|
| `name`                | `std::string`           | The name of the instructor               |
| `availability`        | `std::vector<TimeSlot>` | Time slots when the instructor is available |
| `preferredCourses`    | `std::vector<Course>`   | Preferred courses for the instructor     |

### University

Represents the combination of courses, instructors, and time slots.

| Attribute      | Type                          | Description                         |
|----------------|-------------------------------|-------------------------------------|
| `courses`      | `std::vector<Course>`         | List of courses to be scheduled     |
| `instructors`  | `std::vector<Instructor>`     | List of instructors available for scheduling |
| `timeSlots`    | `std::vector<TimeSlot>`       | List of available time slots        |
| `timeTable`    | `std::vector<TimetableComponent>` | The final scheduled timetable |

### TimeSlot Class

| Method                                        | Functionality |
|-----------------------------------------------|---------------|
| `TimeSlot(std::string day, std::string startTime, std::string endTime)` | Initializes a time slot with given day, start time, and end time. |
| `json toJson() const`                         | Converts the TimeSlot object to JSON format. |
| `static TimeSlot fromJson(json j)`             | Constructs a TimeSlot object from JSON data. |
| `void displayInfo() const`                    | Displays information about the time slot. |

### Course Class

| Method                                         | Functionality |
|-----------------------------------------------|---------------|
| `Course(std::string courseName)`               | Initializes a course with a given name. |
| `json toJson() const`                         | Converts the Course object to JSON format. |
| `static Course fromJson(json j)`               | Constructs a Course object from JSON data. |
| `void displayInfo() const`                    | Displays information about the course. |

### Instructor Class

| Method                                        | Functionality |
|-----------------------------------------------|---------------|
| `Instructor(std::string name)`                 | Initializes an instructor with a given name. |
| `json toJson() const`                         | Converts the Instructor object to JSON format. |
| `static Instructor fromJson(json j)`           | Constructs an Instructor object from JSON data. |
| `void displayInfo() const`                    | Displays information about the instructor. |

### University Class

| Method                                         | Functionality |
|-----------------------------------------------|---------------|
| `University()`                                | Initializes an empty university object. |
| `University(std::vector<Course>& _courses, std::vector<Instructor>& _instructors, std::vector<TimeSlot>& _timeSlots)` | Initializes university with given courses, instructors, and time slots. |
| `void addCourse(Course& course)`              | Adds a course to the university. |
| `void addInstructor(Instructor& instructor)`  | Adds an instructor to the university. |
| `void addTimeSlot(TimeSlot& timeSlot)`        | Adds a time slot to the university. |
| `void saveState(const std::string& fileName)` | Saves the state of the university to a JSON file. |
| `void loadState(const std::string& fileName)` | Loads the state of the university from a JSON file. |
| `std::vector<TimetableComponent> schedule()`  | Generates a scheduled timetable. |

## Installation

### Prerequisites

- C++14 or higher
- CMake
- Google Test (gtest)
- [nlohmann/json](https://github.com/nlohmann/json)


