cmake_minimum_required(VERSION 3.15)

project(DoctorClient)

set(INCLUDE_PATHS /opt/homebrew/Cellar/restclient-cpp/0.5.2/include /opt/homebrew/Cellar/jsoncpp/1.9.6/include)
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
    ${INCLUDE_PATHS}
    /opt/homebrew/Cellar/restclient-cpp/0.5.2/include
    /opt/homebrew/Cellar/jsoncpp/1.9.6/include
)

target_link_libraries(DoctorClient 
    /opt/homebrew/lib/librestclient-cpp.dylib
    /opt/homebrew/lib/libjsoncpp.dylib
)
