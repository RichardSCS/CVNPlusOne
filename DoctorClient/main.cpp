// Copyright 2024 CVNPlusOne

#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <csignal>
#include "restclient-cpp/restclient.h"
#include "DoctorClient.h"

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
    std::cout << "1. Create an appointment\n";
    std::cout << "2. Get all appointment codes\n";
    std::cout << "3. Get details for a specific appointment\n";
    std::cout << "4. Get details for all appointments\n";
    std::cout << "5. Delete an appointment\n";
    std::cout << "6. Exit\n";
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

    DoctorClient client(baseUrl);
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
            case 1: {
                std::string title, location;
                int startTime, endTime;

                std::cout << "Enter appointment title: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, title);

                std::cout << "Enter start time (UNIX timestamp): ";
                while (!(std::cin >> startTime)) {
                    std::cout << "Invalid input. Please enter a valid integer for start time: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                std::cout << "Enter end time (UNIX timestamp): ";
                std::cin >> endTime;

                std::cout << "Enter appointment location: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, location);

                client.createAppointment(title, startTime, endTime, location);
                break;
            }
            case 2:
                client.displayAllAppointmentCodes();
                break;
            case 3:
                std::cout << "Enter appointment code: ";
                std::cin >> apptCode;
                client.displayAppointmentDetail(apptCode);
                break;
            case 4:
                client.displayAllAppointmentDetails();
                break;
            case 5:
                std::cout << "Enter appointment code: ";
                std::cin >> apptCode;
                client.deleteAppointment(apptCode);
                break;
            case 6:
                std::cout << "Exiting program\n";
                return 0;
            default:
                std::cout << "Invalid option. Please try again\n";
                break;
        }
    }

    return 0;
}
