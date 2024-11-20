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

TEST_F(ApptDatabaseUnitTests, SaveApptAndLoadDbTest) {
    std::string apptCode = "APPT6";
    std::map<std::string, Appointment> apptMapping = testMyFileDatabase->getAppointmentMapping();
    auto it = apptMapping.find(apptCode);
    ASSERT_EQ(it, apptMapping.end());

    Appointment* testAppointment = new Appointment(apptCode, "DB Test Appointment 1", 1729681200, 1729681800, "Dentist Office");
    testApptDatabase->saveApptToDatabase(*testAppointment);
    testApptDatabase->loadContentsFromDatabase(testMyFileDatabase);

    apptMapping = testMyFileDatabase->getAppointmentMapping();
    it = apptMapping.find(apptCode);
    ASSERT_NE(it, apptMapping.end());
}

TEST_F(ApptDatabaseUnitTests, SaveContentsAndLoadDbTest) {
    std::string apptCode = "APPT9";
    std::map<std::string, Appointment> apptMapping = testMyFileDatabase->getAppointmentMapping();
    auto it = apptMapping.find(apptCode);
    ASSERT_EQ(it, apptMapping.end());

    Appointment* testAppointment = new Appointment(apptCode, "DB Test Appointment 2", 1729681200, 1729681800, "Podiatrist Office");
    apptMapping[apptCode] = *testAppointment;
    testApptDatabase->saveContentsToDatabase(apptMapping);

    apptMapping.clear();
    it = apptMapping.find(apptCode);
    ASSERT_EQ(it, apptMapping.end());

    testApptDatabase->loadContentsFromDatabase(testMyFileDatabase);
    apptMapping = testMyFileDatabase->getAppointmentMapping();
    it = apptMapping.find(apptCode);
    ASSERT_NE(it, apptMapping.end());
}

TEST_F(ApptDatabaseUnitTests, DeleteFromDbTest) {
    std::string apptCode = "APPT6";
    testApptDatabase->loadContentsFromDatabase(testMyFileDatabase);
    std::map<std::string, Appointment> apptMapping = testMyFileDatabase->getAppointmentMapping();
    auto it = apptMapping.find(apptCode);
    ASSERT_NE(it, apptMapping.end());

    testApptDatabase->deleteApptFromDatabase(apptCode);
    apptMapping.clear();
    testMyFileDatabase->removeAppointment(apptCode);
    testApptDatabase->loadContentsFromDatabase(testMyFileDatabase);
    apptMapping = testMyFileDatabase->getAppointmentMapping();
    it = apptMapping.find(apptCode);
    ASSERT_EQ(it, apptMapping.end());

    testApptDatabase->wipeDatabase();
}
