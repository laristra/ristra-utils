#------------------------------------------------------------------------------#
#  _____________       _____              _____  _________________
#  ___  __ \__(_)________  /_____________ __  / / /_  /___(_)__  /_______
#  __  /_/ /_  /__  ___/  __/_  ___/  __ `/  / / /_  __/_  /__  /__  ___/
#  _  _, _/_  / _(__  )/ /_ _  /   / /_/ // /_/ / / /_ _  / _  / _(__  )
#  /_/ |_| /_/  /____/ \__/ /_/    \__,_/ \____/  \__/ /_/  /_/  /____/
#
#  Copyright (c) 2018 Los Alamos National Security, LLC
#  All rights reserved.
#------------------------------------------------------------------------------#

#------------------------------------------------------------------------------#
# Set the minimum Cinch version
#------------------------------------------------------------------------------#

cinch_minimum_required(1.0)

#------------------------------------------------------------------------------#
# Set the project name
#------------------------------------------------------------------------------#

project(RistraUtils)

#------------------------------------------------------------------------------#
# Set header suffix regular expression
#------------------------------------------------------------------------------#

set(CINCH_HEADER_SUFFIXES "\\.h")

#------------------------------------------------------------------------------#
# Check for C++17 compiler.
#------------------------------------------------------------------------------#

include(cxx17)

check_for_cxx17_compiler(CXX17_COMPILER)

if(CXX17_COMPILER)
	enable_cxx17()
else()
	message(FATAL_ERROR "C++17 compatible compiler not found")
endif()

#------------------------------------------------------------------------------#
# Load cinch extras
#------------------------------------------------------------------------------#

cinch_load_extras()

#------------------------------------------------------------------------------#
# Add options for driver selection
#------------------------------------------------------------------------------#

set(RISTRA_IO_DRIVERS design hdf5)

if(NOT RISTRA_IO_DRIVER)
  list(GET RISTRA_IO_DRIVERS 0 RISTRA_IO_DRIVER)
endif()

set(RISTRA_IO_DRIVER "${RISTRA_IO_DRIVER}" CACHE STRING
  "Select the driver")
set_property(CACHE RISTRA_IO_DRIVER PROPERTY STRINGS
  ${RISTRA_IO_DRIVERS})

#------------------------------------------------------------------------------#
# Boost Filesystem
#------------------------------------------------------------------------------#

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#------------------------------------------------------------------------------#
# Configure header
#------------------------------------------------------------------------------#

configure_file(${PROJECT_SOURCE_DIR}/config/ristra-utils-config.h.in
  ${CMAKE_BINARY_DIR}/ristra-utils-config.h @ONLY)

include_directories(${CMAKE_BINARY_DIR})

install(
  FILES ${CMAKE_BINARY_DIR}/ristra-utils-config.h
  DESTINATION include
)

#------------------------------------------------------------------------------#
# Add library targets
#------------------------------------------------------------------------------#

cinch_add_library_target(RistraUtils ristra-utils EXPORT_TARGET
  RistraUtilsTargets)
target_link_libraries(RistraUtils ${Boost_LIBRARIES})

#------------------------------------------------------------------------------#
# Prepare variables for RistraUtilsConfig file.
#------------------------------------------------------------------------------#

set(RISTRA_EXTERNAL_INCLUDE_DIRS)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  PROPERTY INCLUDE_DIRECTORIES)

foreach(dir ${dirs})
  if(NOT ${dir} MATCHES ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND RISTRA_EXTERNAL_INCLUDE_DIRS ${dir})
  endif()
endforeach()

set(RISTRA_LIBRARY_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR})
set(RISTRA_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include
  ${RISTRA_EXTERNAL_INCLUDE_DIRS})

set(RISTRA_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/RistraUtils)

#------------------------------------------------------------------------------#
# Extract all project options so they can be exported to the
# ProjectConfig.cmake file.
#------------------------------------------------------------------------------#

get_cmake_property(_variableNames VARIABLES)
string(REGEX MATCHALL "(^|;)RISTRA_[A-Za-z0-9_]*"
  _matchedVars "${_variableNames}"
)

foreach(_variableName ${_matchedVars})
  set(RISTRA_CONFIG_CODE
    "${RISTRA_CONFIG_CODE}\nset(${_variableName} \"${${_variableName}}\")")
endforeach()

#------------------------------------------------------------------------------#
# Export targets and package.
#------------------------------------------------------------------------------#

export(
  TARGETS RistraUtils
  FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraUtilsTargets.cmake
)

export(PACKAGE RistraUtils)

#------------------------------------------------------------------------------#
# CMake config file: This should be the last thing to happen.
#------------------------------------------------------------------------------#

configure_file(${PROJECT_SOURCE_DIR}/config/RistraUtilsConfig.cmake.in
  ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraUtilsConfig.cmake @ONLY)

install(
  FILES ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraUtilsConfig.cmake
  DESTINATION ${RISTRA_CMAKE_DIR}
)

install(
  EXPORT RistraUtilsTargets
  DESTINATION ${RISTRA_CMAKE_DIR}
  COMPONENT dev
)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
