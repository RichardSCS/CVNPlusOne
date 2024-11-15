This is REST Client for the Patient. The Patient client views and deletes appointments which have been added by the Provider/Doctor. 

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
    In RESTClient/build, ./PatientClient
    

Client files:
-------------
main.cpp is the file to send REST API calls to the Server.
It has been tested for the GET API call:
RestClient::get("http://127.0.0.1:8080/retrieveAppt?apptCode=APPT1")

Examples of other REST API calls can be found here:
https://github.com/mrtazz/restclient-cpp/blob/main/README.md
