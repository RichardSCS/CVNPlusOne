Name: Jacob Aaronson
UNI: jja2166

# COMS-4156-MiniProject
This is the GitHub repository for the mini project associated with COMS 4156 Advanced Software Engineering. 

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

#### GET /retrieveDept
* Expected Input Parameters: deptCode
* Expected Output: department details
* Upon Success: HTTP 200 Status Code is returned along with department details in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" in the response body. 

#### GET /retrieveCourse
* Expected Input Parameters: deptCode, courseCode
* Expected Output: course details
* Upon Success: HTTP 200 Status Code is returned along with course details in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Course Not Found" or "Department Not Found" in the response body. 

#### GET /isCourseFull
* Expected Input Parameters: deptCode, courseCode
* Expected Output: true or false
* Upon Success: HTTP 200 Status Code is returned along with true or false in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Course Not Found" or "Department Not Found" in the response body.

#### GET /getMajorCountFromDept
* Expected Input Parameters: deptCode
* Expected Output: number of majors in the specified department
* Upon Success: HTTP 200 Status Code is returned along with number of majors in the specified department in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" in the response body.

#### GET /idDeptChair
* Expected Input Parameters: deptCode
* Expected Output: name of the department chair
* Upon Success: HTTP 200 Status Code is returned along with name of department chair of the specified department in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" in the response body.

#### GET /findCourseLocation
* Expected Input Parameters: deptCode, courseCode
* Expected Output: course location
* Upon Success: HTTP 200 Status Code is returned along with course location in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Course Not Found" or "Department Not Found" in the response body.


#### GET /findCourseInstructor
* Expected Input Parameters: deptCode, courseCode
* Expected Output: course instructor
* Upon Success: HTTP 200 Status Code is returned along with course instructor in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Course Not Found" or "Department Not Found" in the response body.

#### GET /findCourseTime
* Expected Input Parameters: deptCode, courseCode
* Expected Output: course time
* Upon Success: HTTP 200 Status Code is returned along with course time in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Course Not Found" or "Department Not Found" in the response body.

  
#### GET /addMajorToDept
* Expected Input Parameters: deptCode
* Expected Output: Adds a major to the given department
* Upon Success: HTTP 200 Status Code is returned along with "Attribute was updated successfully" in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" in the response body.

#### GET /removeMajorFromDept
* Expected Input Parameters: deptCode
* Expected Output: Removes a major from the given department
* Upon Success: HTTP 200 Status Code is returned along with "Attribute was updated successfully" in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" or "Course Not Found" in the response body.

#### PATCH /changeCourseLocation
* Expected Input Parameters: deptCode, courseCode, location
* Expected Output: Changes course location
* Upon Success: HTTP 200 Status Code is returned along with "Attribute was updated successfully" in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" or "Course Not Found" in the response body.

#### PATCH /changeCourseTeacher
* Expected Input Parameters: deptCode, courseCode, name
* Expected Output: Changes course instructor
* Upon Success: HTTP 200 Status Code is returned along with "Attribute was updated successfully" in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" or "Course Not Found" in the response body.

#### PATCH /changeCourseTime
* Expected Input Parameters: deptCode, courseCode, time
* Expected Output: Changes course time
* Upon Success: HTTP 200 Status Code is returned along with "Attribute was updated successfully" in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" or "Course Not Found" in the response body.

#### PATCH /setEnrollmentCount
* Expected Input Parameters: deptCode, courseCode, count
* Expected Output: Changes course enrollment count
* Upon Success: HTTP 200 Status Code is returned along with "Attribute was updated successfully" in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" or "Course Not Found" in the response body.

#### GET /retrieveCourses
* Expected Input Parameters: courseCode
* Expected Output: Details for all courses from any department with the given course code
* Upon Success: HTTP 200 Status Code is returned along with course details in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "No Courses Found" in the response body.

#### GET /enrollStudentInCourse
* Expected Input Parameters: deptCode, courseCode
* Expected Output: Enrolls student in a course
* Upon Success: HTTP 200 Status Code is returned along with "Student has been enrolled" in the response body
* Upon Failure: HTTP 404 Status Code is returned along with "Department Not Found" or "Course Not Found" in the response body.

## Style Checking Report
The cpplint tool was used to check the style of the code.

## Branch Coverage Reporting
The lcov tool was used to to perform branch analysis in order to see the branch coverage of the relevant code within the code base.
See code_coverage_9_20.png for code coverage info from lcov. Line coverage is 58.9%. Function coverage is 69.2%.

## Static Code Analysis
The cppcheck tool was used to perform static analysis on the codebase.
See IndividualMiniprojectC++/cppcheck_src.txt and IndividualMiniprojectC++/cppcheck_test.txt for output of status analysis checks.

## Continuous Integration Report
I am using GitHub Actions to perform continous integration. To view the latest results go to the following link: https://github.com/jja2166/-4156-Miniproject-2024-Students-Cplusplus-private/actions/workflows/cmake-single-platform.yml