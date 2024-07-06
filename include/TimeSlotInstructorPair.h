#ifndef TIMESLOTINSTRUCORPAIR_H
#define TIMESLOTINSTRUCORPAIR_H

#include "TimeSlot.h"
#include "Instructor.h"

class TimeSlotInstructorPair {
public:
	TimeSlot timeSlot;
	Instructor instructor;
	bool used;

	TimeSlotInstructorPair(TimeSlot t, Instructor i, bool u) :timeSlot(t), instructor(i), used(u) {}
};
#endif