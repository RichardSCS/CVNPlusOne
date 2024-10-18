#ifndef ROUTECONTROLLER_H
#define ROUTECONTROLLER_H

#include "crow.h"
#include "Globals.h"
#include "MyFileDatabase.h"

class RouteController {
    private:
        MyFileDatabase* myFileDatabase;

    public:
        RouteController();
        void initRoutes(crow::App<>& app);
        void setDatabase(MyFileDatabase* db);

        void index(crow::response& res);
        void retrieveAppointment(const crow::request& req, crow::response& res);
        void deleteAppointment(const crow::request& req, crow::response& res);
        void createAppointment(const crow::request& req, crow::response& res);
        void updateAppointmentTime(const crow::request& req, crow::response& res);
        void updateAppointmentTitle(const crow::request& req, crow::response& res);
        void updateAppointmentLocation(const crow::request& req, crow::response& res);
};

#endif 
