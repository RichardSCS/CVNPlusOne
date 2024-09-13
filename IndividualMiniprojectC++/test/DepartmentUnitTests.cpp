// Copyright 2024 Jacob Aaronson

#include <gtest/gtest.h>
#include "Department.h" 

class DepartmentUnitTests : public ::testing::Test {
protected:
    static Department* testDepartment;

    static void SetUpTestSuite() {
        std::shared_ptr<Course> testCourse = std::make_shared<Course>(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
        std::shared_ptr<Course> testCourse2 = std::make_shared<Course>(500, "Adam Johnson", "420 ASA", "12:45-3:00");

        std::map<std::string, std::shared_ptr<Course>> testCourses;
        testCourses["TC1"] = testCourse;
        testCourses["TC2"] = testCourse2;

        testDepartment = new Department("EECS", testCourses, "Eric Adamson", 0);
    }

    static void TearDownTestSuite() {
        delete testDepartment;
    }
};

Department* DepartmentUnitTests::testDepartment = nullptr;

TEST_F(DepartmentUnitTests, ToStringTest) {
    std::string expectedResult = "EECS TC1: \nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55\nEECS TC2: \nInstructor: Adam Johnson; Location: 420 ASA; Time: 12:45-3:00\n";
    ASSERT_EQ(expectedResult, testDepartment->display());
}

TEST_F(DepartmentUnitTests, AddStudentTest) {
    ASSERT_EQ(0, testDepartment->getNumberOfMajors());
    testDepartment->addPersonToMajor();
    ASSERT_EQ(1, testDepartment->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, DropStudentTest) {
    ASSERT_EQ(1, testDepartment->getNumberOfMajors());
    testDepartment->dropPersonFromMajor();
    ASSERT_EQ(0, testDepartment->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, DropStudentWhenZeroTest) {
    ASSERT_EQ(0, testDepartment->getNumberOfMajors());
    testDepartment->dropPersonFromMajor();
    ASSERT_EQ(0, testDepartment->getNumberOfMajors());
}

TEST_F(DepartmentUnitTests, GetDepartmentChairTest) {
    ASSERT_EQ("Eric Adamson", testDepartment->getDepartmentChair());
}

TEST_F(DepartmentUnitTests, GetCourseSelectionTest) {
    ASSERT_EQ("Eric Adamson", testDepartment->getDepartmentChair());
}

TEST_F(DepartmentUnitTests, CreateCourseTest)
{
    testDepartment->createCourse("TC3", "Jerry Seinfeld", "STS 567", "7:30-8:30", 600);
    std::string expectedResult = "EECS TC1: \nInstructor: Griffin Newbold; Location: 417 IAB; Time: 11:40-12:55\nEECS TC2: \nInstructor: Adam Johnson; Location: 420 ASA; Time: 12:45-3:00\nEECS TC3: \nInstructor: Jerry Seinfeld; Location: STS 567; Time: 7:30-8:30\n";
    ASSERT_EQ(expectedResult, testDepartment->display());
}