// Copyright 2024 CVNPlusOne

#include "RouteController.h"
#include <map>
#include <string>
#include <exception>
#include <iostream>
#include "Globals.h"
#include "MyFileDatabase.h"
#include "Appointment.h"
#include "../external_libraries/Crow-1.2.0-Darwin/include/crow.h"

int apptCodeCounter = 2;

// Utility function to handle exceptions
crow::response handleException(const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return crow::response{500, "An error has occurred"};
}

/**
 * Redirects to the homepage.
 *
 * @return A string containing the name of the html file to be loaded.
 */
void RouteController::index(crow::response& res) {
    res.write("Welcome, in order to make an API call direct your browser or Postman to an endpoint "
              "\n\n This can be done using the following format: \n\n http://127.0.0.1:8080/endpoint?arg=value");
    res.end();
}

void RouteController::retrieveAppointment(const crow::request& req, crow::response& res) {
    try {
        auto apptCode = req.url_params.get("apptCode");
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment Not Found");
        } else {
            res.code = 200;
            res.write(it->second.display());
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::updateAppointmentTitle(const crow::request& req, crow::response& res) {
    try {
        auto apptCode = req.url_params.get("apptCode");
        auto apptTitle = req.url_params.get("apptTitle");
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment Not Found");
        } else {
            it->second.setTitle(apptTitle);
            res.code = 200;
            res.write("Appointment title successfully updated.");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::updateAppointmentLocation(const crow::request& req, crow::response& res) {
    try {
        auto apptCode = req.url_params.get("apptCode");
        auto apptLocation = req.url_params.get("apptLocation");
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment Not Found");
        } else {
            it->second.setLocation(apptLocation);
            res.code = 200;
            res.write("Appointment location successfully updated.");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::updateAppointmentTime(const crow::request& req, crow::response& res) {
    try {
         std::cout << "gothere" << std::endl;   
        auto apptCode = req.url_params.get("apptCode");
        auto startTimeStr = (req.url_params.get("startTime"));
        auto endTimeStr = (req.url_params.get("endTime"));

        int startTime = std::stoi(startTimeStr);
        int endTime = std::stoi(endTimeStr);
       
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();
        

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment Not Found");
        } else {
            if (it->second.setTimes(startTime, endTime)) {
                res.code = 200;
                res.write("Appointment time successfully updated.");
            } else {
                res.code = 400;
                res.write("Failed to update appointment time.");
            }
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::createAppointment(const crow::request& req, crow::response& res) {
    try {
        auto title = req.url_params.get("title");
        auto startTime = std::stoi(req.url_params.get("startTime"));
        auto endTime = std::stoi(req.url_params.get("endTime"));
        auto location = req.url_params.get("location");
        std::string apptCode = "APPT" + std::to_string(apptCodeCounter++);

        auto appointmentMapping = myFileDatabase->getAppointmentMapping();

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 200;
            res.write("Appointment Created : apptCode ");
            res.write(apptCode);
            Appointment appt(apptCode, title, startTime, endTime, location);
            appointmentMapping[apptCode] = appt;
            myFileDatabase->setApptMapping(appointmentMapping);
        } else {
            res.code = 404;
            res.write("Appointment Exists : ");
            res.write(it->second.display()); // Use dot operator to access method
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

// Initialize API Routes
void RouteController::initRoutes(crow::App<>& app) {

    CROW_ROUTE(app, "/retrieveAppt")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            retrieveAppointment(req, res);
        });
    CROW_ROUTE(app, "/createAppt")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            createAppointment(req, res);
        });
    CROW_ROUTE(app, "/updateApptTitle")
        .methods(crow::HTTPMethod::PATCH)([this](const crow::request& req, crow::response& res) {
            updateAppointmentTitle(req, res);
        });
    CROW_ROUTE(app, "/updateApptTimes")
        .methods(crow::HTTPMethod::PATCH)([this](const crow::request& req, crow::response& res) {
            updateAppointmentTime(req, res);
        });
}

void RouteController::setDatabase(MyFileDatabase *db) {
    myFileDatabase = db;
}
