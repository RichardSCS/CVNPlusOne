To build the project change your present working directory to this directory and then run the following commands:

cmake .. 
make 
make cpplint -for style checking

If you ever need to clean up some files make clean is always an option

To run coverage report run these commands in this directory:

$cmake -DENABLE_COVERAGE=true . && make
$./CodeCoverage; make coverage
