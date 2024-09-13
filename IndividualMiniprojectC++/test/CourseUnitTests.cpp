// Copyright 2024 Jacob Aaronson

#include <gtest/gtest.h>
#include "Course.h" 

class CourseUnitTests : public ::testing::Test {
protected:
    static Course* testCourse;

    static void SetUpTestSuite() {
        testCourse = new Course(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    }

    static void TearDownTestSuite() {
        delete testCourse;
    }
};

Course* CourseUnitTests::testCourse = nullptr;

TEST_F(CourseUnitTests, ToStringTest) {
    std::string expectedResult = "\nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55";
    ASSERT_EQ(expectedResult, testCourse->display());
}

TEST_F(CourseUnitTests, EnrollStudentTest) {
    ASSERT_EQ(0, testCourse->getEnrolledStudentCount());
    testCourse->enrollStudent();
    ASSERT_EQ(1, testCourse->getEnrolledStudentCount());
}

TEST_F(CourseUnitTests, DropStudentTest) {
    ASSERT_EQ(1, testCourse->getEnrolledStudentCount());
    testCourse->dropStudent();
    ASSERT_EQ(0, testCourse->getEnrolledStudentCount());
}

TEST_F(CourseUnitTests, DropStudentWhenEmptyTest) {
    ASSERT_EQ(0, testCourse->getEnrolledStudentCount());
    testCourse->dropStudent();
    ASSERT_EQ(0, testCourse->getEnrolledStudentCount());
}

TEST_F(CourseUnitTests, EnrollStudentWhenFullTest) {
    testCourse->setEnrolledStudentCount(250);
    ASSERT_EQ(250, testCourse->getEnrolledStudentCount());
    testCourse->enrollStudent();
    ASSERT_EQ(250, testCourse->getEnrolledStudentCount());
}

TEST_F(CourseUnitTests, CourseLocationTest) {
    ASSERT_EQ("417 IAB", testCourse->getCourseLocation());
    testCourse->reassignLocation("518 IAB");
    ASSERT_EQ("518 IAB", testCourse->getCourseLocation());
}

TEST_F(CourseUnitTests, InstructorNameTest) {
    ASSERT_EQ("Griffin Newbold", testCourse->getInstructorName());
    testCourse->reassignInstructor("Eric Klebold");
    ASSERT_EQ("Eric Klebold", testCourse->getInstructorName());
}

TEST_F(CourseUnitTests, CourseTimeSlotTest) {
    ASSERT_EQ("11:40-12:55", testCourse->getCourseTimeSlot());
    testCourse->reassignTime("12:50-12:55");
    ASSERT_EQ("12:50-12:55", testCourse->getCourseTimeSlot());
}
