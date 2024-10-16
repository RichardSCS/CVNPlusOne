#ifndef ROUTECONTROLLER_H
#define ROUTECONTROLLER_H

#include "crow.h"
#include "Globals.h"
#include "MyFileDatabase.h"

class RouteController {
    private:
        MyFileDatabase* myFileDatabase;

    public:
        void initRoutes(crow::App<>& app);
        void setDatabase(MyFileDatabase* db);

        void index(crow::response& res);
        void retrieveAppointment(const crow::request& req, crow::response& res);
};

#endif 
