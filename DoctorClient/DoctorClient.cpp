#include "DoctorClient.h"
#include "restclient-cpp/restclient.h"
#include <jsoncpp/json/json.h>
#include <iostream>
#include <regex>

DoctorClient::DoctorClient(const std::string& baseUrl) : baseUrl(baseUrl), createdAppointments() {}

std::vector<std::string> DoctorClient::getAppointmentCodes(const std::string& createdBy) {
    RestClient::Response response = RestClient::get(baseUrl + "/listAppts?createdBy=" + createdBy);
    std::vector<std::string> codes;

    if (response.code == 200) {
        std::istringstream stream(response.body);
        std::string line;

        while (std::getline(stream, line)) {
            if (!line.empty()) {
                codes.push_back(line);
            }
        }
    } else {
        std::cerr << "Failed to retrieve appointment codes. HTTP code: " << response.code << "\n";
    }

    return codes;
}

std::vector<std::string> DoctorClient::getAppointmentCodesByParticipant(const std::string& createdBy, const std::string& participantId) {
    RestClient::Response response = RestClient::get(baseUrl + "/listAppts?createdBy=" + createdBy + "&participantId=" + participantId);
    std::vector<std::string> codes;

    if (response.code == 200) {
        std::istringstream stream(response.body);
        std::string line;

        while (std::getline(stream, line)) {
            if (!line.empty()) {
                codes.push_back(line);
            }
        }
    } else {
        std::cerr << "Failed to retrieve appointment codes. HTTP code: " << response.code << "\n";
    }

    return codes;
}

std::string DoctorClient::getAppointmentDetails(const std::string& code) {
    RestClient::Response response = RestClient::get(baseUrl + "/retrieveAppt?apptCode=" + code);
    if (response.code == 200) {
        return response.body;
    } else {
        std::cerr << "Failed to retrieve details for " << code << ". HTTP code: " << response.code << "\n";
        return "Appointment details not found";
    }
}

// Reference https://gist.github.com/arthurafarias/56fec2cd49a32f374c02d1df2b6c350f
std::string encodeURIComponent(std::string decoded) {
    std::ostringstream oss;
    std::regex r("[!'\\(\\)*-.0-9A-Za-z_~]");

    for (char &c : decoded) {
        if (std::regex_match((std::string){c}, r)) {
            oss << c;
        } else {
            oss << "%" << std::uppercase << std::hex << (0xff & c);
        }
    }
    return oss.str();
}

std::string DoctorClient::createAppointment(const std::string& title, int startTime, int endTime, const std::string& location, const std::string& participantId, const std::string& createdBy) {
    std::string encodedTitle = encodeURIComponent(title);
    std::string encodedLocation = encodeURIComponent(location);
    std::string encodedParticipantId = encodeURIComponent(participantId);
    std::string encodedCreatedBy = encodeURIComponent(createdBy);

    std::ostringstream urlBuilder;
    urlBuilder << baseUrl << "/createAppt?"
                << "title=" << encodedTitle
                << "&startTime=" << startTime
                << "&endTime=" << endTime
                << "&location=" << encodedLocation
                << "&participantId=" << encodedParticipantId
                << "&createdBy=" << encodedCreatedBy;

    std::cout << urlBuilder.str() << std::endl;
    RestClient::Response response = RestClient::post(urlBuilder.str(), "application/json", "");

    if (response.code == 201) {
        std::cout << response.body << std::endl;
        std::string apptCode = response.body.substr(response.body.find("APPT"));
        DoctorClient::createdAppointments.push_back(apptCode);
        return apptCode;
    } else {
        std::cerr << "Failed to create appointment. Error: " << response.body << ". HTTP code: " << response.code << std::endl;
        return "Failed to create appointment";
    }
}

void DoctorClient::displayAllAppointmentCodes(const std::string& createdBy) {
    std::vector<std::string> codes = getAppointmentCodes(createdBy);
    if (codes.empty()) {
        std::cout << "No appointment codes found\n";
    } else {
        std::cout << "Available Appointment Codes:\n";
        for (const auto& code : codes) {
            std::cout << code << std::endl;
        }
    }
}

void DoctorClient::displayAllAppointmentDetails(const std::string& createdBy) {
    auto codes = getAppointmentCodes(createdBy);
    for (const auto& code : codes) {
        std::cout << "Details for " << code << ": " << getAppointmentDetails(code) << "\n\n";
    }
}

void DoctorClient::displayAppointmentDetailsByParticipant(const std::string& createdBy, const std::string& participantId) {
    auto codes = getAppointmentCodesByParticipant(createdBy, participantId);
    for (const auto& code : codes) {
        std::cout << "Details for " << code << ": " << getAppointmentDetails(code) << "\n\n";
    }
}

void DoctorClient::displayAppointmentDetail(const std::string& code) {
    std::cout << "Details for " << code << ": " << getAppointmentDetails(code) << "\n\n";
}

std::string DoctorClient::deleteAppointment(const std::string& code) {
    RestClient::Response response = RestClient::del(baseUrl + "/deleteAppt?apptCode=" + code);
    if (response.code == 200) {
        std::cout << "Appointment " << code << " deleted successfully\n";
        return response.body;
    } else {
        std::cerr << "Failed to delete appointment " << code << ". HTTP code: " << response.code << "\n";
        return "Appointment Not Found";
    }
}

std::string DoctorClient::updateAppointmentTitle(const std::string& code, const std::string& title) {
    std::string encodedCode = encodeURIComponent(code);
    std::string encodedTitle = encodeURIComponent(title);

    std::ostringstream urlBuilder;
    urlBuilder << baseUrl << "/updateApptTitle?"
                << "apptCode=" << encodedCode
                << "&apptTitle=" << encodedTitle;

    std::cout << urlBuilder.str() << std::endl;
    RestClient::Response response = RestClient::patch(urlBuilder.str(), "application/json", "");

    if (response.code == 200) {
        std::cout << "Appointment " << code << " title updated successfully\n";
        return response.body;
    } else {
        std::cerr << "Failed to update appointment title " << code << ". HTTP code: " << response.code << "\n";
        return "Appointment Not Found";
    }
}

std::string DoctorClient::updateAppointmentLocation(const std::string& code, const std::string& location) {
    std::string encodedCode = encodeURIComponent(code);
    std::string encodedLocation = encodeURIComponent(location);

    std::ostringstream urlBuilder;
    urlBuilder << baseUrl << "/updateApptLocation?"
                << "apptCode=" << encodedCode
                << "&apptLocation=" << encodedLocation;

    std::cout << urlBuilder.str() << std::endl;
    RestClient::Response response = RestClient::patch(urlBuilder.str(), "application/json", "");

    if (response.code == 200) {
        std::cout << "Appointment " << code << " location updated successfully\n";
        return response.body;
    } else {
        std::cerr << "Failed to update appointment location " << code << ". HTTP code: " << response.code << "\n";
        return "Appointment Not Found";
    }
}

std::string DoctorClient::updateAppointmentParticipantId(const std::string& code, const std::string& newParticipant) {
    std::string encodedCode = encodeURIComponent(code);
    std::string encodedNewParticipant = encodeURIComponent(newParticipant);

    std::ostringstream urlBuilder;
    urlBuilder << baseUrl << "/updateApptParticipantId?"
                << "apptCode=" << encodedCode
                << "&apptParticipantId=" << encodedNewParticipant;

    std::cout << urlBuilder.str() << std::endl;
    RestClient::Response response = RestClient::patch(urlBuilder.str(), "application/json", "");

    if (response.code == 200) {
        std::cout << "Appointment " << code << " location updated successfully\n";
        return response.body;
    } else {
        std::cerr << "Failed to update appointment location " << code << ". HTTP code: " << response.code << "\n";
        return "Appointment Not Found";
    }
}

std::string DoctorClient::updateAppointmentTime(const std::string& code, int startTime, int endTime) {
    std::string encodedCode = encodeURIComponent(code);

    std::ostringstream urlBuilder;
    urlBuilder << baseUrl << "/updateApptTimes?"
                << "apptCode=" << encodedCode
                << "&startTime=" << startTime
                << "&endTime=" << endTime;

    std::cout << urlBuilder.str() << std::endl;
    RestClient::Response response = RestClient::patch(urlBuilder.str(), "application/json", "");

    if (response.code == 200) {
        std::cout << "Appointment " << code << " times updated successfully\n";
        return response.body;
    } else {
        std::cerr << "Failed to update appointment times " << code << ". HTTP code: " << response.code << "\n";
        return "Appointment Not Found";
    }
}

