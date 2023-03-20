cmake_minimum_required(VERSION 3.17)

project(
  "Fortran_UDUNITS2"
  VERSION 1.0.0
  LANGUAGES Fortran)

# Add cmake directory to module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find the UDUNITS2 library
find_package(udunits REQUIRED)

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
