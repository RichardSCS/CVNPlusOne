// Copyright 2024 CVNPlusOne

#include "ApptDatabase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

/**
 * Constructs an ApptDatabase object 
 *
 * @param filePath the path to the file containing the password of the database
 */
ApptDatabase::ApptDatabase(const std::string& filePath) : m_filePath(filePath) {
    std::ifstream file(m_filePath);
    std::string line;
    if (file.is_open()) {
        std::getline(file, line);
        file.close();
        dbpw = line;
    } else {
        std::cerr << "Error opening database info file!" << std::endl;
    }
}

bool ApptDatabase::executeQuery(std::string sql_query) {
    try {
        sql::Driver *driver = get_driver_instance();
        sql::Connection *connection = driver->connect("tcp://127.0.0.1:3306", "root", dbpw);
        connection->setSchema("ase");
        sql::Statement *stmt = connection->createStatement();
        sql::ResultSet *res = stmt->executeQuery(sql_query);
        delete stmt;
        delete connection;
    } catch (sql::SQLException &e) {
        // std::cerr << "Error: " << e.what() << std::endl;
        // std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        // std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        return false;
    }
    return true;
}

void ApptDatabase::saveApptToDatabase(const Appointment& appt) {
    std::string query = "REPLACE INTO appointment (id, title, location, start_time, end_time) VALUES ('";
    query += appt.getApptCode() + "', '";
    query += appt.getApptTitle() + "', '";
    query += appt.getApptLocation() + "', ";
    query += "FROM_UNIXTIME(" + std::to_string(appt.getApptStartTime()) + "), ";
    query += "FROM_UNIXTIME(" + std::to_string(appt.getApptEndTime()) + ") );";
    executeQuery(query);
}

void ApptDatabase::saveContentsToDatabase(const std::map<std::string, Appointment>& mapping) {
    for (const auto& appt : mapping) {
        saveApptToDatabase(appt.second);
    }
}

void ApptDatabase::deleteApptFromDatabase(const std::string& apptCode) {
    std::string query = "DELETE FROM appointment WHERE id = '";
    query += apptCode;
    query += "';";
    executeQuery(query);
}

void ApptDatabase::wipeDatabase() {
    std::string query = "DELETE FROM appointment;";
    executeQuery(query);
}

void ApptDatabase::loadContentsFromDatabase(MyFileDatabase* myFileDatabase) {
    std::string query = "SELECT id, title, UNIX_TIMESTAMP(start_time) AS start_time, UNIX_TIMESTAMP(end_time) AS end_time, location FROM appointment;";

    try {
        sql::Driver *driver = get_driver_instance();
        sql::Connection *connection = driver->connect("tcp://127.0.0.1:3306", "root", dbpw);
        connection->setSchema("ase");
        sql::Statement *stmt = connection->createStatement();
        sql::ResultSet *result = stmt->executeQuery(query);
        auto appointmentMapping = myFileDatabase->getAppointmentMapping();
        while (result->next()) {
            std::string id = result->getString("id");
            std::string title = result->getString("title");
            std::string start_time = result->getString("start_time");
            std::string end_time = result->getString("end_time");
            std::string location = result->getString("location");

            Appointment appt(id, title, std::stoi(start_time), std::stoi(end_time), location);
            appointmentMapping[id] = appt;
            //std::cout << "Loading Appt [" << id << "] from database" << std::endl;
            myFileDatabase->setApptMapping(appointmentMapping);
            std::string countStr = id.substr(4); 
            int count = std::stoi(countStr);
            if (count > codeCount) {
                codeCount = count;
            }
        }
        delete stmt;
        delete connection;
        delete result;
    } catch (sql::SQLException &e) {
        // std::cerr << "Error: " << e.what() << std::endl;
        // std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        // std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }
}

int ApptDatabase::getCodeCount() {
    return codeCount;
}
