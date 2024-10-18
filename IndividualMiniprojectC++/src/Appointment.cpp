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
 */
Appointment::Appointment(std::string code, std::string title, time_t startTime, time_t endTime, const std::string &location)
    : code(code), title(title), startTime(startTime), endTime(endTime), location(location) {}

/**
 * Constructs a default Course object with the default parameters.
 *
 */
Appointment::Appointment() : code(""), title(""), startTime(0), endTime(0), location("") {}

const std::string& Appointment::getApptTitle() const {
    return title;
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

void Appointment::addParticipant(const std::string &newParticipant) {
    participants.insert(newParticipant);
}

void Appointment::removeParticipant(const std::string &participant) {
    participants.erase(participant);
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
}
