// Copyright 2024 CVNPlusOne

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
}

void MyApp::onTermination() {
    std::cout << "Termination" << std::endl;
    if (saveData && myFileDatabase) {
        myFileDatabase->saveContentsToFile();
    }

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
    const time_t times[] = {1730383200, 1730386800, 1730383500, 1730387800, 1730383700, 1730389800};
    const std::string types[] = {"Doctor Appointment", "Diagnostic Test", "Prescription Refill"};
    const std::string locations[] = {"Clinic", "Hospital", "Pharmacy"};

    Appointment appt1("APPT1", types[0], times[0], times[1], locations[0]);

    Appointment appt2("APPT2", types[1], times[2], times[3], locations[1]);

    Appointment appt3("APPT3", types[2], times[4], times[5], locations[2]);

    // Setup mapping
    std::map<std::string, Appointment> apptMapping;
    apptMapping["APPT1"] = appt1;
    apptMapping["APPT2"] = appt2;
    apptMapping["APPT3"] = appt3;

    myFileDatabase->setApptMapping(apptMapping);    
}
