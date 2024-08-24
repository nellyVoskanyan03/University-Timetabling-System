#include "Course.h"

#include <iostream>
#include <vector>
#include <string>

Course::Course(): courseName("") {}

Course::Course( std::string _courseName) :
	courseName(_courseName), preferredTimeSlots({}) {}

Course::Course( std::string _courseName, std::vector<TimeSlot>& _preferredTimeSlots) :
	courseName(_courseName), preferredTimeSlots(_preferredTimeSlots) {}

std::string Course::getCourseName() const {
	return courseName;
}

std::vector<TimeSlot> Course::getPreferredTimeSlots() const {
	return preferredTimeSlots;
}

void Course::displayInfo() {
	std::cout << "Course information\nCourse name: " 
		<< courseName 
		<< "\nPreferred time slots: " 
		<< std::endl;
	for (int i = 0; i < preferredTimeSlots.size(); i++)	{
		preferredTimeSlots[i].displayInfo();
	}
}

json Course::toJson() const {
	json courseJson;
	courseJson["courseName"] = courseName;

	for (const auto& ts : preferredTimeSlots) {
		courseJson["preferredTimeSlots"].push_back(ts.toJson());
	}
	return courseJson;
}

void Course::addPreferredTimeSlot(const TimeSlot& timeSlot) {
	preferredTimeSlots.push_back(timeSlot);
}

Course Course::fromJson(const json& courseJson) {
	Course course(courseJson.at("courseName"));
	for (const auto& ts : courseJson.at("preferredTimeSlots")) {
		course.addPreferredTimeSlot(TimeSlot::fromJson(ts));
	}
	return course;
}

bool Course::operator==(Course const& other) const {
	return !courseName.compare(other.courseName) && preferredTimeSlots == other.preferredTimeSlots;
}