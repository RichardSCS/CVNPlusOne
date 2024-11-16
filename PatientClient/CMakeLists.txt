cmake_minimum_required(VERSION 3.15)

project(PatientClient)

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
    /usr/local/include/restclient-cpp
    /usr/include/jsoncpp
)

target_link_libraries(PatientClient 
    restclient-cpp
    jsoncpp
)
