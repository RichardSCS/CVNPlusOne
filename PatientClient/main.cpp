// Copyright 2024 CVNPlusOne

#include <iostream>
#include <map>
#include <string>
#include <csignal>
#include "restclient-cpp/restclient.h"
#include "PatientClient.h"

/**
 *  Method to handle proper termination protocols 
 */
/*
void signalHandler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        MyApp::onTermination();
        std::exit(signal);  
    }
}
*/

void showMenu() {
    std::cout << "=================\n";
    std::cout << "Select an option:\n";
    std::cout << "1. Get all appointment codes\n";
    std::cout << "2. Get details for a specific appointment\n";
    std::cout << "3. Get details for all appointments\n";
    std::cout << "4. Exit\n";
}

/**
 *  Sets up the HTTP client and runs the program 
 */
int main(int argc, char* argv[]) {
     std::string baseUrl;

    std::cout << "Enter the base URL (default: http://127.0.0.1:8080): ";
    std::getline(std::cin, baseUrl);

    if (baseUrl.empty()) {
        baseUrl = "http://127.0.0.1:8080";
        std::cout << "Using local base URL http://127.0.0.1:8080\n\n";
    }

    std::string participantId;
    bool isValid = false;

    while (!isValid) {
        std::cout << "Enter your user ID (cannot be empty): ";
        std::getline(std::cin, participantId);

        if (!participantId.empty()) {
            isValid = true;
            std::cout << "User ID set to: " << participantId << "\n\n";
        } else {
            std::cout << "Invalid input. User ID cannot be empty. Please try again.\n";
        }
    }

    PatientClient client(baseUrl);
    int choice;
    std::string apptCode;

    while (true) {
        showMenu();
        std::cout << "Enter your choice: ";

        while (true) {
            std::cin >> choice;
            if (std::cin.fail()) {
                std::cout << "Invalid option, please try again\n";
            
                std::cin.clear();
                // Ignore rest of the input line https://stackoverflow.com/questions/63953373/how-to-ignore-the-rest-of-the-line
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        } 
    
        switch (choice) {
            case 1:
                client.displayAllAppointmentCodes(participantId);
                break;
            case 2:
                std::cout << "Enter appointment code: ";
                std::cin >> apptCode;
                client.displayAppointmentDetail(apptCode);
                break;
            case 3:
                client.displayAllAppointmentDetails(participantId);
                break;
            case 4:
                std::cout << "Exiting program\n";
                return 0;
            default:
                std::cout << "Invalid option. Please try again\n";
                break;
        }
    }

    return 0;
}
