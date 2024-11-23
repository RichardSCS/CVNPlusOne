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
        try {
            m_driver = get_driver_instance();
            m_connection = m_driver->connect("tcp://127.0.0.1:3306", "root", dbpw);
            m_connection->setSchema("ase");
        } catch (sql::SQLException &e) {
            std::cout << "Failed to connect to database!" << std::endl;
            std::cerr << "Error: " << e.what() << std::endl;
            std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        }
    } else {
        std::cerr << "Error opening database info file!" << std::endl;
    }
}

void ApptDatabase::saveApptToDatabase(const Appointment& appt) {
    if (!m_connection || !m_connection->isValid()) {
        return;
    }

    try {
        std::string query = "REPLACE INTO appointment (id, title, location, participantId, createdBy, start_time, end_time) VALUES (?, ?, ?, ?, ? ";
        query += "FROM_UNIXTIME(" + std::to_string(appt.getApptStartTime()) + "), ";
        query += "FROM_UNIXTIME(" + std::to_string(appt.getApptEndTime()) + ") );";

        sql::PreparedStatement  *prep_stmt;
        prep_stmt = m_connection->prepareStatement(query);
        prep_stmt->setString(1, appt.getApptCode());
        prep_stmt->setString(2, appt.getApptTitle());
        prep_stmt->setString(3, appt.getApptLocation());
        prep_stmt->setString(4, appt.getParticipantId());
        prep_stmt->setString(5, appt.getCreatedBy());
        prep_stmt->execute();
        //std::cout << "Saving Appt [" << appt.getApptCode() << "] to database." << std::endl;
        delete prep_stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }
}

void ApptDatabase::saveContentsToDatabase(const std::map<std::string, Appointment>& mapping) {
    for (const auto& appt : mapping) {
        saveApptToDatabase(appt.second);
    }
}

void ApptDatabase::deleteApptFromDatabase(const std::string& apptCode) {
    if (!m_connection || !m_connection->isValid()) {
        return;
    }
    try {
        std::string query = "DELETE FROM appointment WHERE id = ?";
        sql::PreparedStatement *prep_stmt;
        prep_stmt = m_connection->prepareStatement(query);
        prep_stmt->setString(1, apptCode);
        prep_stmt->execute();
        //std::cout << "Deleting Appt [" << apptCode << "] from database." << std::endl;
        delete prep_stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }
}

void ApptDatabase::wipeDatabase() {
    if (!m_connection || !m_connection->isValid()) {
        return;
    }
    try {
        std::string query = "DELETE FROM appointment;";
        sql::PreparedStatement *prep_stmt;
        prep_stmt = m_connection->prepareStatement(query);
        prep_stmt->execute();
        delete prep_stmt;
    } catch (sql::SQLException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }
}

void ApptDatabase::loadContentsFromDatabase(MyFileDatabase* myFileDatabase) {
    if (!m_connection || !m_connection->isValid()) {
        return;
    }
    std::string query = "SELECT id, title, UNIX_TIMESTAMP(start_time) AS start_time, UNIX_TIMESTAMP(end_time) AS end_time, location, participantId, createdBy FROM appointment;";
    try {
        sql::PreparedStatement *prep_stmt;
        prep_stmt = m_connection->prepareStatement(query);
        sql::ResultSet *result = prep_stmt->executeQuery();

        auto appointmentMapping = myFileDatabase->getAppointmentMapping();
        while (result->next()) {
            std::string id = result->getString("id");
            std::string title = result->getString("title");
            std::string start_time = result->getString("start_time");
            std::string end_time = result->getString("end_time");
            std::string location = result->getString("location");
            std::string participantId = result->getString("participantId");
            std::string createdBy= result->getString("createdBy");

            Appointment appt(id, title, std::stoi(start_time), std::stoi(end_time), location, participantId, createdBy);
            appointmentMapping[id] = appt;
            //std::cout << "Loading Appt [" << id << "] from database" << std::endl;
            myFileDatabase->setApptMapping(appointmentMapping);
            std::string countStr = id.substr(4); 
            int count = std::stoi(countStr);
            if (count > codeCount) {
                codeCount = count;
            }
        }
        delete prep_stmt;
        delete result;
    } catch (sql::SQLException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
    }
}

int ApptDatabase::getCodeCount() {
    return codeCount;
}
