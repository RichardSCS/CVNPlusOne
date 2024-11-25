#include <string>
#include <vector>
#ifndef DOCTORCLIENT_H
#define DOCTORCLIENT_H

class DoctorClient {
    private:
        std::string baseUrl;
        std::vector<std::string> createdAppointments;
    public:
        DoctorClient(const std::string& baseUrl);
        
        std::vector<std::string> getAppointmentCodes(const std::string& createdBy);
        std::vector<std::string> getAppointmentCodesByParticipant(const std::string& createdBy, const std::string& participantId);
        std::string getAppointmentDetails(const std::string& code);
        void displayAllAppointmentCodes(const std::string& createdBy);
        void displayAllAppointmentDetails(const std::string& createdBy);
        void displayAppointmentDetailsByParticipant(const std::string& createdBy, const std::string& participantId); 
        void displayAppointmentDetails();
        void displayAppointmentDetail(const std::string& code);
        std::string deleteAppointment(const std::string& code);
        std::string createAppointment(const std::string& title, int startTime, int endTime, const std::string& location, const std::string& participantId, const std::string& createdBy);
        std::string updateAppointmentTitle(const std::string& code, const std::string& title);
        std::string updateAppointmentLocation(const std::string& code, const std::string& location);
        std::string updateAppointmentParticipantId(const std::string& code, const std::string& newParticipant);
        std::string updateAppointmentTime(const std::string& code,int startTime, int endTime);
};

#endif
