#include "Course.h"

#include <iostream>
#include <vector>
#include <string>

Course::Course(): courseName("") {}

Course::Course( std::string _courseName) :
	courseName(_courseName), preferredTimeSlots({}) {}

Course::Course( std::string _courseName, std::vector<TimeSlot>& _preferredTimeSlots) :
	courseName(_courseName), preferredTimeSlots(_preferredTimeSlots) {}

void Course::displayInfo() {
	std::cout << "Course information\nCourse name: " 
		<< courseName 
		<< "\nPreferred time slots: " 
		<< std::endl;
	for (int i = 0; i < preferredTimeSlots.size(); i++)
	{
		preferredTimeSlots[i].displayInfo();
	}
}
json Course::toJson() const {
	json j;
	j["courseName"] = courseName;
	for (const auto& ts : preferredTimeSlots) {
		j["preferredTimeSlots"].push_back(ts.toJson());
	}
	return j;
}


void Course::addPreferredTimeSlot(const TimeSlot& timeSlot) {
	preferredTimeSlots.push_back(timeSlot);
}

Course Course::fromJson(const json& j) {
	Course course(j.at("courseName"));
	for (const auto& ts : j.at("preferredTimeSlots")) {
		course.addPreferredTimeSlot(TimeSlot::fromJson(ts));
	}
	return course;
}
bool Course::operator==(Course const& c) const {
	return !courseName.compare(c.courseName) && preferredTimeSlots == c.preferredTimeSlots;
}