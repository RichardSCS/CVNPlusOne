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
        routeController->setApptDatabase(MyApp::getApptDatabase());
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

TEST_F(RouteControllerUnitTests, IndexEndpoint) {
    crow::response res;
    routeController->index(res);
    ASSERT_EQ(res.code, 200);
    ASSERT_EQ(res.body, "Welcome, in order to make an API call direct your browser or Postman to an endpoint \n\n This can be done using the following format: \n\n http://127.0.0.1:8080/endpoint?arg=value");
}

TEST_F(RouteControllerUnitTests, CreateAppointmentTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&endTime=1730383800&location=Pharmacy&participantId=patient1&createdBy=doctor1"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(201, response.code);
    ASSERT_EQ("Appointment Created", response.body.substr(0,19));
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingTitle) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?startTime=1730383200&endTime=1730383800&location=Pharmacy&participantId=patient1&createdBy=doctor1"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appointment title", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingPatientId) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&endTime=1730383800&location=Pharmacy&createdBy=doctor1"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appointment participantId", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingDoctorId) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&endTime=1730383800&location=Pharmacy&participantId=patient1"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appointment createdBy", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingStartTime) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&endTime=1730383800&location=Pharmacy&participantId=patient1&createdBy=doctor1"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appointment startTime", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingEndTime) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&location=Pharmacy&participantId=patient1&createdBy=doctor1"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appointment endTime", response.body);
}

TEST_F(RouteControllerUnitTests, CreateAppointmentMissingLocation) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&endTime=1730383800&participantId=patient1&createdBy=doctor1"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(201, response.code);
    ASSERT_EQ("Appointment Created", response.body.substr(0,19));
}

TEST_F(RouteControllerUnitTests, CreateAppointmentEmptyValues) {
    crow::request req;
    crow::response res;

    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ("Missing appointment title", res.body);

    res.clear();
    req.url_params = crow::query_string("?title=&participantId=patient1&createdBy=doctor1");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&participantId=&createdBy=doctor1");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&participantId=patient1&createdBy=");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=notanumber&participantId=patient1&createdBy=doctor1");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Time value must be a whole number.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=&participantId=patient1&createdBy=doctor1");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=11111&endTime=&participantId=patient1&createdBy=doctor1");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=11111&endTime=notanumber&participantId=patient1&createdBy=doctor1");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Time value must be a whole number.");

    res.clear();
    req.url_params = crow::query_string("?title=sample&startTime=111&endTime=11&participantId=patient1&createdBy=doctor1");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "End time cannot be before Start time.");

    res.clear();
    req.url_params = crow::query_string("?title=Office&startTime=10&endTime=10&participantId=patient1&createdBy=doctor1");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 201);
    ASSERT_EQ("Appointment Created", res.body.substr(0,19));

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
    
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appt code", response.body);
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
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ("Missing appt code", res.body);

    res.clear();
    req.url_params = crow::query_string("?apptCode=");
    routeController->deleteAppointment(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    req.url = "/deleteAppt";
    req.url_params = crow::query_string("?apptCode=appt5");
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

TEST_F(RouteControllerUnitTests, UpdateApptTimesEmptyValues) {
    crow::request req;
    crow::response res;

    routeController->updateAppointmentTime(req, res);
    ASSERT_EQ(res.code, 500);
    ASSERT_EQ(res.body, "An error has occurred");

    res.clear();
    req.url_params = crow::query_string("?apptCode=");
    routeController->updateAppointmentTime(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2");
    routeController->updateAppointmentTime(req, res);
    ASSERT_EQ(res.code, 500);
    ASSERT_EQ(res.body, "An error has occurred");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2&startTime=");
    routeController->updateAppointmentTime(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2&startTime=asdf");
    routeController->updateAppointmentTime(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Time value must be a whole number.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2&startTime=10");
    routeController->updateAppointmentTime(req, res);
    ASSERT_EQ(res.code, 500);
    ASSERT_EQ(res.body, "An error has occurred");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT3&startTime=10&endTime=");
    routeController->updateAppointmentTime(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT3&startTime=10&endTime=asdf");
    routeController->updateAppointmentTime(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Time value must be a whole number.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2&startTime=100&endTime=10");
    routeController->updateAppointmentTime(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Failed to update appointment time.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2&startTime=100&endTime=1000");
    req.url = "/updateApptTimes";
    testMethods(&req, &res, {crow::HTTPMethod::PATCH});
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

TEST_F(RouteControllerUnitTests, UpdateAppointmentPatientIdTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&apptParticipantId=newParticipant"};
    routeController->updateAppointmentParticipantId(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment participantId successfully updated.", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentPatientIdTestFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT133&apptParticipantId=newParticipant"};
    routeController->updateAppointmentParticipantId(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentDoctorIdTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&apptCreatedBy=newCreatedBy"};
    routeController->updateAppointmentCreatedBy(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment createdBy successfully updated.", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentDoctorIdTestFail) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT133&apptCreatedBy=newCreatedBy"};
    routeController->updateAppointmentCreatedBy(request, response);
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment Not Found", response.body);
}

TEST_F(RouteControllerUnitTests, UpdateAppointmentTitleEmptyValues) {
    crow::request req;
    crow::response res;

    routeController->updateAppointmentTitle(req, res);
    ASSERT_EQ(res.code, 500);
    ASSERT_EQ(res.body, "An error has occurred");

    res.clear();
    req.url_params = crow::query_string("?apptCode=");
    routeController->updateAppointmentTitle(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT113");
    routeController->updateAppointmentTitle(req, res);
    ASSERT_EQ(res.code, 500);
    ASSERT_EQ(res.body, "An error has occurred");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT113&apptTitle=");
    routeController->updateAppointmentTitle(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2&apptTitle=newTitle");
    req.url = "/updateApptTitle";
    testMethods(&req, &res, {crow::HTTPMethod::PATCH});
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

TEST_F(RouteControllerUnitTests, UpdateAppointmentLocationEmptyValue) {
    crow::request req;
    crow::response res;

    routeController->updateAppointmentLocation(req, res);
    ASSERT_EQ(res.code, 500);
    ASSERT_EQ(res.body, "An error has occurred");

    res.clear();
    req.url_params = crow::query_string("?apptCode=");
    routeController->updateAppointmentLocation(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2");
    routeController->updateAppointmentLocation(req, res);
    ASSERT_EQ(res.code, 500);
    ASSERT_EQ(res.body, "An error has occurred");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2&apptLocation=");
    routeController->updateAppointmentLocation(req, res);
    ASSERT_EQ(res.code, 400);
    ASSERT_EQ(res.body, "Empty query string value not allowed.");

    res.clear();
    req.url_params = crow::query_string("?apptCode=APPT2&apptLocation=newLocation");
    req.url = "/updateApptLocation";
    testMethods(&req, &res, {crow::HTTPMethod::PATCH});
}