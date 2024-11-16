This is REST Client for the Doctor. The Doctor client creates, updates, views and deletes appointments.

It uses the restclient-cpp library for REST API calls to the Server.

Install the required libraries:
    librestclient-cpp:
        In Macos:
        brew tap mrtazz/oss
        brew install restclient-cpp

        In Ubuntu:
        https://packagecloud.io/mrtazz/restclient-cpp
    jsoncpp:
        In Macos:
        brew install jsoncpp

        In Ubuntu:
        sudo apt install libjsoncpp-dev

Build:
    cd build
    cmake ..
    make

Run client:
    Have server app running and start client 
    In RESTClient/build, ./DoctorClient
    

Client files:
-------------
main.cpp 
DoctorClient.cpp
DoctorClient.h

Citations:
----------
1. REST client for C++:
       https://github.com/mrtazz/restclient-cpp/blob/main/README.md
