#include <string>
#include <vector>
#ifndef PATIENTCLIENT_H
#define PATIENTCLIENT_H

class PatientClient {
    private:
        std::string baseUrl;
        std::vector<std::string> createdAppointments;
    public:
        PatientClient(const std::string& baseUrl);
        
        std::vector<std::string> getAppointmentCodes();
        std::string getAppointmentDetails(const std::string& code);
        void displayAllAppointmentCodes();
        void displayAllAppointmentDetails();
        void displayAppointmentDetails();
        void displayAppointmentDetail(const std::string& code);
        std::string deleteAppointment(const std::string& code);
        std::string createAppointment(const std::string& title, int startTime, int endTime, const std::string& location);
};

#endif
