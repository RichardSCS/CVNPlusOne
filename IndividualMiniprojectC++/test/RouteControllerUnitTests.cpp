// Copyright 2024 CVNPlusOne

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
        myApp->run("setup");
        routeController.setDatabase(myApp->getDatabase());
    }

    static void SetUpTestSuite() {

    }

    static void TearDownTestSuite() {
    }

};

MyApp* RouteControllerUnitTests::myApp = nullptr;

TEST_F(RouteControllerUnitTests, CreateAppointmentTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&endTime=1730383800&location=Pharmacy"};
    routeController.createAppointment(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment Created : apptCode APPT4", response.body);
}

TEST_F(RouteControllerUnitTests, DeleteAppointmentSuccess) {
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT1"};
    
    routeController.deleteAppointment(request, response);
    
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment deleted successfully", response.body);
    
    auto appointmentMapping = myApp->getDatabase()->getAppointmentMapping();
    ASSERT_EQ(appointmentMapping.find("APPT1"), appointmentMapping.end());
}

TEST_F(RouteControllerUnitTests, DeleteAppointmentMissingCode) {
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?"};
    
    routeController.deleteAppointment(request, response);
    
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appointment code", response.body);
}

TEST_F(RouteControllerUnitTests, DeleteAppointmentNotFound) {
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=NOTFOUND"};
    
    routeController.deleteAppointment(request, response);
    
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment not found", response.body);
}
TEST_F(RouteControllerUnitTests, RetrieveAppointmentTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT1"};
    routeController.retrieveAppointment(request, response);
    ASSERT_EQ(200, response.code);
    time_t startTime = 1730383200;
    time_t endTime = 1730386800;
    char strt[32], end[32];
    std::strftime(strt, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&startTime));
    std::strftime(end, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&endTime));
    std::string strtStr = strt;
    std::string endStr = end;
    ASSERT_EQ("\nTitle: Doctor Appointment; Location: Clinic; Start Time: " + strtStr + "; End Time: " + endStr, response.body);
}

TEST_F(RouteControllerUnitTests, RetrieveAppointmentTestFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT133"};
    routeController.retrieveAppointment(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTimeTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT1&startTime=1730383201&endTime=1730383801"};
    routeController.updateAppointmentTime(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment time successfully updated.", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTimeTestFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT133&startTime=1730383201&endTime=1730383801"};
    routeController.updateAppointmentTime(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTimeTestFail2) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT1&startTime=1730383801&endTime=1730383800"};
    routeController.updateAppointmentTime(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Failed to update appointment time.", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTitleTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT1&apptTitle=\"PT Appointment\""};
    routeController.updateAppointmentTitle(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment title successfully updated.", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTitleTestFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT133&apptTitle=PT Appointment"};
    routeController.updateAppointmentTitle(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment Not Found", response.body);
}
