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
        void setStartTime(const time_t newStartTime);
        void setEndTime(const time_t newEndTime);
        std::string participantId;
        std::string createdBy;
    
    public:
        Appointment(const std::string& code, const std::string& title, time_t startTime, time_t endTime, const std::string &location, const std::string &participantId, const std::string &createdBy);
        Appointment();

        void serialize(std::ostream& out) const;
        void deserialize(std::istream& in);

        const std::string& getApptCode() const;
        const std::string& getApptTitle() const;
        const time_t getApptStartTime() const;
        const time_t getApptEndTime() const;
        const std::string& getApptLocation() const;
        const std::string& getParticipantId() const;
        const std::string& getCreatedBy() const;
        std::string display() const;

        bool setTimes(const time_t newStartTime, const time_t newEndTime);
        void setLocation(const std::string &newLocation);
        void setTitle(const std::string &newTitle);
        void setParticipantId(const std::string &newParticipant);
        void setCreatedBy(const std::string &newCreatedBy);
};

#endif
