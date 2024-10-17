// Copyright 2024 CVNPlusOne

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

/**
 * Saves the contents of the internal data structure to the file. Contents of the file are
 * overwritten with this operation.
 */
void MyFileDatabase::saveContentsToFile() const {
    std::ofstream outFile(filePath, std::ios::binary);
    size_t mapSize = appointmentMapping.size();
    outFile.write(reinterpret_cast<const char*>(&mapSize), sizeof(mapSize));
    for (const auto& it : appointmentMapping) {
        size_t keyLen = it.first.length();
        outFile.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
        outFile.write(it.first.c_str(), keyLen);
        it.second.serialize(outFile);
    }
    outFile.close();
}

/**
 * Deserializes the object from the file and returns the department mapping.
 *
 * @return the deserialized department mapping
 */
void MyFileDatabase::deSerializeObjectFromFile() {
    std::ifstream inFile(filePath, std::ios::binary);
    size_t mapSize;
    inFile.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));
    for (size_t i = 0; i < mapSize; ++i) {
        size_t keyLen;
        inFile.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
        std::string key(keyLen, ' ');
        inFile.read(&key[0], keyLen);
        Appointment appt; 
        appt.deserialize(inFile);
        appointmentMapping[key] = appt;
    }
    inFile.close();
}

/**
 * Returns a string representation of the database.
 *
 * @return a string representation of the database
 */
std::string MyFileDatabase::display() const {
    std::string result;
    for (const auto& it : appointmentMapping) {
        result += "For the " + it.first + " department:\n" + it.second.display() + "\n";
    }
    return result;
}
