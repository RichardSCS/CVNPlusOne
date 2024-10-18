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
        void setStartTime(const time_t newStartTime);
        void setEndTime(const time_t newEndTime);
    
    public:
        Appointment(std::string code, std::string title, time_t startTime, time_t endTime, const std::string &location);
        Appointment();

        void serialize(std::ostream& out) const;
        void deserialize(std::istream& in);

        const std::string& getApptCode() const;
        const std::string& getApptTitle() const;
        const time_t getApptStartTime() const;
        const time_t getApptEndTime() const;
        const std::string& getApptLocation() const;
        std::string display() const;

        bool setTimes(const time_t newStartTime, const time_t newEndTime);
        void setLocation(const std::string &newLocation);
        void setTitle(const std::string &newTitle);
        void addParticipant(const std::string &newParticipant);
        void removeParticipant(const std::string &participant);
};

#endif
