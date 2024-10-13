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
    std::string expectedResult = "\nTitle: Test Appointment 1; Location: Dentist Office; Start Time: Wed, 2024-10-23 07:00; End Time: Wed, 2024-10-23 07:10";
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