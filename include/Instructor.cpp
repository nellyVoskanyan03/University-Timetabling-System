#include "Instructor.h"
#include <string>
#include <iostream>
#include <vector>
#include "TimeSlot.h"
#include "Course.h"


Instructor::Instructor() {}
Instructor::Instructor(std::string _name):
	name(_name), preferredCourses({}), availability({}) {}

void Instructor::displayInfo() {
	std::cout << "Instructor's information\nName: "
		<< name
		<< "\nAvailable time slots: "
		<< std::endl;
	for (int i = 0; i < availability.size(); i++)
	{
		availability[i].displayInfo();
	}
	std::cout <<"\nPreferred Courses : "
		<< std::endl;
	for (int i = 0; i < preferredCourses.size(); i++)
	{
		preferredCourses[i].displayInfo();
	}
}

json Instructor::toJson() const {
	json j;
	j["name"] = name;
	for (const auto& ts : availability) {
		j["availability"].push_back(ts.toJson());
	}
	for (const auto& course : preferredCourses) {
		j["preferredCourses"].push_back(course.toJson());
	}
	return j;
}

void Instructor::addAvailability(const TimeSlot& timeSlot) {
	availability.push_back(timeSlot);
}

void Instructor::addPreferredCourse(const Course& course) {
	preferredCourses.push_back(course);
}

Instructor Instructor::fromJson(const json& j) {
	Instructor instructor(j.at("name"));
	for (const auto& ts : j.at("availability")) {
		instructor.addAvailability(TimeSlot::fromJson(ts));
	}
	for (const auto& course : j.at("preferredCourses")) {
		instructor.addPreferredCourse(Course::fromJson(course));
	}
	return instructor;
}

bool Instructor::operator==(Instructor const& i) const{
	return !name.compare(i.name) && availability == i.availability && preferredCourses == i.preferredCourses;
}

bool Instructor::operator!=(Instructor const& i) const{
	return !(*this == i);
}