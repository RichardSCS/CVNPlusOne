// Copyright 2024 CVNPlusOne

#include <gtest/gtest.h>
#include "RouteController.h" 
#include "MyApp.h"

class RouteControllerUnitTests : public ::testing::Test {
protected:
    static crow::SimpleApp* app;
    static RouteController* routeController;
    static std::vector<crow::HTTPMethod> methods;

    static void SetUpTestSuite() {
        MyApp::run("setup");
        MyApp::onTermination();
        MyApp::run("");

        app = new crow::SimpleApp();
        routeController = new RouteController;

        routeController->initRoutes(*app);
        app->validate();
        routeController->setDatabase(MyApp::getDatabase());
        routeController.setApptDatabase(MyApp::getApptDatabase());
    }

    static void TearDownTestSuite() {
        delete app;
        delete routeController;
    }

    static void testMethods(crow::request* req, crow::response* res,
            std::initializer_list<crow::HTTPMethod> acceptableMethods) {
        for (const auto& method : methods) {
            res->clear();
            req->method = method;
            app->handle_full(*req, *res);
            if (std::any_of(acceptableMethods.begin(), acceptableMethods.end(),
            [method](crow::HTTPMethod acceptableMethod)
            { return method == acceptableMethod; })) {
                if (method == crow::HTTPMethod::POST) {
                    ASSERT_EQ(res->code, 201);
                } else {
                    ASSERT_EQ(res->code, 200);
                }
            } else {
                ASSERT_EQ(res->code, 405);
            }
        }
    }
};

crow::SimpleApp* RouteControllerUnitTests::app = nullptr;
RouteController* RouteControllerUnitTests::routeController = nullptr;
std::vector<crow::HTTPMethod> RouteControllerUnitTests::methods = {crow::HTTPMethod::GET,
                                                                   crow::HTTPMethod::POST,
                                                                   crow::HTTPMethod::PUT,
                                                                   crow::HTTPMethod::PATCH,
                                                                   crow::HTTPMethod::DELETE};

TEST_F(RouteControllerUnitTests, CreateAppointmentTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&endTime=1730383800&location=Pharmacy"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(201, response.code);
    ASSERT_EQ("Appointment Created : apptCode APPT4", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingTitle) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?startTime=1730383200&endTime=1730383800&location=Pharmacy"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appointment title", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingStartTime) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&endTime=1730383800&location=Pharmacy"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appointment startTime", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingEndTime) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&location=Pharmacy"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appointment endTime", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingLocation) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&endTime=1730383800"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(201, response.code);
    ASSERT_EQ("Appointment Created : apptCode APPT5", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentEmptyValues) {
    crow::request req;
    crow::response res;

    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ("Missing appointment title", res.body);

    res.clear();
    req.url_params = crow::query_string("?title=");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=notanumber");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Time value must be a whole number.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=11111&endTime=");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=11111&endTime=notanumber");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Time value must be a whole number.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=111&endTime=11");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "End time cannot be before Start time.");

    res.clear();
    req.url_params = crow::query_string("?title=Office&startTime=10&endTime=10");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 201);
    ASSERT_EQ(res.body, "Appointment Created : apptCode APPT6");

    req.url = "/createAppt";
    testMethods(&req, &res, {crow::HTTPMethod::POST});
}

TEST_F(RouteControllerUnitTests, DeleteAppointmentSuccess) {
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT1"};
    
    routeController->deleteAppointment(request, response);
    
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment deleted successfully", response.body);
    
    auto appointmentMapping = MyApp::getDatabase()->getAppointmentMapping();
    ASSERT_EQ(appointmentMapping.find("APPT1"), appointmentMapping.end());
}

TEST_F(RouteControllerUnitTests, DeleteAppointmentMissingCode) {
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?"};
    
    routeController->deleteAppointment(request, response);
    
    ASSERT_EQ(500, response.code);
    ASSERT_EQ("An error has occurred", response.body);
}

TEST_F(RouteControllerUnitTests, DeleteAppointmentNotFound) {
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=NOTFOUND"};
    
    routeController->deleteAppointment(request, response);
    
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment not found", response.body);
}

TEST_F(RouteControllerUnitTests, DeleteAppointmentTest) {
    crow::request req;
    crow::response res;

    routeController->deleteAppointment(req, res);
    ASSERT_EQ(res.code, 500);
    ASSERT_EQ("An error has occurred", res.body);

    res.clear();
    req.url_params = crow::query_string("?apptCode=");
    routeController->deleteAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    req.url = "/deleteAppt";
    req.url_params = crow::query_string("?apptCode=appt4");
    testMethods(&req, &res, {crow::HTTPMethod::DELETE});
}

TEST_F(RouteControllerUnitTests, RetrieveAppointmentTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2"};
    routeController->retrieveAppointment(request, response);
    ASSERT_EQ(200, response.code);
    time_t startTime = 1730383500;
    time_t endTime = 1730387800;
    char strt[32], end[32];
    std::strftime(strt, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&startTime));
    std::strftime(end, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&endTime));
    std::string strtStr = strt;
    std::string endStr = end;
    ASSERT_EQ("\nTitle: Diagnostic Test; Location: Hospital; Start Time: " + strtStr + "; End Time: " + endStr, response.body);
}

TEST_F(RouteControllerUnitTests, RetrieveAppointmentTestFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT133"};
    routeController->retrieveAppointment(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, RetrieveAppt) {
    crow::request req;
    crow::response res;

    routeController->retrieveAppointment(req, res);
    ASSERT_EQ(res.code, 500);
    ASSERT_EQ("An error has occurred", res.body);

    res.clear();
    req.url_params = crow::query_string("?apptCode=");
    routeController->retrieveAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=appt2");
    routeController->retrieveAppointment(req, res);
    ASSERT_EQ(res.code, 200);

    req.url = "/retrieveAppt";
    testMethods(&req, &res, {crow::HTTPMethod::GET});
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTimeTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&startTime=1730383201&endTime=1730383801"};
    routeController->updateAppointmentTime(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment time successfully updated.", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTimeTestFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT133&startTime=1730383201&endTime=1730383801"};
    routeController->updateAppointmentTime(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTimeTestFail2) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&startTime=1730383801&endTime=1730383800"};
    routeController->updateAppointmentTime(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Failed to update appointment time.", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTitleTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&apptTitle=\"PT Appointment\""};
    routeController->updateAppointmentTitle(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment title successfully updated.", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTitleTestFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT133&apptTitle=PT Appointment"};
    routeController->updateAppointmentTitle(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentLocationTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&apptLocation=\"Doctor Office\""};
    routeController->updateAppointmentLocation(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment location successfully updated.", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentLocationTestFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT133&apptLocation=\"Doctor Office\""};
    routeController->updateAppointmentLocation(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment Not Found", response.body);
}
