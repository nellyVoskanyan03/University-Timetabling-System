#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "../include/University.h"
#include <vector>
#include <fstream>

// Test TimeSlot class
TEST(TimeSlotTest, CreateTimeSlot) {
    TimeSlot ts("Monday", "09:00", "10:00");
    EXPECT_EQ(ts.getDay(), "Monday");
    EXPECT_EQ(ts.getStartTime(), "09:00");
    EXPECT_EQ(ts.getEndTime(), "10:00");
}

TEST(TimeSlotTest, CreateJson) {
    TimeSlot ts("Monday", "09:00", "10:00");
    json timeSlotJson = ts.toJson();
    EXPECT_EQ(timeSlotJson["day"], "Monday");
    EXPECT_EQ(timeSlotJson["startTime"], "09:00");
    EXPECT_EQ(timeSlotJson["endTime"], "10:00");
}

TEST(TimeSlotTest, ReadJson) {
    json timeSlotJson = { {"day", "Monday"}, {"startTime", "09:00"}, {"endTime", "10:00"} };
    TimeSlot ts = TimeSlot::fromJson(timeSlotJson);
    EXPECT_EQ(ts.getDay(), "Monday");
    EXPECT_EQ(ts.getStartTime(), "09:00");
    EXPECT_EQ(ts.getEndTime(), "10:00");
}

TEST(TimeSlotTest, Equal) {
    TimeSlot ts1("Monday", "09:00", "10:00");
    TimeSlot ts2 = ts1;
    EXPECT_TRUE(ts1 == ts2);
    
    TimeSlot ts3("Sunday", "09:00", "10:00");
    EXPECT_FALSE(ts1 == ts3);
    
    TimeSlot ts4("Monday", "09:01", "10:00");
    EXPECT_FALSE(ts1 == ts4);
    
    TimeSlot ts5("Monday", "09:00", "10:10");
    EXPECT_FALSE(ts1 == ts5);

}

TEST(TimeSlotTest, NotEqual) {
    TimeSlot ts1("Monday", "09:00", "10:00");
    TimeSlot ts2 = ts1;
    EXPECT_FALSE(ts1 != ts2);
    
    TimeSlot ts3("Sunday", "09:00", "10:00");
    EXPECT_TRUE(ts1 != ts3);
    
    TimeSlot ts4("Monday", "09:01", "10:00");
    EXPECT_TRUE(ts1 != ts4);
    
    TimeSlot ts5("Monday", "09:00", "10:10");
    EXPECT_TRUE(ts1 != ts5);

}

// Test Course class
TEST(CourseTest, CreateCourse) {
    Course course("Math");
    EXPECT_EQ(course.getCourseName(), "Math");
    EXPECT_EQ(course.getPreferredTimeSlots().size(), 0); 
    
    std::vector<TimeSlot> preferredTimeSlots;
    preferredTimeSlots.emplace_back("Monday", "09:00", "10:00");

    Course course1("Math", preferredTimeSlots);
    EXPECT_EQ(course1.getCourseName(), "Math");
    EXPECT_EQ(course1.getPreferredTimeSlots().size(), 1);
}

TEST(CourseTest, AddPreferredTimeSlot) {
    Course course("Math");
    TimeSlot ts("Monday", "09:00", "10:00");
    course.addPreferredTimeSlot(ts);
    EXPECT_EQ(course.getPreferredTimeSlots().size(), 1);
    EXPECT_EQ(course.getPreferredTimeSlots()[0].getDay(), "Monday");
    EXPECT_EQ(course.getPreferredTimeSlots()[0].getStartTime(), "09:00");
    EXPECT_EQ(course.getPreferredTimeSlots()[0].getEndTime(), "10:00");
}

TEST(CourseTest, CreateJson) {
    std::vector<TimeSlot> preferredTimeSlots;
    preferredTimeSlots.emplace_back("Monday", "09:00", "10:00");

    Course course("Math", preferredTimeSlots);
    json courseJson = course.toJson();

    EXPECT_EQ(courseJson["courseName"], "Math");
    EXPECT_EQ(courseJson["preferredTimeSlots"].size(), 1);
}

TEST(CourseTest, ReadJson) {
    json courseJson = { 
        {"courseName", "Math"},
        {"preferredTimeSlots", {} }
    };
    courseJson["preferredTimeSlots"].push_back({ {"day", "Monday"}, {"startTime", "09:00"}, {"endTime", "10:00"} });

    Course course = Course::fromJson(courseJson);
    EXPECT_EQ(course.getCourseName(), "Math");
    EXPECT_EQ(course.getPreferredTimeSlots().size(), 1);
    EXPECT_EQ(course.getPreferredTimeSlots()[0].getDay(), "Monday");
    EXPECT_EQ(course.getPreferredTimeSlots()[0].getStartTime(), "09:00");
    EXPECT_EQ(course.getPreferredTimeSlots()[0].getEndTime(), "10:00");
}

TEST(CourseTest, Equal) {
    std::vector<TimeSlot> preferredTimeSlots;
    preferredTimeSlots.emplace_back("Monday", "09:00", "10:00");

    Course course1("Math", preferredTimeSlots);
    Course course2 = course1;
    EXPECT_TRUE(course1 == course2);

    Course course3("Art", preferredTimeSlots);
    EXPECT_FALSE(course1 == course3);
    
    Course course4("Math");
    EXPECT_FALSE(course1 == course4);
}

// Test Instructor class
TEST(InstructorTest, CreateInstructor) {
    Instructor instructor("Dr. Smith");
    EXPECT_EQ(instructor.getName(), "Dr. Smith");
    EXPECT_EQ(instructor.getPreferredCourses().size(), 0);
    EXPECT_EQ(instructor.getAvailability().size(), 0);
}

TEST(InstructorTest, AddAvailability) {
    Instructor instructor("Dr. Smith");
    TimeSlot ts("Monday", "09:00", "10:00");
    instructor.addAvailability(ts);
    EXPECT_EQ(instructor.getAvailability().size(), 1);
    EXPECT_EQ(instructor.getAvailability()[0].getDay(), "Monday");
    EXPECT_EQ(instructor.getAvailability()[0].getStartTime(), "09:00");
    EXPECT_EQ(instructor.getAvailability()[0].getEndTime(), "10:00");
}

TEST(InstructorTest, AddPreferredCourse) {
    Instructor instructor("Dr. Smith");
    Course course("Math");
    instructor.addPreferredCourse(course);
    EXPECT_EQ(instructor.getPreferredCourses().size(), 1);
    EXPECT_EQ(instructor.getPreferredCourses()[0].getCourseName(), "Math");
}

TEST(InstructorTest, CreateJson) {
    TimeSlot ts("Monday", "09:00", "10:00");
    Course course("Clean Code");

    Instructor instructor("Uncle Bob");
    instructor.addAvailability(ts);
    instructor.addPreferredCourse(course);

    json instructorJson = instructor.toJson();

    EXPECT_EQ(instructorJson["name"], "Uncle Bob");
    EXPECT_EQ(instructorJson["availability"].size(), 1);
    EXPECT_EQ(instructorJson["preferredCourses"].size(), 1);
}

TEST(InstructorTest, ReadJson) {
    json timeSlotJson = { {"day", "Monday"}, {"startTime", "09:00"}, {"endTime", "10:00"} };
    json courseJson = {
        {"courseName", "Clean code"},
        {"preferredTimeSlots", {} }
    };
    courseJson["preferredTimeSlots"].push_back(timeSlotJson);

    json instructorJson = { {"name", "Uncle Bob"}, {"availability", {}}, {"preferredCourses",{}} };
    instructorJson["availability"].push_back(timeSlotJson);
    instructorJson["preferredCourses"].push_back(courseJson);

    Instructor instructor =  Instructor::fromJson(instructorJson);
    EXPECT_EQ(instructor.getName(), "Uncle Bob");
    EXPECT_EQ(instructor.getPreferredCourses().size(), 1);
    EXPECT_EQ(instructor.getAvailability().size(), 1);
}

TEST(InstructorTest, Equal) {
    TimeSlot ts("Monday", "09:00", "10:00");
    Course course("Clean Code");

    Instructor instructor1("Uncle Bob");
    instructor1.addAvailability(ts);
    instructor1.addPreferredCourse(course);

    Instructor instructor2 = instructor1;
    EXPECT_TRUE(instructor1 == instructor2);

    instructor2.addAvailability(ts);
    EXPECT_FALSE(instructor1 == instructor2);

    instructor1.addAvailability(ts);
    instructor2.addPreferredCourse(course);
    EXPECT_FALSE(instructor1 == instructor2);
}

TEST(InstructorTest, NotEqual) {
    TimeSlot ts("Monday", "09:00", "10:00");
    Course course("Clean Code");

    Instructor instructor1("Uncle Bob");
    instructor1.addAvailability(ts);
    instructor1.addPreferredCourse(course);

    Instructor instructor2 = instructor1;
    EXPECT_FALSE(instructor1 != instructor2);

    instructor2.addAvailability(ts);
    EXPECT_TRUE(instructor1 != instructor2);

    instructor1.addAvailability(ts);
    instructor2.addPreferredCourse(course);
    EXPECT_TRUE(instructor1 != instructor2);
}

// Test University class
TEST(UniversityTest, AddCourse) {
    University uni;
    Course course("Math");
    uni.addCourse(course);
    EXPECT_EQ(uni.getCourses().size(), 1);
    EXPECT_EQ(uni.getCourses()[0].getCourseName(), "Math");
}

TEST(UniversityTest, AddInstructor) {
    University uni;
    Instructor instructor("Dr. Smith");
    uni.addInstructor(instructor);
    EXPECT_EQ(uni.getInstructors().size(), 1);
    EXPECT_EQ(uni.getInstructors()[0].getName(), "Dr. Smith");
}

TEST(UniversityTest, AddTimeSlot) {
    University uni;
    TimeSlot ts("Monday", "09:00", "10:00");
    uni.addTimeSlot(ts);
    EXPECT_EQ(uni.getTimeSlots().size(), 1);
    EXPECT_EQ(uni.getTimeSlots()[0].getDay(), "Monday");
    EXPECT_EQ(uni.getTimeSlots()[0].getStartTime(), "09:00");
    EXPECT_EQ(uni.getTimeSlots()[0].getEndTime(), "10:00");
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

    EXPECT_EQ(uni.getTimeTable().size(), 2);
    EXPECT_EQ(uni.getTimeTable()[0].course.getCourseName(), "Math");
    EXPECT_EQ(uni.getTimeTable()[0].timeSlot.getDay(), "Monday");
    EXPECT_EQ(uni.getTimeTable()[0].timeSlot.getStartTime(), "09:00");
    EXPECT_EQ(uni.getTimeTable()[0].instructor.getName(), "Dr. Smith");
    EXPECT_EQ(uni.getTimeTable()[1].course.getCourseName(), "Physics");
    EXPECT_EQ(uni.getTimeTable()[1].timeSlot.getDay(), "Tuesday");
    EXPECT_EQ(uni.getTimeTable()[1].timeSlot.getStartTime(), "10:00");
    EXPECT_EQ(uni.getTimeTable()[1].instructor.getName(), "Dr. Johnson");
}

TEST(UniversityTest, ScheduleComplex) {
    TimeSlot mon1("Monday", "10:00", "11:00");
    TimeSlot mon2("Monday", "11:00", "12:00");
    TimeSlot mon3("Monday", "13:00", "14:00");
    TimeSlot mon4("Monday", "14:00", "15:00");

    std::vector<TimeSlot> uniTS({ mon1,mon2,mon3 });
    Course c1("math");
    c1.addPreferredTimeSlot(mon1);
    c1.addPreferredTimeSlot(mon3);

    Course c2("Chemistry");
    c2.addPreferredTimeSlot(mon2);
    Course c3("physics");
    c3.addPreferredTimeSlot(mon1);
 

    std::vector<Course> uniC({ c1,c2,c3 });
    Instructor i1("Isaac Newton");
    i1.addAvailability(mon1); 
    i1.addAvailability(mon3);
    i1.addPreferredCourse(c1);
    i1.addPreferredCourse(c3);
    Instructor i2("Dmitri Mendeleev");
    i2.addAvailability(mon2);
    i2.addAvailability(mon4);
    i2.addPreferredCourse(c2);
    i2.addPreferredCourse(c3);
    std::vector<Instructor> uniI({ i1,i2 });


    University uni(uniC,uniI,uniTS);
    uni.schedule();
    

    EXPECT_EQ(uni.getTimeTable().size(), 3);
    EXPECT_EQ(uni.getTimeTable()[0].course.getCourseName(), "math");
    EXPECT_EQ(uni.getTimeTable()[0].timeSlot, mon3);
    EXPECT_EQ(uni.getTimeTable()[0].instructor.getName(), "Isaac Newton");
    EXPECT_EQ(uni.getTimeTable()[1].course.getCourseName(), "Chemistry");
    EXPECT_EQ(uni.getTimeTable()[1].timeSlot, mon2);
    EXPECT_EQ(uni.getTimeTable()[1].instructor.getName(), "Dmitri Mendeleev");
    EXPECT_EQ(uni.getTimeTable()[2].course.getCourseName(), "physics");
    EXPECT_EQ(uni.getTimeTable()[2].timeSlot, mon1);
    EXPECT_EQ(uni.getTimeTable()[2].instructor.getName(), "Isaac Newton");
}

TEST(UniversityTest, SaveAndLoadState) {
    TimeSlot mon1("Monday", "10:00", "11:00");

    std::vector<TimeSlot> uniTS({ mon1 });
    Course c1("math");
    c1.addPreferredTimeSlot(mon1);

    std::vector<Course> uniC({ c1 });
    Instructor i1("Isaac Newton");
    i1.addAvailability(mon1);
    i1.addPreferredCourse(c1);
    std::vector<Instructor> uniI({ i1 });


    University uni(uniC, uniI, uniTS);
    uni.schedule();
    uni.saveState("result");

    University uni1;
    uni1.loadState("result");
    uni1.schedule();

    EXPECT_EQ(uni.getCourses(), uni1.getCourses());
    EXPECT_EQ(uni.getInstructors(), uni1.getInstructors());
    EXPECT_EQ(uni.getTimeSlots(), uni1.getTimeSlots());
    EXPECT_EQ(uni.getTimeTable(), uni1.getTimeTable());
}
