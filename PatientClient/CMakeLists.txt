cmake_minimum_required(VERSION 3.15)

project(PatientClient)

set(INCLUDE_PATHS /opt/homebrew/Cellar/restclient-cpp/0.5.2/include /opt/homebrew/Cellar/jsoncpp/1.9.6/include)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH build/CMakeModules)
set(SOURCE_FILES
    main.cpp
    PatientClient.cpp
)

add_executable(PatientClient 
    ${SOURCE_FILES}
)

target_include_directories(PatientClient PUBLIC 
    ${INCLUDE_PATHS}
    /opt/homebrew/Cellar/restclient-cpp/0.5.2/include
    /opt/homebrew/Cellar/jsoncpp/1.9.6/include
)

target_link_libraries(PatientClient 
    /opt/homebrew/lib/librestclient-cpp.dylib
    /opt/homebrew/lib/libjsoncpp.dylib
)
