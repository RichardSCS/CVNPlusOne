// Copyright 2024 CVNPlusOne

#include <gtest/gtest.h>
#include "Appointment.h" 

class AppointmentUnitTests : public ::testing::Test {
protected:
    static Appointment* testAppointment;

    static void SetUpTestSuite() {
        testAppointment = new Appointment("TEST_APPT1", "Test Appointment 1", 1729681200, 1729681800, "Dentist Office");
    }

    static void TearDownTestSuite() {
        delete testAppointment;
    }
};

Appointment* AppointmentUnitTests::testAppointment = nullptr;

TEST_F(AppointmentUnitTests, ToStringTest) {
    char strt[32], end[32];
    std::time_t apptStartTime = testAppointment->getApptStartTime();
    std::time_t apptEndTime = testAppointment->getApptEndTime();
    std::strftime(strt, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&apptStartTime));
    std::strftime(end, 32, "%a, %Y-%m-%d %H:%M", std::localtime(&apptEndTime));
    std::string strtStr = strt;
    std::string endStr = end;
    std::string expectedResult = "\nTitle: Test Appointment 1; Location: Dentist Office; Start Time: " + strtStr + "; End Time: " + endStr;
    ASSERT_EQ(expectedResult, testAppointment->display());
}

TEST_F(AppointmentUnitTests, UpdateTitleTest) {
    ASSERT_EQ("Test Appointment 1", testAppointment->getApptTitle());
    testAppointment->setTitle("Dentist Visit");
    ASSERT_EQ("Dentist Visit", testAppointment->getApptTitle());
}

TEST_F(AppointmentUnitTests, UpdateLocationTest) {
    ASSERT_EQ("Dentist Office", testAppointment->getApptLocation());
    testAppointment->setLocation("Doctor Office");
    ASSERT_EQ("Doctor Office", testAppointment->getApptLocation());
}

TEST_F(AppointmentUnitTests, UpdateTimeTest) {
    ASSERT_EQ(1729681200, testAppointment->getApptStartTime());
    ASSERT_EQ(1729681800, testAppointment->getApptEndTime());
    testAppointment->setTimes(1729681900, 1729682500);
    ASSERT_EQ(1729681900, testAppointment->getApptStartTime());
    ASSERT_EQ(1729682500, testAppointment->getApptEndTime());
}

TEST_F(AppointmentUnitTests, UpdateTimeTestFail) {
    ASSERT_EQ(1729681900, testAppointment->getApptStartTime());
    ASSERT_EQ(1729682500, testAppointment->getApptEndTime());
    testAppointment->setTimes(1729683900, 1729682500);
    ASSERT_EQ(1729681900, testAppointment->getApptStartTime());
    ASSERT_EQ(1729682500, testAppointment->getApptEndTime());
}