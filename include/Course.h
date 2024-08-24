#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <vector>
#include <string>
#include "TimeSlot.h"

class Course {
private:
	std::string courseName;
	std::vector<TimeSlot> preferredTimeSlots;

public:
	Course();
	Course( std::string);
	Course( std::string, std::vector<TimeSlot>&);

	std::string getCourseName() const;
	std::vector<TimeSlot> getPreferredTimeSlots() const;

	void displayInfo();
	void addPreferredTimeSlot(const TimeSlot&);

	json toJson() const;
	static Course fromJson(const json& );

	bool operator==(Course const& ) const;
};

#endif