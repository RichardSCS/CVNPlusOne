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
