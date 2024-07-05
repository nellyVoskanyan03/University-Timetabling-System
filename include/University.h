#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <string>
#include <vector>
#include "Course.h"
#include "TimeSlot.h"
#include "Instructor.h"
#include "TimetableComponent.h"

class University {
public:
	std::vector<Course> courses;
	std::vector<Instructor> instructors;
	std::vector<TimeSlot> timeSlots;
	std::vector<TimetableComponent> timeTable;

	University();
	University(std::vector<Course>&, std::vector<Instructor>&, std::vector<TimeSlot>&);

	void addCourse(Course&);
	void addInstructor(Instructor&);
	void addTimeSlot(TimeSlot&);

	void saveState(const std::string&);
	void loadState(const std::string&);
	std::vector<TimetableComponent> schedule();
	
	//std::vector<ScheduleComponent> schedule(int numOfSchedules,int numOfGenerationEvaluation, double mutationProbability);

	/*std::vector<std::vector<ScheduleComponent>> generatePopulation(int);
	std::vector<ScheduleComponent> randomSelection(std::vector<std::vector<ScheduleComponent>>&);
	void scheduleMutation(std::vector<ScheduleComponent>&, double);
	void scheduleRepair(std::vector<ScheduleComponent>&, int);
	void localOptimization(std::vector<ScheduleComponent>&);
	void replace(std::vector<ScheduleComponent>&, std::vector<ScheduleComponent>&, std::vector<std::vector<ScheduleComponent>>&);
	std::vector<ScheduleComponent> best(std::vector<std::vector<ScheduleComponent>>&);*/
};
#endif 

