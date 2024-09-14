// Copyright 2024 Jacob Aaronson

#include <gtest/gtest.h>
#include "MyFileDatabase.h" 

class MyFileDatabaseUnitTests : public ::testing::Test {
protected:
    
    static void SetUpTestSuite() {
    }

    static void TearDownTestSuite() {
    }
};

TEST_F(MyFileDatabaseUnitTests, TestGetAndSetMapping) {    
    MyFileDatabase* testMyFileDatabase = new MyFileDatabase(0, "testdbfile.bin");
    std::shared_ptr<Course> testCourse = std::make_shared<Course>(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    std::shared_ptr<Course> testCourse2 = std::make_shared<Course>(500, "Adam Johnson", "420 ASA", "12:45-3:00");

    std::map<std::string, std::shared_ptr<Course>> testCourses;
    testCourses["TC1"] = testCourse;
    testCourses["TC2"] = testCourse2;

    Department* testDepartment;
    testDepartment = new Department("EECS", testCourses, "Eric Adamson", 0);

    std::map<std::string, Department> testDepartments;
    testDepartments["EECS"] = *testDepartment;

    testMyFileDatabase->setMapping(testDepartments);
    std::map<std::string, Department> depts = testMyFileDatabase->getDepartmentMapping();
    ASSERT_EQ(depts["EECS"].display(), testDepartments["EECS"].display());
}

TEST_F(MyFileDatabaseUnitTests, TestSerialization) {    
    MyFileDatabase* testMyFileDatabase = new MyFileDatabase(1, "testdbfile2.bin");
    std::shared_ptr<Course> testCourse = std::make_shared<Course>(250, "Griffin Newbold", "417 IAB", "11:40-12:55");
    std::shared_ptr<Course> testCourse2 = std::make_shared<Course>(500, "Adam Johnson", "420 ASA", "12:45-3:00");

    std::map<std::string, std::shared_ptr<Course>> testCourses;
    testCourses["TC1"] = testCourse;
    testCourses["TC2"] = testCourse2;

    Department* testDepartment;
    testDepartment = new Department("EECS", testCourses, "Eric Adamson", 0);

    std::map<std::string, Department> testDepartments;
    testDepartments["EECS"] = *testDepartment;

    testMyFileDatabase->saveContentsToFile();
    MyFileDatabase testMyFileDatabase2{0, "testdbfile2.bin"};
    std::map<std::string, Department> depts = testMyFileDatabase2.getDepartmentMapping();
    ASSERT_EQ(testMyFileDatabase->display(), testMyFileDatabase2.display());
}