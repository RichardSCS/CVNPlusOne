#include "Appointment.h"
#include <map>
#include <string>

#ifndef MYFILEDATABASE_H
#define MYFILEDATABASE_H

class MyFileDatabase {
    public:
        MyFileDatabase(int flag, const std::string& filePath);

        void setApptMapping(const std::map<std::string, Appointment>& mapping);
        void saveContentsToFile() const;
        void deSerializeObjectFromFile();
        
        std::map<std::string, Appointment> getAppointmentMapping() const;
        std::string display() const;
        bool removeAppointment(const std::string& apptCode);

    private:
        std::string m_filePath;

        std::map<std::string, Appointment> m_appointmentMapping;
};

#endif
