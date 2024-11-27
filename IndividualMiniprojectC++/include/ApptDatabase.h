#include "Appointment.h"
#include "MyFileDatabase.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include <map>
#include <string>

#ifndef APPTDATABASE_H
#define APPTDATABASE_H

class ApptDatabase {
    public:
        explicit ApptDatabase(const std::string& filePath);

        void loadContentsFromDatabase(MyFileDatabase* myFileDatabase);
        void saveApptToDatabase(const Appointment& appt);
        void deleteApptFromDatabase(const std::string& apptCode);
        void wipeDatabase();
        void saveContentsToDatabase(const std::map<std::string, Appointment>& mapping);
        int getCodeCount();
        Appointment* getAppointmentFromDatabase(const std::string& apptCode);

    private:
        std::string m_filePath = "";
        std::string dbpw = "";
        int codeCount = 0;
        bool executeQuery(std::string sql_query);

        sql::Driver *m_driver = nullptr;
        sql::Connection *m_connection = nullptr;
};

#endif
