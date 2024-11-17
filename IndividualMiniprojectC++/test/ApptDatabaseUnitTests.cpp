/**
 * Copyright 2024 <Columbia University>
 */

#include <gtest/gtest.h>
#include "ApptDatabase.h" 
#include "MyApp.h"

class ApptDatabaseUnitTests : public ::testing::Test {
protected:
    static ApptDatabase* testApptDatabase;
    static MyFileDatabase* testMyFileDatabase;

    static void SetUpTestSuite() {
        MyApp::run("setup");
        MyApp::onTermination();
        system("cp testfile.bin unittestfile.bin");
        testMyFileDatabase = new MyFileDatabase(0, "unittestfile.bin");
        testApptDatabase = new ApptDatabase("database.txt");
    }

    static void TearDownTestSuite() {
        system("rm unittestfile.bin");
        delete testMyFileDatabase;
        delete testApptDatabase;
    }
};

MyFileDatabase* ApptDatabaseUnitTests::testMyFileDatabase = nullptr;
ApptDatabase* ApptDatabaseUnitTests::testApptDatabase = nullptr;

TEST_F(ApptDatabaseUnitTests, SaveApptToDbTest) {
    std::string apptCode = "DB_TEST_APPT1";
    Appointment* testAppointment = new Appointment(apptCode, "DB Test Appointment 1", 1729681200, 1729681800, "Dentist Office");
    testApptDatabase->saveApptToDatabase(*testAppointment);
    testApptDatabase->loadContentsFromDatabase(testMyFileDatabase);
    std::map<std::string, Appointment> apptMapping = testMyFileDatabase->getAppointmentMapping();
    auto it = apptMapping.find(apptCode);
    ASSERT_NE(it, apptMapping.end());
}

