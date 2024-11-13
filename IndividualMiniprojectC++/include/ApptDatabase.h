#include "Appointment.h"
#include "MyFileDatabase.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include <map>
#include <string>

#ifndef APPTDATABASE_H
#define APPTDATABASE_H

class ApptDatabase {
    public:
        ApptDatabase(const std::string& filePath);

        void loadContentsFromDatabase(MyFileDatabase* myFileDatabase);
        void saveApptToDatabase(const Appointment& appt);
        void deleteApptFromDatabase(const std::string& apptCode);
        void saveContentsToDatabase(const std::map<std::string, Appointment>& mapping);

    private:
        std::string m_filePath = "";
        std::string dbpw = "";
        bool executeQuery(std::string sql_query);
};

#endif
