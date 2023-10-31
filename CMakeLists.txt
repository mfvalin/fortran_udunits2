cmake_minimum_required(VERSION 3.17)

project(
  Fortran_UDUNITS2
  VERSION 1.0.0
  LANGUAGES Fortran)

# Add cmake directory to module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find the UDUNITS2 library
find_package(udunits REQUIRED)
find_package(EXPAT REQUIRED)

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

set (top-dir Fortran_UDUNITS2-${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
set (Fortran_UDUNITS2_TOP_DIR "${CMAKE_INSTALL_PREFIX}/${top-dir}" CACHE PATH "")

# Create the library
add_library(
  Fortran_UDUNITS2
  ${SOURCES}
)
target_link_libraries(
  Fortran_UDUNITS2
  udunits::udunits EXPAT::EXPAT
)

# Install the library
install(
  TARGETS Fortran_UDUNITS2
  EXPORT Fortran_UDUNITS2
  LIBRARY DESTINATION "${Fortran_UDUNITS2_TOP_DIR}/lib"
  ARCHIVE DESTINATION "${Fortran_UDUNITS2_TOP_DIR}/lib"
  RUNTIME DESTINATION "${Fortran_UDUNITS2_TOP_DIR}/bin"
  INCLUDES DESTINATION "${Fortran_UDUNITS2_TOP_DIR}/include"
)

# We need to install the module files
install(
  DIRECTORY "${CMAKE_Fortran_MODULE_DIRECTORY}/"
  DESTINATION "${Fortran_UDUNITS2_TOP_DIR}/include"
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
  Fortran_UDUNITS2Config.cmake.in
  Fortran_UDUNITS2Config.cmake
  INSTALL_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Fortran_UDUNITS2Config.cmake
)
write_basic_package_version_file(
  Fortran_UDUNITS2Config-version.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/Fortran_UDUNITS2Config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/Fortran_UDUNITS2Config-version.cmake
    DESTINATION "${Fortran_UDUNITS2_TOP_DIR}/cmake"
)

install(
  EXPORT Fortran_UDUNITS2
  FILE Fortran_UDUNITS2Targets.cmake
  NAMESPACE Fortran_UDUNITS2::
  DESTINATION "${Fortran_UDUNITS2_TOP_DIR}/cmake"
)
export(EXPORT Fortran_UDUNITS2
  FILE "${CMAKE_CURRENT_BINARY_DIR}/Fortran_UDUNITS2Targets.cmake"
  NAMESPACE Fortran_UDUNITS2::
)

# There is a test in tests, let's add it
# Linking to udunits requires EXPAT
find_package(EXPAT REQUIRED)

# Build the executable
add_executable(
  "test_f_udunits_2.exe"
  "tests/test_f_udunits_2.F90"
)
target_link_libraries(
  test_f_udunits_2.exe
  Fortran_UDUNITS2 udunits::udunits EXPAT::EXPAT
)

# https://www.scivision.dev/cmake-auto-gitignore-build-dir/
# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()
