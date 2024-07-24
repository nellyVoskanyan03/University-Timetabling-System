#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <vector>
#include <string>
#include "TimeSlot.h"
#include "Course.h"

class Instructor {
public:
	std::string name;
	std::vector<TimeSlot> availability;
	std::vector<Course> preferredCourses;

	Instructor();
	Instructor(std::string);

	void addPreferredCourse(const Course& course);
	void addAvailability(const TimeSlot&);
	void displayInfo();
	json toJson() const;
	static Instructor fromJson(const json& );
	bool operator==(Instructor const&) const;
	bool operator!=(Instructor const&) const;
	
};

#endif