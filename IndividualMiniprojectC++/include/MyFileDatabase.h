#include "Appointment.h"
#include <map>
#include <string>

#ifndef MYFILEDATABASE_H
#define MYFILEDATABASE_H

class MyFileDatabase {
    public:
        MyFileDatabase(int flag, const std::string& filePath);

        void setApptMapping(const std::map<std::string, Appointment>& mapping);
        
        std::map<std::string, Appointment> getAppointmentMapping() const;
        std::string display() const;

    private:
        std::string filePath;

        std::map<std::string, Appointment> appointmentMapping;
};

#endif