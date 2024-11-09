// Copyright 2024 CVNPlusOne

#include <iostream>
#include <map>
#include <string>
#include <csignal>
#include "restclient-cpp/include/restclient-cpp/restclient.h"

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

/**
 *  Sets up the HTTP client and runs the program 
 */
int main(int argc, char* argv[]) {
    std::string mode = argc > 1 ? argv[1] : "run";
    //MyApp::run(mode);

    RestClient::Response r = RestClient::get("http://127.0.0.1:8080/retrieveAppt?apptCode=APPT1");

    return 0;
}
