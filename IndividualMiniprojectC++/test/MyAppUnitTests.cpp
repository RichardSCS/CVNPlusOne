// Copyright 2024 Jacob Aaronson

#include <gtest/gtest.h>
#include "MyApp.h" 

class MyAppUnitTests : public ::testing::Test {
protected:
    static MyApp* testMyApp;

    static void SetUpTestSuite() {
        
    }

    static void TearDownTestSuite() {
        delete testMyApp;
    }
};

MyApp* MyAppUnitTests::testMyApp = nullptr;

TEST_F(MyAppUnitTests, MyAppTest) {
    testMyApp->run(""); 
    std::string display = "For the CHEM department:\nCHEM 1403: \nInstructor: Ruben M Savizky; Location: 309 HAV; Time: 6:10-7:25\nCHEM 1500: \nInstructor: Joseph C Ulichny; Location: 302 HAV; Time: 6:10-9:50\nCHEM 2045: \nInstructor: Luis M Campos; Location: 209 HAV; Time: 1:10-2:25\nCHEM 2444: \nInstructor: Christopher Eckdahl; Location: 309 HAV; Time: 11:40-12:55\nCHEM 2494: \nInstructor: Talha Siddiqui; Location: 202 HAV; Time: 1:10-5:00\nCHEM 3080: \nInstructor: Milan Delor; Location: 209 HAV; Time: 10:10-11:25\nCHEM 4071: \nInstructor: Jonathan S Owen; Location: 320 HAV; Time: 8:40-9:55\nCHEM 4102: \nInstructor: Dalibor Sames; Location: 320 HAV; Time: 10:10-11:25\n\nFor the COMS department:\nCOMS 1004: \nInstructor: Adam Cannon; Location: 417 IAB; Time: 11:40-12:55\nCOMS 3134: \nInstructor: Brian Borowski; Location: 301 URIS; Time: 4:10-5:25\nCOMS 3157: \nInstructor: Jae Lee; Location: 417 IAB; Time: 4:10-5:25\nCOMS 3203: \nInstructor: Ansaf Salleb-Aouissi; Location: 301 URIS; Time: 10:10-11:25\nCOMS 3251: \nInstructor: Tony Dear; Location: 402 CHANDLER; Time: 1:10-3:40\nCOMS 3261: \nInstructor: Josh Alman; Location: 417 IAB; Time: 2:40-3:55\nCOMS 3827: \nInstructor: Daniel Rubenstein; Location: 207 Math; Time: 10:10-11:25\nCOMS 4156: \nInstructor: Gail Kaiser; Location: 501 NWC; Time: 10:10-11:25\n\nFor the ECON department:\nECON 1105: \nInstructor: Waseem Noor; Location: 309 HAV; Time: 2:40-3:55\nECON 2257: \nInstructor: Tamrat Gashaw; Location: 428 PUP; Time: 10:10-11:25\nECON 3211: \nInstructor: Murat Yilmaz; Location: 310 FAY; Time: 4:10-5:25\nECON 3213: \nInstructor: Miles Leahey; Location: 702 HAM; Time: 4:10-5:25\nECON 3412: \nInstructor: Thomas Piskula; Location: 702 HAM; Time: 11:40-12:55\nECON 4415: \nInstructor: Evan D Sadler; Location: 309 HAV; Time: 10:10-11:25\nECON 4710: \nInstructor: Matthieu Gomez; Location: 517 HAM; Time: 8:40-9:55\nECON 4840: \nInstructor: Mark Dean; Location: 142 URIS; Time: 2:40-3:55\n\nFor the IEOR department:\nIEOR 2500: \nInstructor: Uday Menon; Location: 627 MUDD; Time: 11:40-12:55\nIEOR 3404: \nInstructor: Christopher J Dolan; Location: 303 MUDD; Time: 10:10-11:25\nIEOR 3658: \nInstructor: Daniel Lacker; Location: 310 FAY; Time: 10:10-11:25\nIEOR 4102: \nInstructor: Antonius B Dieker; Location: 209 HAM; Time: 10:10-11:25\nIEOR 4106: \nInstructor: Kaizheng Wang; Location: 501 NWC; Time: 10:10-11:25\nIEOR 4405: \nInstructor: Yuri Faenza; Location: 517 HAV; Time: 11:40-12:55\nIEOR 4511: \nInstructor: Michael Robbins; Location: 633 MUDD; Time: 9:00-11:30\nIEOR 4540: \nInstructor: Krzysztof M Choromanski; Location: 633 MUDD; Time: 7:10-9:40\n\nFor the PHYS department:\nPHYS 1001: \nInstructor: Szabolcs Marka; Location: 301 PUP; Time: 2:40-3:55\nPHYS 1221: \nInstructor: James G. Mccann; Location: 301 PUP; Time: 4:10-5:25\nPHYS 1520: \nInstructor: Victor G. Moffat; Location: 630 MUDD; Time: 4:10-5:25\nPHYS 2000: \nInstructor: Frank E. L. Banta; Location: 402 CHANDLER; Time: 1:10-3:40\nPHYS 3801: \nInstructor: Katherine M. McMahon; Location: 603 MUDD; Time: 4:10-5:25\nPHYS 4205: \nInstructor: Michael P. Larkin; Location: 309 HAV; Time: 6:10-9:50\n\n";
    ASSERT_EQ(display, testMyApp->getDatabase()->display());

    MyFileDatabase* emptyMyFileDataBase = new MyFileDatabase(1, "testfile.bin");
    testMyApp->overrideDatabase(emptyMyFileDataBase); 
    ASSERT_EQ("", testMyApp->getDatabase()->display());

    testMyApp->onTermination();
}