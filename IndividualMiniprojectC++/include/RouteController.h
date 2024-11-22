#ifndef ROUTECONTROLLER_H
#define ROUTECONTROLLER_H

#include "crow.h"
#include "Globals.h"
#include "MyFileDatabase.h"
#include "ApptDatabase.h"

class RouteController {
    private:
        MyFileDatabase* myFileDatabase;
        ApptDatabase* apptDatabase;

    public:
        RouteController();
        void initRoutes(crow::App<>& app);
        void setDatabase(MyFileDatabase* db);
        void setApptDatabase(ApptDatabase* db);

        void index(crow::response& res);
        void retrieveAppointment(const crow::request& req, crow::response& res);
        void deleteAppointment(const crow::request& req, crow::response& res);
        void createAppointment(const crow::request& req, crow::response& res);
        void updateAppointmentTime(const crow::request& req, crow::response& res);
        void updateAppointmentTitle(const crow::request& req, crow::response& res);
        void updateAppointmentLocation(const crow::request& req, crow::response& res);
        void updateAppointmentPatientId(const crow::request& req, crow::response& res);
        void updateAppointmentDoctorId(const crow::request& req, crow::response& res);
        void listAppointments(const crow::request& req, crow::response& res);

    protected:
        bool isStrEmpty(const std::string& value, crow::response& res);
        bool verifyTimeStr(const std::string& value, crow::response& res);
        void toUpper(std::string& string);
};

#endif 
