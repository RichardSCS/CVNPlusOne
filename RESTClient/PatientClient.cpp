#include "PatientClient.h"
#include "restclient-cpp/restclient.h"
#include <json/json.h>
#include <iostream>

PatientClient::PatientClient(const std::string& baseUrl) : baseUrl(baseUrl) {}

std::vector<std::string> PatientClient::getAppointmentCodes() {
    RestClient::Response response = RestClient::get(baseUrl + "/listAppts");
    std::vector<std::string> codes;

    if (response.code == 200) {
        Json::Value jsonData;
        Json::Reader jsonReader;
        
        if (jsonReader.parse(response.body, jsonData)) {
            if (jsonData.isArray()) {
                for (const auto& item : jsonData) {
                    codes.push_back(item.asString());
                }
            } else {
                std::cerr << "Unexpected JSON format: Expected an array\n";
            }
        } else {
            std::cerr << "Failed to parse JSON response\n";
        }
    } else {
        std::cerr << "Failed to retrieve appointment codes. HTTP code: " << response.code << "\n";
    }

    return codes;
}

std::string PatientClient::getAppointmentDetails(const std::string& code) {
    RestClient::Response response = RestClient::get(baseUrl + "/retrieveAppt?apptCode=" + code);
    if (response.code == 200) {
        return response.body;
    } else {
        std::cerr << "Failed to retrieve details for " << code << ". HTTP code: " << response.code << "\n";
        return "Appointment details not found";
    }
}

void PatientClient::displayAllAppointmentCodes() {
    std::vector<std::string> codes = getAppointmentCodes();
    if (codes.empty()) {
        std::cout << "No appointment codes found\n";
    } else {
        std::cout << "Available Appointment Codes:\n";
        for (const auto& code : codes) {
            std::cout << code << std::endl;
        }
    }
}

void PatientClient::displayAllAppointmentDetails() {
    auto codes = getAppointmentCodes();
    for (const auto& code : codes) {
        std::cout << "Details for " << code << ": " << getAppointmentDetails(code) << "\n\n";
    }
}

void PatientClient::displayAppointmentDetail(const std::string& code) {
    std::cout << "Details for " << code << ": " << getAppointmentDetails(code) << "\n\n";
}

std::string PatientClient::deleteAppointment(const std::string& code) {
    RestClient::Response response = RestClient::get(baseUrl + "/deleteAppt?apptCode=" + code);
    if (response.code == 200) {
        return response.body;
    } else {
        std::cerr << "Failed to delete appoitment " << code << ". HTTP code: " << response.code << "\n";
        return "Appointment Not Found";
    }
}

