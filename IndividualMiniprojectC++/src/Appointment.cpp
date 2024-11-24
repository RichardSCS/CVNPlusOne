// Copyright 2024 CVNPlusOne

#include "Appointment.h"
#include <iostream>
#include <string>
#include <ctime>


/**
 * Constructs a new Appointment object with the given parameters.
 *
 * @param title         The title of the appointment.
 * @param startTime     The start time of the appointment.
 * @param endTime       The end time of the appointment.
 * @param location      The location of the appointment.
 * @param participantId     Patient of the appointment.
 * @param createdBy      Doctor of the appointment.
 */

Appointment::Appointment(const std::string &code, const std::string &title, time_t startTime, time_t endTime, const std::string &location, const std::string &participantId, const std::string &createdBy)
    : code(code), title(title), startTime(startTime), endTime(endTime), location(location), participantId(participantId), createdBy(createdBy) {}

/**
 * Constructs a default Course object with the default parameters.
 *
 */
Appointment::Appointment() : code(""), title(""), startTime(0), endTime(0), location(""), participantId(""), createdBy("") {}

const std::string& Appointment::getApptTitle() const {
    return title;
}

const std::string& Appointment::getApptCode() const {
    return code;
}

const time_t Appointment::getApptStartTime() const {
    return startTime;
}
       
const time_t Appointment::getApptEndTime() const {
    return endTime;
}

const std::string& Appointment::getApptLocation() const {
    return location;
}

const std::string& Appointment::getParticipantId() const {
    return participantId;
}

const std::string& Appointment::getCreatedBy() const {
    return createdBy;
}

std::string Appointment::display() const {
    char strt[32], end[32];
    std::strftime(strt, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&startTime));
    std::strftime(end, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&endTime));
    std::string strtStr = strt;
    std::string endStr = end;
    return "\nTitle: " + title + "; Location: " + location + "; Start Time: "
            + strtStr + "; End Time: " + endStr;
}

bool Appointment::setTimes(const time_t newStartTime, const time_t newEndTime) {
    if (newStartTime < newEndTime) {
        setStartTime(newStartTime);
        setEndTime(newEndTime);
        return true;
    }
    return false;
}

void Appointment::setStartTime(const time_t newStartTime) {
    startTime = newStartTime;
}

void Appointment::setEndTime(const time_t newEndTime) {
    endTime = newEndTime;
}

void Appointment::setLocation(const std::string &newLocation) {
    location = newLocation;
}

void Appointment::setTitle(const std::string &newTitle) {
    title = newTitle;
}

void Appointment::setParticipantId(const std::string &newParticipant) {
    participantId = newParticipant;
}

void Appointment::setCreatedBy(const std::string &newCreatedBy) {
    createdBy = newCreatedBy;
}

void Appointment::serialize(std::ostream& out) const {
    size_t codeLen = code.length();
    out.write(reinterpret_cast<const char*>(&codeLen), sizeof(codeLen));
    out.write(code.c_str(), codeLen);

    size_t titleLen = title.length();
    out.write(reinterpret_cast<const char*>(&titleLen), sizeof(titleLen));
    out.write(title.c_str(), titleLen);

    out.write(reinterpret_cast<const char*>(&startTime), sizeof(startTime));
    out.write(reinterpret_cast<const char*>(&endTime), sizeof(endTime));

    size_t locationLen = location.length();
    out.write(reinterpret_cast<const char*>(&locationLen), sizeof(locationLen));
    out.write(location.c_str(), locationLen);

    size_t patientIdLen = participantId.length();
    out.write(reinterpret_cast<const char*>(&patientIdLen), sizeof(patientIdLen));
    out.write(participantId.c_str(), patientIdLen);

    size_t doctorIdLen = createdBy.length();
    out.write(reinterpret_cast<const char*>(&doctorIdLen), sizeof(doctorIdLen));
    out.write(createdBy.c_str(), doctorIdLen);
}

void Appointment::deserialize(std::istream& in) {
    size_t codeLen;
    in.read(reinterpret_cast<char*>(&codeLen), sizeof(codeLen));
    code.resize(codeLen);
    in.read(&code[0], codeLen);

    size_t titleLen;
    in.read(reinterpret_cast<char*>(&titleLen), sizeof(titleLen));
    title.resize(titleLen);
    in.read(&title[0], titleLen);

    in.read(reinterpret_cast<char*>(&startTime), sizeof(startTime));
    in.read(reinterpret_cast<char*>(&endTime), sizeof(endTime));

    size_t locationLen;
    in.read(reinterpret_cast<char*>(&locationLen), sizeof(locationLen));
    location.resize(locationLen);
    in.read(&location[0], locationLen);

    size_t patientIdLen;
    in.read(reinterpret_cast<char*>(&patientIdLen), sizeof(patientIdLen));
    participantId.resize(patientIdLen);
    in.read(&participantId[0], patientIdLen);

    size_t doctorIdLen;
    in.read(reinterpret_cast<char*>(&doctorIdLen), sizeof(doctorIdLen));
    createdBy.resize(doctorIdLen);
    in.read(&createdBy[0], doctorIdLen);
}
