// Copyright 2024 CVNPlusOne

#include "RouteController.h"
#include <map>
#include <string>
#include <exception>
#include <iostream>
#include "Globals.h"
#include "MyFileDatabase.h"
#include "Appointment.h"
#include "ApptDatabase.h"
#include "crow.h"
#include "regex"

int codeCount = 4;

// Utility function to handle exceptions
crow::response handleException(const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return crow::response{500, "An error has occurred"};
}

bool RouteController::isStrEmpty(const std::string& value, crow::response& res) {
    std::regex re_empty("^\\s*$");
    if (std::regex_match(value, re_empty)) {
        res.code = 400;
        res.write("Empty query string value not allowed.");
        return true;
    }
    return false;
}

bool RouteController::verifyTimeStr(const std::string& value, crow::response& res) {
    if (isStrEmpty(value, res))
        return false;

    std::regex time("^\\d+$");
    if (!std::regex_match(value, time)) {
        res.code = 400;
        res.write("Time value must be a whole number.");
        return false;
    }
    return true;
}

void RouteController::toUpper(std::string& string) {
    std::transform(string.cbegin(), string.cend(), string.begin(),
                    [](auto c) { return toupper(c); });
}

RouteController::RouteController() : myFileDatabase(nullptr), apptDatabase(nullptr) {}

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
        std::string apptCode = req.url_params.get("apptCode");
        if (isStrEmpty(apptCode, res)) {
            res.end();
            return;
        }
        toUpper(apptCode);
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
        if (isStrEmpty(apptCode, res) || isStrEmpty(apptTitle, res)) {
            res.end();
            return;
        }
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment Not Found");
        } else {
            it->second.setTitle(apptTitle);
            myFileDatabase->setApptMapping(appointmentMapping);
            if (apptDatabase) {
                apptDatabase->saveApptToDatabase(it->second);
            }
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
        if (isStrEmpty(apptCode, res) || isStrEmpty(apptLocation, res)) {
            res.end();
            return;
        }
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment Not Found");
        } else {
            it->second.setLocation(apptLocation);
            myFileDatabase->setApptMapping(appointmentMapping);
            if (apptDatabase) {
                apptDatabase->saveApptToDatabase(it->second);
            }
            res.code = 200;
            res.write("Appointment location successfully updated.");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::updateAppointmentPatientId(const crow::request& req, crow::response& res) {
    try {
        auto apptCode = req.url_params.get("apptCode");
        auto apptPatientId = req.url_params.get("apptPatientId");
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment Not Found");
        } else {
            it->second.setPatientId(apptPatientId);
            myFileDatabase->setApptMapping(appointmentMapping);
            res.code = 200;
            res.write("Appointment patientId successfully updated.");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::updateAppointmentDoctorId(const crow::request& req, crow::response& res) {
    try {
        auto apptCode = req.url_params.get("apptCode");
        auto apptDotorId = req.url_params.get("apptDoctorId");
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment Not Found");
        } else {
            it->second.setDoctorId(apptDotorId);
            myFileDatabase->setApptMapping(appointmentMapping);
            res.code = 200;
            res.write("Appointment doctorId successfully updated.");
        }
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::listAppointments(const crow::request& req, crow::response& res) {
    try {
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();
        
        std::string appointmentList = "[";
        bool first = true;

        for (const auto& appt : appointmentMapping) {
            if (!first) {
                appointmentList += ", ";
            }
            appointmentList += "\"" + appt.first + "\"";
            first = false;
        }

        appointmentList += "]";

        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(appointmentList);
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::updateAppointmentTime(const crow::request& req, crow::response& res) {
    try {
        auto apptCode = req.url_params.get("apptCode");
        auto startTimeStr = (req.url_params.get("startTime"));
        auto endTimeStr = (req.url_params.get("endTime"));
        if (isStrEmpty(apptCode, res) || isStrEmpty(startTimeStr, res) || isStrEmpty(endTimeStr, res)) {
            res.end();
            return;
        }

        int startTime = std::stoi(startTimeStr);
        int endTime = std::stoi(endTimeStr);
       
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();
        

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment Not Found");
        } else {
            if (it->second.setTimes(startTime, endTime)) {
                myFileDatabase->setApptMapping(appointmentMapping);
                if (apptDatabase) {
                    apptDatabase->saveApptToDatabase(it->second);
                }
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

void RouteController::deleteAppointment(const crow::request& req, crow::response& res) {
    try {
        std::string apptCode = req.url_params.get("apptCode");

        if (isStrEmpty(apptCode, res)) {
            res.end();
            return;
        }

        toUpper(apptCode);

        auto appointmentMapping = myFileDatabase->getAppointmentMapping();
        auto it = appointmentMapping.find(apptCode);

        if (it == appointmentMapping.end()) {
            res.code = 404;
            res.write("Appointment not found");
            res.end();
            return;
        }

        appointmentMapping.erase(it);
        myFileDatabase->removeAppointment(apptCode);
        if (apptDatabase) {
            apptDatabase->deleteApptFromDatabase(apptCode);
        }

        res.code = 200;
        res.write("Appointment deleted successfully");
        res.end();
    } catch (const std::exception& e) {
        res = handleException(e);
    }
}

void RouteController::createAppointment(const crow::request& req, crow::response& res) {
    try {
        auto title = req.url_params.get("title");
        if (!title) {
            res.code = 400; 
            res.write("Missing appointment title");
            res.end();
            return;
        }

        std::string titleStr = title;
        if (isStrEmpty(titleStr, res)) {
            res.end();
            return;
        }

        auto patientId = req.url_params.get("patientId");
        if (!patientId) {
            res.code = 400; 
            res.write("Missing appointment patientId");
            res.end();
            return;
        }

        std::string patientIdStr = patientId;
        if (isStrEmpty(patientIdStr, res)) {
            res.end();
            return;
        }

        auto doctorId = req.url_params.get("doctorId");
        if (!doctorId) {
            res.code = 400; 
            res.write("Missing appointment doctorId");
            res.end();
            return;
        }

        std::string doctorIdStr = doctorId;
        if (isStrEmpty(doctorIdStr, res)) {
            res.end();
            return;
        }

        auto startTimeStr = req.url_params.get("startTime");
        if (!startTimeStr) {
            res.code = 400; 
            res.write("Missing appointment startTime");
            res.end();
            return;
        }

        if (!verifyTimeStr(startTimeStr, res)) {
            res.end();
            return;
        }

        auto startTime = std::stoi(startTimeStr);

        auto endTimeStr = req.url_params.get("endTime");
        if (!endTimeStr) {
            res.code = 400; 
            res.write("Missing appointment endTime");
            res.end();
            return;
        }

        if (!verifyTimeStr(endTimeStr, res)) {
            res.end();
            return;
        }

        auto endTime = std::stoi(endTimeStr);

        if (endTime < startTime) {
            res.code = 400;
            res.body = "End time cannot be before Start time.";
            res.end();
            return;
        }

        bool freeChar = false;
        auto location = req.url_params.get("location");
        if (!location) {
            freeChar = true;
            location = reinterpret_cast<char*>(malloc(1));
            location[0] = '\0';
        }

        if (apptDatabase) {
            int dbCount = apptDatabase->getCodeCount();
            if (dbCount > codeCount) {
                    codeCount = dbCount;
            }
        }

        std::string apptCode = "APPT" + std::to_string(++codeCount);

        auto appointmentMapping = myFileDatabase->getAppointmentMapping();

        auto it = appointmentMapping.find(apptCode);
        if (it == appointmentMapping.end()) {
            res.code = 201;
            res.write("Appointment Created : apptCode ");
            res.write(apptCode);
            Appointment appt(apptCode, title, startTime, endTime, location, patientId, doctorId);
            appointmentMapping[apptCode] = appt;
            myFileDatabase->setApptMapping(appointmentMapping);
            if (apptDatabase) {
                apptDatabase->saveApptToDatabase(appt);
            }
        } else {
            res.code = 404;
            res.write("Appointment Exists : ");
            res.write(it->second.display()); // Use dot operator to access method
        }
        if (freeChar)
            free(location);

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
    
    CROW_ROUTE(app, "/deleteAppt")
        .methods(crow::HTTPMethod::DELETE)([this](const crow::request& req, crow::response& res) {
            deleteAppointment(req, res);
        });
    
    CROW_ROUTE(app, "/createAppt")
        .methods(crow::HTTPMethod::POST)([this](const crow::request& req, crow::response& res) {
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
    CROW_ROUTE(app, "/updateApptLocation")
        .methods(crow::HTTPMethod::PATCH)([this](const crow::request& req, crow::response& res) {
            updateAppointmentLocation(req, res);
        });
    CROW_ROUTE(app, "/updateApptPatientId")
        .methods(crow::HTTPMethod::PATCH)([this](const crow::request& req, crow::response& res) {
            updateAppointmentPatientId(req, res);
        });
    CROW_ROUTE(app, "/updateApptDoctorId")
        .methods(crow::HTTPMethod::PATCH)([this](const crow::request& req, crow::response& res) {
            updateAppointmentDoctorId(req, res);
        });
    CROW_ROUTE(app, "/listAppts")
        .methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
            listAppointments(req, res);
        });
}

void RouteController::setDatabase(MyFileDatabase *db) {
    myFileDatabase = db;
}

void RouteController::setApptDatabase(ApptDatabase *db) {
    apptDatabase = db;
}
