#include <string>
#include <set>
#ifndef APPOINTMENT_H
#define APPOINTMENT_H

class Appointment {
    private:
        std::string code;
        std::string title;
        time_t startTime;
        time_t endTime;
        std::string location;
        std::set<std::string> participants;
    
    public:
        Appointment(std::string code, std::string title, time_t startTime, time_t endTime, const std::string &location);
        Appointment();

        std::string getApptCode() const;
        std::string getApptTitle() const;
        time_t getApptStartTime() const;
        time_t getApptEndTime() const;
        std::string getApptLocation() const;
        std::string display() const;

        void setStartTime(const time_t newStartTime);
        void setEndTime(const time_t newEndTime);
        void setLocation(const std::string &newLocation);
        void addParticipant(const std::string &newParticipant);
        void removeParticipant(const std::string &participant);
};

#endif