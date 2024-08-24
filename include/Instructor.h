#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <vector>
#include <string>
#include "TimeSlot.h"
#include "Course.h"

class Instructor {
private:
	std::string name;
	std::vector<TimeSlot> availability;
	std::vector<Course> preferredCourses;

public:
	Instructor();
	Instructor(std::string);

	std::string getName() const;
	std::vector<TimeSlot> getAvailability() const;
	std::vector<Course> getPreferredCourses() const;

	void addPreferredCourse(const Course& course);
	void addAvailability(const TimeSlot&);
	void displayInfo();
	json toJson() const;
	static Instructor fromJson(const json& );
	bool operator==(Instructor const&) const;
	bool operator!=(Instructor const&) const;
};

#endif