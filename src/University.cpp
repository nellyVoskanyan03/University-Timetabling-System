#include "University.h"
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
#include <algorithm>
#include "Course.h"
#include "TimeSlot.h"
#include "Instructor.h"
#include"TimetableComponent.h"
#include <cstdlib>
#include <algorithm>  
#include <map>

University::University() {}

University::University(std::vector<Course>& _courses, std::vector<Instructor>& _instructors, std::vector<TimeSlot>& _timeSlots) : 
	courses(_courses), 
	instructors(_instructors), 
	timeSlots(_timeSlots) {}

void University::addCourse(Course& course) {
	courses.push_back(course);
}

void University::addInstructor(Instructor& instructor) {
	instructors.push_back(instructor);
}

void University::addTimeSlot(TimeSlot& timeSlot) {
	timeSlots.push_back(timeSlot);
}

void University::saveState(const std::string& fileName ) {
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

void University::loadState(const std::string& filename) {
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

void possibleSchedulesWithoutInstructors(std::vector<TimeSlot>& timeSlots, std::vector<Course>& courses, int currentColumn, std::vector<TimetableComponent>& curr, std::vector<std::vector<TimetableComponent>>& res)
{

    if (currentColumn == timeSlots.size())
    {
        res.push_back(curr);
        return;
    }
    for (int i = 0; i < courses.size(); i++)
    {
        TimetableComponent sc(courses[i], timeSlots[currentColumn]);
        curr.push_back(sc);
        possibleSchedulesWithoutInstructors(timeSlots, courses, currentColumn + 1, curr, res);
        curr.pop_back();
    }
}

bool instructorIsFree(const std::vector<Instructor>& curr, const Instructor& instructor, const std::vector<TimetableComponent>& schedule){
    for (int i = 0; i < curr.size() - 1; i++)
    {
        if (curr[i] == instructor && schedule[curr.size() - 1].timeSlot == schedule[i].timeSlot)
        {
            return false;
        }
    }
    return true;
}

bool instructorIsAvailable(Instructor& instructor, TimeSlot& timeSlot) {
    return std::find(instructor.availability.begin(), instructor.availability.end(), timeSlot) != instructor.availability.end();
}

void instructorCombinationsForGivenSchedule(std::vector<Instructor>& instructors, 
    std::vector<Instructor>& curr,
    std::vector<std::vector<Instructor>>& res, 
    std::vector<TimetableComponent>& schedule)
{
    if (curr.size() == schedule.size() )
    {
        res.push_back(curr);
        return;
    }
    for (int i = 0; i < instructors.size(); i++)
    {
        curr.push_back(instructors[i]);

        if (instructorIsAvailable(instructors[i], schedule[curr.size() - 1].timeSlot)
            && instructorIsFree(curr,instructors[i],schedule))
        {
            instructorCombinationsForGivenSchedule(instructors, curr, res, schedule);
        }
        curr.pop_back();

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
std::vector<TimeSlot> timeSlotsThatHaveInstructors(std::vector<TimeSlot>& timeSlots, std::vector<Instructor>& instructors) {
    std::vector<TimeSlot> validTimeSlots;
    
    for (int i = 0; i < instructors.size(); i++)
    {
        for (int j = 0; j < instructors[i].availability.size(); j++)
        {
           
            if (std::find(timeSlots.begin(), timeSlots.end(), instructors[i].availability[j]) != timeSlots.end())
            {
                validTimeSlots.push_back(instructors[i].availability[j]);
            }
           
        }
    }
    
    return validTimeSlots;
}

void insertInstructersInSchedule(std::vector<TimetableComponent>& schedule, std::vector<Instructor>& instructorCombination) {
    for (int i = 0; i < instructorCombination.size(); i++)
    {
        schedule[i].instructor = instructorCombination [i];
    }
}

std::vector<TimetableComponent> University::schedule() {
    

    auto availableTimeSlots = timeSlotsThatHaveInstructors(timeSlots, instructors); // O(sum of instructors' availability)
    
    std::vector<std::vector<TimetableComponent>> possibleSchedules;
    std::vector<TimetableComponent> currSchedule;
    possibleSchedulesWithoutInstructors(availableTimeSlots, courses, 0, currSchedule, possibleSchedules); // O(availableTimeSlots.size()^courses.size())

    int maxFitness = -1;
    std::vector<TimetableComponent> bestSchedule;

    for (int i = 0; i < possibleSchedules.size(); i++)
    {
        std::vector<Instructor> curr;
        std::vector<std::vector<Instructor>> instructorCombinations;
        instructorCombinationsForGivenSchedule(instructors, curr, instructorCombinations, possibleSchedules[i]); // O( possibleSchedules[i].size()^Instructors.size())

        for (int j = 0; j < instructorCombinations.size(); j++)
        {
            insertInstructersInSchedule(possibleSchedules[i], instructorCombinations[j]); // O( possibleSchedules[i].size())
                
            int fitValue = fitness(possibleSchedules[i]); // 0(possibleSchedules[i].size()*lg(courses.size())*lg(courses.size()))
            if (maxFitness < fitValue)
            {
                maxFitness = fitValue;
                bestSchedule = possibleSchedules[i];
            }
        }

        
    }
    timeTable = bestSchedule;
    return bestSchedule;
}

//std::vector<ScheduleComponent> University::schedule(int numOfSchedules, int numOfGenerationEvaluation, double mutationProbability) {
//    std::vector<std::vector<ScheduleComponent>> Q = generatePopulation(numOfSchedules);
//    int currentGeneration = 0;
//    std::vector<ScheduleComponent> parent;
//    std::vector<ScheduleComponent> child;
//    while (currentGeneration <= numOfGenerationEvaluation)
//    {
//        parent = randomSelection(Q);
//        child = parent;
//        scheduleMutation(child, mutationProbability);
//        scheduleRepair(child, mutationProbability);
//        localOptimization(child);
//        replace(parent, child, Q);
//        currentGeneration++;
//    }
//    return best(Q);
//}
//
//void University::scheduleMutation(std::vector<ScheduleComponent>& schedule, double mp) {
//    for (int i = 0; i < courses.size() ; i++)
//    {
//        double m = ((double)rand() / (RAND_MAX)) + 1;
//        if (m <= mp)
//        {
//            TimeSlot newTimeSlot = listOfPossibleTimeSlots(timeSlots)[0];
//            if (allreadyAssignedToCourse(scedule, newTimeSlot))
//            {
//                for (int j = 0; j < listOfPossibleTimeSlots(timeSlots).size(); j++)
//                {
//                    if (!allreadyAssignedToCourse(scedule, timeSlots[j]))
//                    {
//                        newTimeSlot = timeSlots[j]; 
//                        break;
//                    }
//                }
//            }
//            schedule[i].timeSlot = newTimeSlot;
//        }
//
//        m = ((double)rand() / (RAND_MAX)) + 1;
//        if (m <= mp)
//        {
//            Instructor newInstructor = listOfPossibleInstructors(schedule[i].timeSlot)[0];
//            schedule[i].instructor = newInstructor;
//        }
//    }
//}
//
//void University::scheduleRepair(std::vector<ScheduleComponent>& schedule, int maxRepairTimes) {
//    std::vector<ScheduleComponent>& repairedSchedule = schedule;
//    for (size_t i = 0; i < maxRepairTimes; i++)
//    {
//        if (isValid(repairedSchedule))
//        {
//            schedule = repairedSchedule;
//            return;
//        }
//        
//        for (int j = 0; j < courses.size(); j++)
//        {
//            std::vector<TimeSlot> tabuList;
//            for (int k = 0; k < courses.size(); k++)
//            {
//                if (k!= j 
//                    && repairedSchedule[j].instructor == repairedSchedule[k].instructor 
//                    && repairedSchedule[j].timeSlot == repairedSchedule[k].timeSlot)
//                {
//                    tabuList.push_back(repairedSchedule[j].timeSlot);
//                    std::vector<TimeSlot> potentialTimes = sub(AvailableSlots(repairedSchedule[j].instructor), tabuList);;
//                    if (potentialTimes.size() != 0)
//                    {
//                        repairedSchedule[j].timeSlot = potentialTimes[0];
//                    }
//                }
//            }
//        }
//    }
//    schedule = repairedSchedule;
//}
//
//void University::localOptimization(std::vector<ScheduleComponent>& schedule) {
//    std::vector<ScheduleComponent> optimizedSchedule = schedule;
//    for (int i = 0; i < courses.size(); i++)
//    {
//
//    }
//}