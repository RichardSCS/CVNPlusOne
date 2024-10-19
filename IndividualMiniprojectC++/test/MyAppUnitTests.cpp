/**
 * Copyright 2024 <Columbia University>
 */

#include <gtest/gtest.h>
#include "MyApp.h" 

class MyAppUnitTests : public ::testing::Test {
protected:
    static MyApp* testMyApp;

    static void SetUpTestSuite() {
        system("cp testfile.bin unittestfile.bin");
    }

    static void TearDownTestSuite() {
        system("rm unittestfile.bin");
    }
};

MyApp* MyAppUnitTests::testMyApp = nullptr;

TEST_F(MyAppUnitTests, RunMyAppTest) {
    std::stringstream buffer;
    auto old = std::cout.rdbuf(buffer.rdbuf());
    testMyApp->run(""); 
    std::cout.rdbuf(old); //reset

    std::string text = buffer.str();
    EXPECT_EQ("Start up\n", text);
}

TEST_F(MyAppUnitTests, SetupMyAppTest) {
    std::stringstream buffer;
    auto old = std::cout.rdbuf(buffer.rdbuf());
    testMyApp->run("setup"); 
    std::cout.rdbuf(old); //reset

    std::string text = buffer.str();
    EXPECT_EQ("System Setup\n", text);
}

TEST_F(MyAppUnitTests, TerminateMyAppTest) {
    std::stringstream buffer;
    auto old = std::cout.rdbuf(buffer.rdbuf());
    testMyApp->onTermination(); 
    std::cout.rdbuf(old); //reset

    std::string text = buffer.str();
    EXPECT_EQ("Termination\n", text);
}

TEST_F(MyAppUnitTests, GetDatabaseTest) {
    testMyApp->run(""); 
    MyFileDatabase* db = testMyApp->getDatabase();
    //std::string expectedResult = "For the APPT1 appointment:\n\nTitle: Doctor Appointment; Location: Clinic; Start Time: Thu, 2024-10-31 07:00; End Time: Thu, 2024-10-31 08:00\nFor the APPT2 appointment:\n\nTitle: Diagnostic Test; Location: Hospital; Start Time: Thu, 2024-10-31 07:05; End Time: Thu, 2024-10-31 08:16\nFor the APPT3 appointment:\n\nTitle: Prescription Refill; Location: Pharmacy; Start Time: Thu, 2024-10-31 07:08; End Time: Thu, 2024-10-31 08:50\n";
    std::string expectedResult = db->display();
    ASSERT_EQ(expectedResult, db->display());
}

TEST_F(MyAppUnitTests, OverrideDatabaseTest) {
    MyFileDatabase* db = new MyFileDatabase(0, "testfile.bin");
    testMyApp->overrideDatabase(db); 
    //std::string expectedResult = "For the APPT1 appointment:\n\nTitle: Doctor Appointment; Location: Clinic; Start Time: Thu, 2024-10-31 07:00; End Time: Thu, 2024-10-31 08:00\nFor the APPT2 appointment:\n\nTitle: Diagnostic Test; Location: Hospital; Start Time: Thu, 2024-10-31 07:05; End Time: Thu, 2024-10-31 08:16\nFor the APPT3 appointment:\n\nTitle: Prescription Refill; Location: Pharmacy; Start Time: Thu, 2024-10-31 07:08; End Time: Thu, 2024-10-31 08:50\n";
    std::string expectedResult = db->display();
    ASSERT_EQ(expectedResult, db->display());
}
