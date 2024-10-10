#include "Department.h"
#include "Appointment.h"
#include <map>
#include <string>

#ifndef MYFILEDATABASE_H
#define MYFILEDATABASE_H

class MyFileDatabase {
    public:
        MyFileDatabase(int flag, const std::string& filePath);

        void setMapping(const std::map<std::string, Department>& mapping);
        void setApptMapping(const std::map<std::string, Appointment>& mapping);
        void saveContentsToFile() const;
        void deSerializeObjectFromFile();
        
        std::map<std::string, Department> getDepartmentMapping() const;
        std::map<std::string, Appointment> getAppointmentMapping() const;
        std::string display() const;

    private:
        std::map<std::string, Department> departmentMapping;
        std::string filePath;

        std::map<std::string, Appointment> appointmentMapping;
};

#endif