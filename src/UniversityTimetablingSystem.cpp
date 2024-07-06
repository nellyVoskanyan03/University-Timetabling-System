#include <iostream>
#include <vector>
#include "UniversityTimetablingSystem.h"
#include "TimeSlot.h"
#include "Course.h"
#include "Instructor.h"
#include "University.h";

int main()
{
	TimeSlot mon1("Monday", "10:00", "11:00");
	TimeSlot mon2("Monday", "11:00", "12:00");
	TimeSlot mon3("Monday", "13:00", "14:00");
	TimeSlot mon4("Monday", "14:00", "15:00");

	TimeSlot tue1("Tuesday", "10:00", "11:00");
	TimeSlot tue2("Tuesday", "11:00", "12:00");
	TimeSlot tue3("Tuesday", "13:00", "14:00");
	TimeSlot tue4("Tuesday", "14:00", "15:00");

	TimeSlot wed1("Wednesday", "10:00", "11:00");
	TimeSlot wed2("Wednesday", "11:00", "12:00");
	TimeSlot wed3("Wednesday", "13:00", "14:00");
	TimeSlot wed4("Wednesday", "14:00", "15:00");
	
	TimeSlot thr1("Thursday", "10:00", "11:00");
	TimeSlot thr2("Thursday", "11:00", "12:00");
	TimeSlot thr3("Thursday", "13:00", "14:00");
	TimeSlot thr4("Thursday", "14:00", "15:00");
	
	TimeSlot fri1("Friday", "10:00", "11:00");
	TimeSlot fri2("Friday", "11:00", "12:00");
	TimeSlot fri3("Friday", "13:00", "14:00");
	TimeSlot fri4("Friday", "14:00", "15:00");

	std::vector<TimeSlot> uniTS({ mon1,mon2,mon3 });

	Course c1("Complex analiz t.");
	c1.preferredTimeSlots = { mon2,tue2,wed2,thr2,fri2 };
	Course c2("complex analiz g.");
	c2.preferredTimeSlots = { mon1,tue1,wed1,thr1,fri1, fri2 };

	Course c3("Fizika t.");
	c3.preferredTimeSlots = { fri3 };
	Course c4("Fizika g.");
	c4.preferredTimeSlots = { mon3 };

	Course c5("OS t.");
	c5.preferredTimeSlots = { tue1 };
	Course c6("OS g.");
	c6.preferredTimeSlots = { fri1 };
	
	Course c7("Algo t.");
	c7.preferredTimeSlots = { wed3 };
	Course c8("algo g.");
	c8.preferredTimeSlots = { tue3 };
	
	std::vector<Course> uniC({ c1,c2,c3,c4 });

	Instructor i1("Armen");
	i1.availability = { mon1,mon2,mon3,tue1,tue2,tue3,tue4 };
	i1.preferredCourses = { c1,c2,c3,c4};

	Instructor i2("Karen");
	i2.availability = { mon1,mon2,mon3 };
	i2.preferredCourses = { c1,c2,c3,c4 };

	std::vector<Instructor> uniI({ i1,i2 });

	
	University uni(uniC, uniI, uniTS);
	uni.loadState("Uni");
	uni.schedule();
	uni.saveState("Uni");

	return 0;
}
