#include <gtest/gtest.h>
#include "TimeSlot.h"
#include "Instructor.h"
#include "Course.h"
#include "University.h"
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

// Test TimeSlot class
TEST(TimeSlotTest, CreateTimeSlot) {
    TimeSlot ts("Monday", "09:00", "10:00");
    EXPECT_EQ(ts.day, "Monday");
    EXPECT_EQ(ts.startTime, "09:00");
    EXPECT_EQ(ts.endTime, "10:00");
}

// Test Course class
TEST(CourseTest, CreateCourse) {
    Course course("Math");
    EXPECT_EQ(course.courseName, "Math");
}

TEST(CourseTest, AddPreferredTimeSlot) {
    Course course("Math");
    TimeSlot ts("Monday", "09:00", "10:00");
    course.addPreferredTimeSlot(ts);
    EXPECT_EQ(course.preferredTimeSlots.size(), 1);
    EXPECT_EQ(course.preferredTimeSlots[0].day, "Monday");
    EXPECT_EQ(course.preferredTimeSlots[0].startTime, "09:00");
    EXPECT_EQ(course.preferredTimeSlots[0].endTime, "10:00");
}

// Test Instructor class
TEST(InstructorTest, CreateInstructor) {
    Instructor instructor("Dr. Smith");
    EXPECT_EQ(instructor.name, "Dr. Smith");
}

TEST(InstructorTest, AddAvailability) {
    Instructor instructor("Dr. Smith");
    TimeSlot ts("Monday", "09:00", "10:00");
    instructor.addAvailability(ts);
    EXPECT_EQ(instructor.availability.size(), 1);
    EXPECT_EQ(instructor.availability[0].day, "Monday");
    EXPECT_EQ(instructor.availability[0].startTime, "09:00");
    EXPECT_EQ(instructor.availability[0].endTime, "10:00");
}

TEST(InstructorTest, AddPreferredCourse) {
    Instructor instructor("Dr. Smith");
    Course course("Math");
    instructor.addPreferredCourse(course);
    EXPECT_EQ(instructor.preferredCourses.size(), 1);
    EXPECT_EQ(instructor.preferredCourses[0].courseName, "Math");
}

// Test University class
TEST(UniversityTest, AddCourse) {
    University uni;
    Course course("Math");
    uni.addCourse(course);
    EXPECT_EQ(uni.courses.size(), 1);
    EXPECT_EQ(uni.courses[0].courseName, "Math");
}

TEST(UniversityTest, AddInstructor) {
    University uni;
    Instructor instructor("Dr. Smith");
    uni.addInstructor(instructor);
    EXPECT_EQ(uni.instructors.size(), 1);
    EXPECT_EQ(uni.instructors[0].name, "Dr. Smith");
}

TEST(UniversityTest, AddTimeSlot) {
    University uni;
    TimeSlot ts("Monday", "09:00", "10:00");
    uni.addTimeSlot(ts);
    EXPECT_EQ(uni.timeSlots.size(), 1);
    EXPECT_EQ(uni.timeSlots[0].day, "Monday");
    EXPECT_EQ(uni.timeSlots[0].startTime, "09:00");
    EXPECT_EQ(uni.timeSlots[0].endTime, "10:00");
}


TEST(UniversityTest, ScheduleBasic) {
    University uni;
    TimeSlot ts1("Monday", "09:00", "10:00");
    TimeSlot ts2("Tuesday", "10:00", "11:00");

    Course course1("Math");
    Course course2("Physics");
    course1.addPreferredTimeSlot(ts1);
    course2.addPreferredTimeSlot(ts2);

    Instructor instructor1("Dr. Smith");
    Instructor instructor2("Dr. Johnson");
    instructor1.addAvailability(ts1);
    instructor2.addAvailability(ts2);
    instructor1.addPreferredCourse(course1);
    instructor2.addPreferredCourse(course2);

    uni.addCourse(course1);
    uni.addCourse(course2);
    uni.addInstructor(instructor1);
    uni.addInstructor(instructor2);
    uni.addTimeSlot(ts1);
    uni.addTimeSlot(ts2);

    uni.schedule();

    EXPECT_EQ(uni.timeTable.size(), 2);
    EXPECT_EQ(uni.timeTable[0].course.courseName, "Math");
    EXPECT_EQ(uni.timeTable[0].timeSlot.day, "Monday");
    EXPECT_EQ(uni.timeTable[0].timeSlot.startTime, "09:00");
    EXPECT_EQ(uni.timeTable[0].instructor.name, "Dr. Smith");
    EXPECT_EQ(uni.timeTable[1].course.courseName, "Physics");
    EXPECT_EQ(uni.timeTable[1].timeSlot.day, "Tuesday");
    EXPECT_EQ(uni.timeTable[1].timeSlot.startTime, "10:00");
    EXPECT_EQ(uni.timeTable[1].instructor.name, "Dr. Johnson");
}


TEST(UniversityTest, ScheduleComplex) {
    TimeSlot mon1("Monday", "10:00", "11:00");
    TimeSlot mon2("Monday", "11:00", "12:00");
    TimeSlot mon3("Monday", "13:00", "14:00");
    TimeSlot mon4("Monday", "14:00", "15:00");

    std::vector<TimeSlot> uniTS({ mon1,mon2,mon3 });
    Course c1("math");
    c1.preferredTimeSlots = { mon1,mon3 };
    Course c2("Chemistry");
    c2.preferredTimeSlots = { mon2 };
    Course c3("physics");
    c3.preferredTimeSlots = { mon1 };
 

    std::vector<Course> uniC({ c1,c2,c3 });
    Instructor i1("Isaac Newton");
    i1.availability = { mon1,mon3 };
    i1.preferredCourses = { c1,c3 };
    Instructor i2("Dmitri Mendeleev");
    i2.availability = { mon2,mon4 };
    i2.preferredCourses = { c2, c3 };
    std::vector<Instructor> uniI({ i1,i2 });


    University uni(uniC,uniI,uniTS);
    uni.schedule();
    

    EXPECT_EQ(uni.timeTable.size(), 3);
    EXPECT_EQ(uni.timeTable[0].course.courseName, "math");
    EXPECT_EQ(uni.timeTable[0].timeSlot, mon3);
    EXPECT_EQ(uni.timeTable[0].instructor.name, "Isaac Newton");
    EXPECT_EQ(uni.timeTable[1].course.courseName, "Chemistry");
    EXPECT_EQ(uni.timeTable[1].timeSlot, mon2);
    EXPECT_EQ(uni.timeTable[1].instructor.name, "Dmitri Mendeleev");
    EXPECT_EQ(uni.timeTable[2].course.courseName, "physics");
    EXPECT_EQ(uni.timeTable[2].timeSlot, mon1);
    EXPECT_EQ(uni.timeTable[2].instructor.name, "Isaac Newton");
}

TEST(UniversityTest, saveAndLoadState) {
    TimeSlot mon1("Monday", "10:00", "11:00");

    std::vector<TimeSlot> uniTS({ mon1 });
    Course c1("math");
    c1.preferredTimeSlots = { mon1 };

    std::vector<Course> uniC({ c1 });
    Instructor i1("Isaac Newton");
    i1.availability = { mon1 };
    i1.preferredCourses = { c1 };
    std::vector<Instructor> uniI({ i1 });


    University uni(uniC, uniI, uniTS);
    uni.schedule();
    uni.saveState("result");

    University uni1;
    uni1.loadState("result");
    uni1.schedule();

    EXPECT_EQ(uni.courses, uni1.courses);
    EXPECT_EQ(uni.instructors, uni1.instructors);
    EXPECT_EQ(uni.timeSlots, uni1.timeSlots);
    EXPECT_EQ(uni.timeTable, uni1.timeTable);
}
