/**
 * Copyright 2024 <Columbia University>
 */

#include <gtest/gtest.h>
#include "MyFileDatabase.h" 
#include "MyApp.h"

class MyFileDatabaseUnitTests : public ::testing::Test {
protected:
    static MyFileDatabase* testMyFileDatabase;

    static void SetUpTestSuite() {
        MyApp::run("setup");
        MyApp::onTermination();
        system("cp testfile.bin unittestfile.bin");
        testMyFileDatabase = new MyFileDatabase(0, "unittestfile.bin");
    }

    static void TearDownTestSuite() {
        system("rm unittestfile.bin");
        delete testMyFileDatabase;
    }
};

MyFileDatabase* MyFileDatabaseUnitTests::testMyFileDatabase = nullptr;

TEST_F(MyFileDatabaseUnitTests, SaveContentsToFileTest) {
    testMyFileDatabase->saveContentsToFile();
    int retCode = system("diff unittestfile.bin testfile.bin");
    EXPECT_EQ(0, retCode);
}

TEST_F(MyFileDatabaseUnitTests, ToStringTest) {
   std::string expectedResult = "For the APPT1 appointment:\n\nTitle: Doctor Appointment; Location: Clinic; Start Time: Thu, 2024-10-31 07:00; End Time: Thu, 2024-10-31 08:00\nFor the APPT2 appointment:\n\nTitle: Diagnostic Test; Location: Hospital; Start Time: Thu, 2024-10-31 07:05; End Time: Thu, 2024-10-31 08:16\nFor the APPT3 appointment:\n\nTitle: Prescription Refill; Location: Pharmacy; Start Time: Thu, 2024-10-31 07:08; End Time: Thu, 2024-10-31 08:50\nFor the APPT4 appointment:\n\nTitle: Meeting; Location: Pharmacy; Start Time: Thu, 2024-10-31 07:00; End Time: Thu, 2024-10-31 07:10\n";
    ASSERT_EQ(expectedResult, testMyFileDatabase->display());
}
