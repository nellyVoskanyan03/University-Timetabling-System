#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <vector>
#include <string>
#include "TimeSlot.h"

class Course {
public:
	std::string courseName;
	std::vector<TimeSlot> preferredTimeSlots;
	Course();
	Course( std::string);
	Course( std::string, std::vector<TimeSlot>&);
	void displayInfo();
	json toJson() const;
	
	void addPreferredTimeSlot(const TimeSlot&);
	static Course fromJson(const json& );
	bool operator==(Course const& ) const;
};

#endif