// Copyright 2024 Jacob Aaronson

#include "MyFileDatabase.h"
#include <iostream>
#include <fstream>

/**
 * Constructs a MyFileDatabase object and loads up the data structure with
 * the contents of the file.
 *
 * @param flag     used to distinguish mode of database
 * @param filePath the path to the file containing the entries of the database
 */
MyFileDatabase::MyFileDatabase(int flag, const std::string& filePath) : filePath(filePath) {
    Appointment appt1("APPT1", "Doctor Appointment", 1730383200, 1730386800, "Clinic");
    std::map<std::string, Appointment> apptMapping;
    apptMapping["APPT1"] = appt1;
    setApptMapping(apptMapping);
}

void MyFileDatabase::setApptMapping(const std::map<std::string, Appointment>& mapping) {
    appointmentMapping = mapping;
}

std::map<std::string, Appointment> MyFileDatabase::getAppointmentMapping() const {
    return appointmentMapping;
}


bool MyFileDatabase::removeAppointment(const std::string& apptCode) {
    auto appointmentMapping = getAppointmentMapping();

    auto it = appointmentMapping.find(apptCode);

    if (it == appointmentMapping.end()) {
        return false;
    }

    appointmentMapping.erase(it);
    setApptMapping(appointmentMapping);

    return true;
}