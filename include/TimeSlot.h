#ifndef TIMESLOT_H
#define TIMESLOT_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
class TimeSlot {
public:
	std::string day;
	std::string startTime;
	std::string endTime;
	TimeSlot();
	TimeSlot(std::string, std::string, std::string);
	void displayInfo();
	json toJson() const;
	static TimeSlot fromJson(const json& );
	bool operator==(TimeSlot const& t) const;
	bool operator!=(TimeSlot const& t) const;
};

#endif