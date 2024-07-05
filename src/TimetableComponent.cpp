#include "Course.h"
#include "Instructor.h"
#include "TimeSlot.h" 
#include "TimetableComponent.h"


TimetableComponent::TimetableComponent() {}

TimetableComponent::TimetableComponent(Course c, TimeSlot t)
        : course(c), timeSlot(t) {}

json TimetableComponent::toJson() const {
      return {
           {"courseName", course.courseName},
           {"timeSlot", timeSlot.toJson()},
           {"instructor", instructor.name}
       };
 }

