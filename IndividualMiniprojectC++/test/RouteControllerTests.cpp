// Copyright 2024 Jacob Aaronson

#include <gtest/gtest.h>
#include "RouteController.h" 
#include "MyApp.h"

class RouteControllerUnitTests : public ::testing::Test {
protected:
    static MyApp* myApp;
    crow::SimpleApp app;
    RouteController routeController;

    RouteControllerUnitTests() {
        routeController.initRoutes(app);
        myApp->run("");
        routeController.setDatabase(myApp->getDatabase());
    }
    
    static void SetUpTestSuite() {
        
    }

    static void TearDownTestSuite() {
    }

};

MyApp* RouteControllerUnitTests::myApp = nullptr;

TEST_F(RouteControllerUnitTests, RetrieveCoursesTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?courseCode=1004"};
    routeController.retrieveCourses(request, response);
    ASSERT_EQ(200, response.code);

    ASSERT_EQ("COMS 1004:\nInstructor: Adam Cannon; Location: 417 IAB; Time: 11:40-12:55", response.body);
}

TEST_F(RouteControllerUnitTests, RetrieveCoursesTestFailure) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?courseCode=1004999"};
    routeController.retrieveCourses(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("No Courses Found", response.body);
}

TEST_F(RouteControllerUnitTests, EnrollStudentInCourseTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=1004"};
    routeController.enrollStudentInCourse(request, response);
    ASSERT_EQ(200, response.code);

    ASSERT_EQ("Student has been enrolled", response.body);
}

TEST_F(RouteControllerUnitTests, EnrollStudentInCourseTestFailureDept) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=FFFF&courseCode=1004"};
    routeController.enrollStudentInCourse(request, response);
    ASSERT_EQ(404, response.code);

    ASSERT_EQ("Department Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, EnrollStudentInCourseTestFailureCourse) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=100490"};
    routeController.enrollStudentInCourse(request, response);
    ASSERT_EQ(404, response.code);

    ASSERT_EQ("Course Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, EnrollStudentInCourseTestFailureCapacity) {  
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEOR&courseCode=2500"};
    routeController.enrollStudentInCourse(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Student has not been enrolled", response.body);
}

TEST_F(RouteControllerUnitTests, setEnrolledStudentCount) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=3134&count=257"};
    routeController.setEnrollmentCount(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Attribute was updated successfully.", response.body);
}