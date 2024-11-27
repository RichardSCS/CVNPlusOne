// Copyright 2024 CVNPlusOne

#include <gtest/gtest.h>
#include "RouteController.h" 
#include "MyApp.h"
#include "ApptDatabase.h"

class IntegrationTests : public ::testing::Test {
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

crow::SimpleApp* IntegrationTests::app = nullptr;
RouteController* IntegrationTests::routeController = nullptr;
std::vector<crow::HTTPMethod> IntegrationTests::methods = {crow::HTTPMethod::GET,
                                                                   crow::HTTPMethod::POST,
                                                                   crow::HTTPMethod::PUT,
                                                                   crow::HTTPMethod::PATCH,
                                                                   crow::HTTPMethod::DELETE};

TEST_F(IntegrationTests, CreateAppointmentTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?title=Meeting&startTime=1730383200&endTime=1730383800&location=Pharmacy&createdBy=creator1&participantId=participant1"};
    routeController->createAppointment(request, response);
    ASSERT_EQ(201, response.code);
    ASSERT_EQ("Appointment Created", response.body.substr(0,19));

    std::string apptCode = response.body.substr(31, std::string::npos);
    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase(apptCode);
    ASSERT_EQ(appt->getApptTitle(), "Meeting");
    ASSERT_EQ(appt->getApptStartTime(), 1730383200);
    ASSERT_EQ(appt->getApptEndTime(), 1730383800);
    ASSERT_EQ(appt->getApptLocation(), "Pharmacy");
    ASSERT_EQ(appt->getCreatedBy(), "creator1");
    ASSERT_EQ(appt->getParticipantId(), "participant1");
    delete appt;
}

TEST_F(IntegrationTests, CreateAppointmentEmptyLocation) {
    crow::request req;
    crow::response res;
    req.url_params = crow::query_string("?title=Office&startTime=10&endTime=10&createdBy=creator2&participantId=participant2");
    routeController->createAppointment(req, res);
    ASSERT_EQ(res.code, 201);
    ASSERT_EQ("Appointment Created", res.body.substr(0,19));

    std::string apptCode = res.body.substr(31, std::string::npos);
    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase(apptCode);
    ASSERT_EQ(appt->getApptTitle(), "Office");
    ASSERT_EQ(appt->getApptStartTime(), 10);
    ASSERT_EQ(appt->getApptEndTime(), 10);
    ASSERT_EQ(appt->getApptLocation(), "");
    ASSERT_EQ(appt->getCreatedBy(), "creator2");
    ASSERT_EQ(appt->getParticipantId(), "participant2");
    delete appt;
}

TEST_F(IntegrationTests, DeleteAppointmentMissingCode) {
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?"};
    
    routeController->deleteAppointment(request, response);
    
    ASSERT_EQ(400, response.code);
    ASSERT_EQ("Missing appt code", response.body);

    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase("APPT1");
    ASSERT_NE(appt, nullptr);
}

TEST_F(IntegrationTests, DeleteAppointmentNotFound) {
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=NOTFOUND"};
    
    routeController->deleteAppointment(request, response);
    
    ASSERT_EQ(404, response.code);
    ASSERT_EQ("Appointment not found", response.body);

    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase("APPT1");
    ASSERT_NE(appt, nullptr);
}

TEST_F(IntegrationTests, DeleteAppointmentSuccess) {
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT1"};
    
    routeController->deleteAppointment(request, response);
    
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment deleted successfully", response.body);
    
    auto appointmentMapping = MyApp::getDatabase()->getAppointmentMapping();
    ASSERT_EQ(appointmentMapping.find("APPT1"), appointmentMapping.end());

    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase("APPT1");
    ASSERT_EQ(appt, nullptr);
}

TEST_F(IntegrationTests, UpdateAppointmentTimeTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&startTime=99999&endTime=9999999"};
    routeController->updateAppointmentTime(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment time successfully updated.", response.body);

    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase("APPT2");
    ASSERT_EQ(appt->getApptStartTime(), 99999);
    ASSERT_EQ(appt->getApptEndTime(), 9999999);
}

TEST_F(IntegrationTests, UpdateAppointmentTitleTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&apptTitle=New title"};
    routeController->updateAppointmentTitle(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment title successfully updated.", response.body);

    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase("APPT2");
    ASSERT_EQ(appt->getApptTitle(), "New title");
}

TEST_F(IntegrationTests, UpdateAppointmentLocationTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&apptLocation=New location"};
    routeController->updateAppointmentLocation(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment location successfully updated.", response.body);

    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase("APPT2");
    ASSERT_EQ(appt->getApptLocation(), "New location");
}

TEST_F(IntegrationTests, UpdateAppointmentParticipantIdTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&apptParticipantId=Homer Simpson"};
    routeController->updateAppointmentParticipantId(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment participantId successfully updated.", response.body);

    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase("APPT2");
    ASSERT_EQ(appt->getParticipantId(), "Homer Simpson");
}

TEST_F(IntegrationTests, updateAppointmentCreatedByTest) {    
    crow::request request;
    crow::response response;
    request.url_params = crow::query_string{"?apptCode=APPT2&apptCreatedBy=Dr. Hibbert"};
    routeController->updateAppointmentCreatedBy(request, response);
    ASSERT_EQ(200, response.code);
    ASSERT_EQ("Appointment createdBy successfully updated.", response.body);

    Appointment* appt = MyApp::getApptDatabase()->getAppointmentFromDatabase("APPT2");
    ASSERT_EQ(appt->getCreatedBy(), "Dr. Hibbert");
}
