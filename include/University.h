#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>
#include <vector>
#include "Course.h"
#include "TimeSlot.h"
#include "Instructor.h"
#include "TimetableComponent.h"

class University {
private:
	std::vector<Course> courses;
	std::vector<Instructor> instructors;
	std::vector<TimeSlot> timeSlots;
	std::vector<TimetableComponent> timeTable;

public:
	University();
	University(std::vector<Course>&, std::vector<Instructor>&, std::vector<TimeSlot>&);

	void addCourse(Course&);
	void addInstructor(Instructor&);
	void addTimeSlot(TimeSlot&);
	
	std::vector<Course> getCourses() const;
	std::vector<Instructor> getInstructors() const;
	std::vector<TimeSlot> getTimeSlots() const;
	std::vector<TimetableComponent> getTimeTable() const;

	void saveState(const std::string&);
	void loadState(const std::string&);
	std::vector<TimetableComponent> schedule();
};
#endif 

