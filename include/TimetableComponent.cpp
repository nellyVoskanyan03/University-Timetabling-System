#include "Course.h"
#include "Instructor.h"
#include "TimeSlot.h" 
#include "TimetableComponent.h"


TimetableComponent::TimetableComponent() {}

TimetableComponent::TimetableComponent(Course c, TimeSlot t, Instructor i)
        : course(c), timeSlot(t), instructor(i) {}

json TimetableComponent::toJson() const {
      return {
           {"courseName", course.getCourseName()},
           {"timeSlot", timeSlot.toJson()},
           {"instructor", instructor.getName()}
       };
 }
bool TimetableComponent::operator==(TimetableComponent const& t) const {
    return course == t.course && timeSlot == t.timeSlot;
}


