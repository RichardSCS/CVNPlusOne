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

