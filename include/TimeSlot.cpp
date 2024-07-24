#include "TimeSlot.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
TimeSlot::TimeSlot(): day(""), startTime(""), endTime("") {}

TimeSlot::TimeSlot(std::string _day, std::string _startTime, std::string _endTime):
	day(_day), 
	startTime(_startTime),
	endTime(_endTime) {}

void TimeSlot::displayInfo() {
	std::cout << "Day: " 
		<< day << " Start time: " 
		<< startTime << " End time: " 
		<< endTime
		<< std::endl;
}

json TimeSlot::toJson() const {
	return { {"day", day}, {"startTime", startTime}, {"endTime", endTime} };
}

TimeSlot TimeSlot::fromJson(const json& j) {
	return TimeSlot(j.at("day"), j.at("startTime"), j.at("endTime"));
}

bool TimeSlot::operator==(TimeSlot const& t) const{
	return !day.compare(t.day)  && !startTime.compare(t.startTime) && !endTime.compare(t.endTime);
}

bool TimeSlot::operator!=(TimeSlot const& t) const{
	return !(*this == t);
}