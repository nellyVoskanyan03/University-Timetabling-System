#ifndef TIMETABLECOMPONENT_H
#define TIMETABLECOMPONENT_H

#include "Course.h"
#include "Instructor.h"
#include "TimeSlot.h"

class TimetableComponent {
public:
    Course course;
    TimeSlot timeSlot;
    Instructor instructor;

    TimetableComponent(); 
    TimetableComponent(Course, TimeSlot, Instructor);
    json toJson() const;
    bool operator==(TimetableComponent const&) const;
    
};

#endif