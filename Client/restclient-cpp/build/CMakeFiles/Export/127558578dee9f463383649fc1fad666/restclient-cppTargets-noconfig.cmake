#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "restclient-cpp" for configuration ""
set_property(TARGET restclient-cpp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(restclient-cpp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/librestclient-cpp.2.1.1.dylib"
  IMPORTED_SONAME_NOCONFIG "@rpath/librestclient-cpp.2.1.1.dylib"
  )

list(APPEND _cmake_import_check_targets restclient-cpp )
list(APPEND _cmake_import_check_files_for_restclient-cpp "${_IMPORT_PREFIX}/lib/librestclient-cpp.2.1.1.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
