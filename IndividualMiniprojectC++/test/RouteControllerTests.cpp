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

TEST_F(RouteControllerUnitTests, retrieveDepartment) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS"};
    routeController.retrieveDepartment(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("COMS 1004: \nInstructor: Adam Cannon; Location: 417 IAB; Time: 11:40-12:55\nCOMS 3134: \nInstructor: Brian Borowski; Location: 301 URIS; Time: 4:10-5:25\nCOMS 3157: \nInstructor: Jae Lee; Location: 417 IAB; Time: 4:10-5:25\nCOMS 3203: \nInstructor: Ansaf Salleb-Aouissi; Location: 301 URIS; Time: 10:10-11:25\nCOMS 3251: \nInstructor: Tony Dear; Location: 402 CHANDLER; Time: 1:10-3:40\nCOMS 3261: \nInstructor: Josh Alman; Location: 417 IAB; Time: 2:40-3:55\nCOMS 3827: \nInstructor: Daniel Rubenstein; Location: 207 Math; Time: 10:10-11:25\nCOMS 4156: \nInstructor: Gail Kaiser; Location: 501 NWC; Time: 10:10-11:25\n", response.body);
}

TEST_F(RouteControllerUnitTests, retrieveDepartmentFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMSSSS"};
    routeController.retrieveDepartment(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Department Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, retrieveCourse) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=1004"};
    routeController.retrieveCourse(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("\nInstructor: Adam Cannon; Location: 417 IAB; Time: 11:40-12:55", response.body);
}

TEST_F(RouteControllerUnitTests, retrieveCourseFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=1004444"};
    routeController.retrieveCourse(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Course Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, isCourseFull) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEOR&courseCode=2500"};
    routeController.isCourseFull(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("true", response.body);
}

TEST_F(RouteControllerUnitTests, isCourseFullNot) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=1004"};
    routeController.isCourseFull(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("false", response.body);
}

TEST_F(RouteControllerUnitTests, getMajorCountFromDept) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEOR"};
    routeController.getMajorCountFromDept(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("There are: 67 majors in the department", response.body);
}

TEST_F(RouteControllerUnitTests, getMajorCountFromDeptFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEORRRR"};
    routeController.getMajorCountFromDept(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Department Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, identifyDeptChair) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEOR"};
    routeController.identifyDeptChair(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Jay Sethuraman is the department chair.", response.body);
}

TEST_F(RouteControllerUnitTests, identifyDeptChairFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEORRRR"};
    routeController.identifyDeptChair(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Department Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, findCourseLocation) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEOR&courseCode=2500"};
    routeController.findCourseLocation(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("627 MUDD is where the course is located.", response.body);
}

TEST_F(RouteControllerUnitTests, findCourseLocationFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEORRRR&courseCode=2500"};
    routeController.findCourseLocation(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Department Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, findCourseInstructor) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEOR&courseCode=2500"};
    routeController.findCourseInstructor(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Uday Menon is the instructor for the course.", response.body);
}

TEST_F(RouteControllerUnitTests, findCourseInstructorFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEORRRR&courseCode=2500"};
    routeController.findCourseInstructor(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Department Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, findCourseTime) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEOR&courseCode=2500"};
    routeController.findCourseTime(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("The course meets at: 11:40-12:55", response.body);
}

TEST_F(RouteControllerUnitTests, findCourseTimeFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=IEORRRR&courseCode=2500"};
    routeController.findCourseInstructor(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Department Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, addMajorToDept) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS"};
    routeController.addMajorToDept(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Attribute was updated successfully", response.body);
}

TEST_F(RouteControllerUnitTests, setEnrollmentCount) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=3827&count=38"};
    routeController.setEnrollmentCount(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Attribute was updated successfully.", response.body);
}

TEST_F(RouteControllerUnitTests, setEnrollmentCountFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=382997&count=38"};
    routeController.setEnrollmentCount(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Course Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, setCourseInstructor) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=3827&instructor=Ratburn"};
    routeController.setCourseInstructor(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Attribute was updated successfully.", response.body);
}

TEST_F(RouteControllerUnitTests, setCourseInstructorFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=382997&instructor=Ratburn"};
    routeController.setCourseInstructor(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Course Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, setCourseTime) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=3827&time=11:50-12:50"};
    routeController.setCourseTime(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Attribute was updated successfully.", response.body);
}

TEST_F(RouteControllerUnitTests, setCourseTimeFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=382997&time=12:45-3:40"};
    routeController.setCourseTime(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Course Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, removeMajorFromDept) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS"};
    routeController.removeMajorFromDept(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Attribute was updated successfully", response.body);
}

TEST_F(RouteControllerUnitTests, removeMajorFromDeptFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMFF"};
    routeController.removeMajorFromDept(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Department Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, dropStudentFromCourse) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=3827"};
    routeController.dropStudentFromCourse(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Student has been dropped", response.body);
}

TEST_F(RouteControllerUnitTests, dropStudentFromCourseFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?deptCode=COMS&courseCode=382997"};
    routeController.dropStudentFromCourse(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Course Not Found", response.body);
}
