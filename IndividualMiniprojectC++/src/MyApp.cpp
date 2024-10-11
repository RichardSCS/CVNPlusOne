// Copyright 2024 Jacob Aaronson

#include "MyApp.h"
#include "Appointment.h"
#include <iostream>

MyFileDatabase* MyApp::myFileDatabase = nullptr;
bool MyApp::saveData = false;

void MyApp::run(const std::string& mode) {
    saveData = true;
    if (mode == "setup") {
        setupDatabase();
        std::cout << "System Setup" << std::endl;
        return;
    }
    myFileDatabase = new MyFileDatabase(0, "testfile.bin");
    std::cout << "Start up" << std::endl;


    // Appointment appt1("APPT1", "Doctor Appointment", 1730383200, 1730386800, "Clinic");
    // std::map<std::string, Appointment> apptMapping;
    // apptMapping["APPT1"] = appt1;
    // myFileDatabase->setApptMapping(apptMapping);
}

void MyApp::onTermination() {
    std::cout << "Termination" << std::endl;

    delete myFileDatabase;
    myFileDatabase = nullptr;
}

void MyApp::overrideDatabase(MyFileDatabase* testData) {
    delete myFileDatabase;
    myFileDatabase = testData;
    saveData = false;
}

MyFileDatabase *MyApp::getDatabase() {
    return myFileDatabase;
}

void MyApp::setupDatabase() {
    myFileDatabase = new MyFileDatabase(1, "testfile.bin");
    resetDataFile();
}

void MyApp::resetDataFile() {
    
}
