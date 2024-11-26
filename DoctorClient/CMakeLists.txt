cmake_minimum_required(VERSION 3.15)

project(DoctorClient)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH build/CMakeModules)
set(SOURCE_FILES
    main.cpp
    DoctorClient.cpp
)

add_executable(DoctorClient 
    ${SOURCE_FILES}
)

target_include_directories(DoctorClient PUBLIC 
    /usr/local/include/restclient-cpp
    /usr/include/jsoncpp
)

target_link_libraries(DoctorClient 
    restclient-cpp
    jsoncpp
)
