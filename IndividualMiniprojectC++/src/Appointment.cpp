// Copyright 2024 Jacob Aaronson

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

std::string Appointment::getApptTitle() const
{
    return title;
}

time_t Appointment::getApptStartTime() const
{
    return startTime;
}
        
time_t Appointment::getApptEndTime() const
{
    return endTime;
}
        
std::string Appointment::getApptLocation() const
{
    return location;
}

std::string Appointment::display() const {
    char strt[32], end[32];
    std::strftime(strt, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&startTime)); 
    std::strftime(end, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&endTime)); 
    std::string strtStr = strt;
    std::string endStr = end;
    return "\nTitle: " + title + "; Location: " + location + "; Start Time: " + strtStr + "; End Time: " + endStr;
}

void Appointment::setStartTime(const time_t newStartTime)
{
    startTime = newStartTime;
}

void Appointment::setEndTime(const time_t newEndTime)
{
    endTime = newEndTime;
}

void Appointment::setLocation(const std::string &newLocation)
{
    location = newLocation;
}

void Appointment::addParticipant(const std::string &newParticipant)
{
    participants.insert(newParticipant);
}

void Appointment::removeParticipant(const std::string &participant)
{
    participants.erase(participant);
}

