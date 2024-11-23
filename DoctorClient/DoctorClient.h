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
        
        std::vector<std::string> getAppointmentCodes();
        std::string getAppointmentDetails(const std::string& code);
        void displayAllAppointmentCodes();
        void displayAllAppointmentDetails();
        void displayAppointmentDetails();
        void displayAppointmentDetail(const std::string& code);
        std::string deleteAppointment(const std::string& code);
        std::string createAppointment(const std::string& title, int startTime, int endTime, const std::string& location);
        std::string updateAppointmentTitle(const std::string& code, const std::string& title);
        std::string updateAppointmentLocation(const std::string& code, const std::string& location);
        std::string updateAppointmentTime(const std::string& code,int startTime, int endTime);
};

#endif
