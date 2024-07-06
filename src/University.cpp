#include "University.h"

#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include "Course.h"
#include "TimeSlot.h"
#include "Instructor.h"
#include "TimetableComponent.h"
#include "TimeSlotInstructorPair.h"


University::University() {}

University::University(std::vector<Course>& _courses, std::vector<Instructor>& _instructors, std::vector<TimeSlot>& _timeSlots) : 
	courses(_courses), 
	instructors(_instructors), 
	timeSlots(_timeSlots) {}

void University::addCourse(Course& course)
{
	courses.push_back(course);
}

void University::addInstructor(Instructor& instructor)
{
	instructors.push_back(instructor);
}

void University::addTimeSlot(TimeSlot& timeSlot)
{
	timeSlots.push_back(timeSlot);
}

void University::saveState(const std::string& fileName )
{
    json j;
    for (const auto& course : courses) {
        j["courses"].push_back(course.toJson());
    }
    for (const auto& instructor : instructors) {
        j["instructors"].push_back(instructor.toJson());
    }
    for (const auto& ts : timeSlots) {
        j["timeSlots"].push_back(ts.toJson());
    }
    for (const auto& entry : timeTable) {
        j["timetable"].push_back(entry.toJson());
    }
    std::ofstream file(fileName);
    file << j.dump(4);
}

void University::loadState(const std::string& filename) 
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "No such file." << std::endl;
        return;
    }

    json j;
    file >> j;  

    try
    {
        for (const auto& courseJson : j.at("courses")) {
            courses.push_back(Course::fromJson(courseJson));
        }
        for (const auto& instructorJson : j.at("instructors")) {
            instructors.push_back(Instructor::fromJson(instructorJson));
        }
        for (const auto& tsJson : j.at("timeSlots")) {
            timeSlots.push_back(TimeSlot::fromJson(tsJson));
        }
    }
    catch (const json::out_of_range& m)
    {
        std::cout << "Provided file don't contain valid schedule: "<< m.what();
    }
    
}

int fitness(std::vector<TimetableComponent>& schedule) {
    int fitValue = 0;
    for (int i = 0; i < schedule.size(); i++)
    {
        if (std::find(schedule[i].instructor.preferredCourses.begin(), 
            schedule[i].instructor.preferredCourses.end(),
            schedule[i].course) != schedule[i].instructor.preferredCourses.end())
        {
            ++fitValue;
        }
        if (std::find(schedule[i].course.preferredTimeSlots.begin(),
            schedule[i].course.preferredTimeSlots.end(),
            schedule[i].timeSlot) != schedule[i].course.preferredTimeSlots.end())
        {
            ++fitValue;
        }
    }
    return fitValue;
}

std::vector<TimeSlotInstructorPair> makeTimeSlotInstructorPairs(std::vector<Instructor>& instructors)
{
    std::vector<TimeSlotInstructorPair>timeSlotInstructorPairs;
   
    for (int i = 0; i < instructors.size(); i++)
    {
        for (int j = 0; j < instructors[i].availability.size(); j++)
        {
            timeSlotInstructorPairs.push_back(TimeSlotInstructorPair(instructors[i].availability[j], instructors[i], false));
        }
    }
    return timeSlotInstructorPairs;
}

void makePossibleSchedules(std::vector<TimeSlotInstructorPair>& timeSlotInstructorPairs,
    std::vector<Course>& courses, 
    std::vector<TimetableComponent>& currSchedule, 
    std::vector<std::vector<TimetableComponent>>& possibleSchedules)
{
    if (currSchedule.size() == courses.size())
    {
        possibleSchedules.push_back(currSchedule); 
        return;
    }
    for (int i = 0; i < timeSlotInstructorPairs.size(); i++)
    {
        if (!timeSlotInstructorPairs[i].used)
        {
            TimetableComponent component(courses[currSchedule.size()], timeSlotInstructorPairs[i].timeSlot, timeSlotInstructorPairs[i].instructor);
            currSchedule.push_back(component);
            timeSlotInstructorPairs[i].used = true;

            makePossibleSchedules(timeSlotInstructorPairs, courses, currSchedule, possibleSchedules);

            currSchedule.pop_back();
            timeSlotInstructorPairs[i].used = false;
        }
    }
}

std::vector<TimetableComponent> University::schedule() {
    auto timeSlotInstructorPairs = makeTimeSlotInstructorPairs(instructors); 
    
    std::vector<std::vector<TimetableComponent>> possibleSchedules;
    std::vector<TimetableComponent> currSchedule;
    
    makePossibleSchedules(timeSlotInstructorPairs, courses, currSchedule, possibleSchedules); 

    int maxFitness = -1;
    std::vector<TimetableComponent> bestSchedule;

    for (int i = 0; i < possibleSchedules.size(); i++)
    {
        int fitValue = fitness(possibleSchedules[i]); 
        if (maxFitness < fitValue)
        {
            maxFitness = fitValue;
            bestSchedule = possibleSchedules[i];
        }        
    }
    timeTable = bestSchedule;
    return bestSchedule;
}