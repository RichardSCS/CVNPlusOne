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

TEST_F(RouteControllerUnitTests, CreateAppointmentTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&endTime=1730383800&location=Pharmacy"};
    routeController.createAppointment(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment Created : apptCode APPT2", response.body);
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