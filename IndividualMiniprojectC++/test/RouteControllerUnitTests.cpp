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
