cmake_minimum_required(VERSION 3.17)

project(
  "Fortran_UDUNITS2"
  VERSION 1.0.0
  LANGUAGES Fortran)

# Add cmake directory to module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find the UDUNITS2 library
find_package(udunits REQUIRED)

# Let's print some information about the library
include(CMakePrintHelpers)
cmake_print_properties(
  TARGETS udunits::udunits
  PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES
    INTERFACE_LINK_LIBRARIES
)
cmake_print_variables(udunits_INCLUDE_DIR)
cmake_print_variables(udunits_LIBRARY)
cmake_print_variables(udunits_LIBRARY_SHARED)

# Add source files
set (SOURCES
  "source/f_udunits_2.F90"
  "source/f_udunits_2.inc"
)

# set fortran module directory
set(CMAKE_Fortran_MODULE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include")

# Create the library
add_library(
  "Fortran_UDUNITS2"
  ${SOURCES}
)

# Install the library
install(
  TARGETS "Fortran_UDUNITS2"
  EXPORT "Fortran_UDUNITS2Targets"
  LIBRARY DESTINATION "lib"
  ARCHIVE DESTINATION "lib"
  RUNTIME DESTINATION "bin"
  INCLUDES DESTINATION "include"
)

# We need to install the module files
install(
  DIRECTORY "${CMAKE_Fortran_MODULE_DIRECTORY}/"
  DESTINATION "include"
)

# Install the export file
install(
  EXPORT "Fortran_UDUNITS2Targets"
  FILE "Fortran_UDUNITS2Targets.cmake"
  NAMESPACE "Fortran_UDUNITS2::"
  DESTINATION "lib/cmake/Fortran_UDUNITS2"
)

# NOTE: The below bit of code is commented out because it is not
#       working. I can't seem to figure out how to link to libxml2
#       from macOS. I seem to be hitting the "How to link against
#       tbd files" problem.
#       https://discourse.cmake.org/t/newer-versions-of-macos-require-linking-against-tbd-files-and-not-old-system-paths-to-dylib/6871/3

#################################################################
# # There is a test in tests, let's add it                      #
# enable_testing()                                              #
#                                                               #
# # Linking to udunits requires XML2                            #
# find_package(LibXml2 REQUIRED)                                #
# cmake_print_properties(                                       #
#   TARGETS LibXml2::LibXml2                                    #
#   PROPERTIES                                                  #
#     INTERFACE_INCLUDE_DIRECTORIES                             #
#     INTERFACE_LINK_LIBRARIES                                  #
# )                                                             #
# cmake_print_variables(LibXml2_INCLUDE_DIRS LibXml2_LIBRARIES) #
#                                                               #
# # Build the executable                                        #
# add_executable(                                               #
#   "test_f_udunits_2.exe"                                      #
#   "tests/test_f_udunits_2.F90"                                #
# )                                                             #
# target_link_libraries(                                        #
#   test_f_udunits_2.exe                                        #
#   Fortran_UDUNITS2 udunits::udunits LibXml2::LibXml2          #
# )                                                             #
#                                                               #
#################################################################
# https://www.scivision.dev/cmake-auto-gitignore-build-dir/
# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()

# Piggyback that file into install
install(
   FILES ${PROJECT_BINARY_DIR}/.gitignore
   DESTINATION ${CMAKE_INSTALL_PREFIX}
   )
