/**
 * Copyright 2024 <Columbia University>
 */

#include <gtest/gtest.h>
#include "MyFileDatabase.h" 

class MyFileDatabaseUnitTests : public ::testing::Test {
protected:
    static MyFileDatabase* testMyFileDatabase;

    static void SetUpTestSuite() {
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

/*
TEST_F(MyFileDatabaseUnitTests, ToStringTest) {
    ASSERT_EQ(expectedResult, testMyFileDatabase->display());
}
*/
