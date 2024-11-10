This is a basic REST Client. 

It uses the restclient-cpp library for REST API calls to the Server.

Install the librestclient-cpp:
In Macos:
brew tap mrtazz/oss
brew install restclient-cpp

In Ubuntu:
https://packagecloud.io/mrtazz/restclient-cpp

Client files:
-------------
main.cpp is the file to send REST API calls to the Server.
It has been tested for the GET API call:
RestClient::get("http://127.0.0.1:8080/retrieveAppt?apptCode=APPT1")

Examples of other REST API calls can be found here:
https://github.com/mrtazz/restclient-cpp/blob/main/README.md
