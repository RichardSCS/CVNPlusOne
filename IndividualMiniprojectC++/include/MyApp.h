#ifndef MYAPP_H
#define MYAPP_H

#include <string>
#include <map>
#include "MyFileDatabase.h"
#include "ApptDatabase.h"

class MyApp {
    public:
        static void run(const std::string& mode);
        static void onTermination();
        static void overrideDatabase(MyFileDatabase* testData);
        static MyFileDatabase* getDatabase();
        static ApptDatabase* getApptDatabase();

    private:
        static void setupDatabase();
        static void resetDataFile();

        static MyFileDatabase* myFileDatabase;
        static ApptDatabase* apptDatabase;
        static bool saveData;
};

#endif
