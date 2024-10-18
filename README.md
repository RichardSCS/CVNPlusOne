Team Name: CVNPlusOne

# COMS-4156-Project
This is the GitHub repository for the project associated with COMS 4156 Advanced Software Engineering. 

## Building and Running a Local Instance
In order to build and use the service you must install the following (assuming an Ubuntu install):

1. CLang 3.30
2. ASIO library
3. Crow library
4. Boost library
5. Crow and Boost libraries should be extracted to the "external_libraries" folder.

## Running a Cloud based Instance
You can run a cloud-based instance of this service by spinning up a Compute Engine VM, and then installing as if it were a local instance.

## Running Tests
The unit tests are located under the directory 'test'. To run the projects unit tests, you must first build the project.

Running 'make' will build both the program binary and the test binary. You can execute the test binary to see the outcome of the tests.

## Endpoints
This section describes the endpoints that the service provides, as well as their inputs and outputs. 

#### GET /retrieveAppt
* Expected Input Parameters: apptCode
* Expected Output: appointment details
* Upon Success: HTTP 200 Status Code is returned along with appointment details in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Appointment Not Found" in the response body. 

#### DELETE /deleteAppt
* Expected Input Parameters: apptCode
* Expected Output: "Appointment deleted successfully"
* Upon Success: HTTP 200 Status Code is returned along with 
"Appointment deleted successfully" in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Appointment Not Found" in the response body. 

#### PUT /createAppt
* Expected Input Parameters: title startTime endTime location
* Expected Output: apptCode
* Upon Success: HTTP 201 Status Code is returned along with appointment code in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Appointment Exists :" and details of appointment in the response body. 
* If title param is missing, HTTP 400 Status Code is returned along with "Missing appointment title" in the response body
* If startTime is missing, HTTP 400 Status Code is returned along with "Missing appointment startTime" in the response body
* If endTime is missing, HTTP 400 Status Code is returned along with "Missing appointment endTime" in the response body
* If location is missing, HTTP 400 Status Code is returned along with "Missing appointment location" in the response body

#### PATCH /updateApptTitle
* Expected Input Parameters: apptCode apptTitle
* Expected Output: "Appointment title successfully updated."
* Upon Success: HTTP 200 Status Code is returned along with "Appointment title successfully updated." in the response body.
* Upon Failure: HTTP 404 Status Code is returned along with "Appointment Not Found" in the response body. 

#### PATCH /updateApptLocation
* Expected Input Parameters: apptCode apptLocation
* Expected Output: "Appointment location successfully updated."
* Upon Success: HTTP 200 Status Code is returned along with "Appointment location successfully updated." in the response body.
* Upon Failure: HTTP 404 Status Code is returned along with "Appointment Not Found" in the response body. 

#### PATCH /updateApptTimes
* Expected Input Parameters: apptCode startTime endTime
* Expected Output: "Appointment time successfully updated."
* Upon Success: HTTP 200 Status Code is returned along with "Appointment time successfully updated." in the response body.
* Upon Failure: HTTP 404 Status Code is returned along with "Appointment Not Found" or HTTP 400 Status Code is returned along with "Failed to update appointment time." in the response body. 

## Database
For first iteration we have set up testfile.bin. On calling `IndividualMiniproject setup`, db entries will be setup. On subsequent calls to IndividualMiniproject without `setup`, it reads the appointments from the db. On termination it writes the appointments created into the db.

## Style Checking Report
The cpplint tool was used to check the style of the code.

## Branch Coverage Reporting
The lcov tool was used to to perform branch analysis in order to see the branch coverage of the relevant code within the code base.

## Static Code Analysis
The cppcheck tool was used to perform static analysis on the codebase.

## Continuous Integration Report
We are using GitHub Actions to perform continous integration. 

## Tools used
We use Postman for API testing, and Github Issue for project management purpose