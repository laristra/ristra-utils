#------------------------------------------------------------------------------#
#  _____________       _____              ____________
#  ___  __ \__(_)________  /_____________ ___  /___  /
#  __  /_/ /_  /__  ___/  __/_  ___/  __ `/_  / __  /
#  _  _, _/_  / _(__  )/ /_ _  /   / /_/ /_  /___  /___
#  /_/ |_| /_/  /____/ \__/ /_/    \__,_/ /_____/_____/
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

project(RistraLL)

#------------------------------------------------------------------------------#
# Set header suffix regular expression
#------------------------------------------------------------------------------#

set(CINCH_HEADER_SUFFIXES "\\.h")

#------------------------------------------------------------------------------#
# Check for C++17 compiler.
#------------------------------------------------------------------------------#

include(cxx17)

check_for_cxx17_compiler(CXX11_COMPILER)

if(CXX11_COMPILER)
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

set(RISTRALL_IO_DRIVERS design hdf5)

if(NOT RISTRALL_IO_DRIVER)
  list(GET RISTRALL_IO_DRIVERS 0 RISTRALL_IO_DRIVER)
endif()

set(RISTRALL_IO_DRIVER "${RISTRALL_IO_DRIVER}" CACHE STRING "Select the driver")
set_property(CACHE RISTRALL_IO_DRIVER PROPERTY STRINGS ${RISTRALL_IO_DRIVERS})

#------------------------------------------------------------------------------#
# Boost Filesystem
#------------------------------------------------------------------------------#

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#------------------------------------------------------------------------------#
# Configure header
#------------------------------------------------------------------------------#

configure_file(${PROJECT_SOURCE_DIR}/config/ristrall-config.h.in
  ${CMAKE_BINARY_DIR}/ristrall-config.h @ONLY)

include_directories(${CMAKE_BINARY_DIR})

install(
  FILES ${CMAKE_BINARY_DIR}/ristrall-config.h
  DESTINATION include
)

#------------------------------------------------------------------------------#
# Add library targets
#------------------------------------------------------------------------------#

cinch_add_library_target(RistraLL ristrall EXPORT_TARGET RistraLLTargets)
target_link_libraries(RistraLL ${Boost_LIBRARIES})

#------------------------------------------------------------------------------#
# Prepare variables for RistraLLConfig file.
#------------------------------------------------------------------------------#

set(RISTRALL_EXTERNAL_INCLUDE_DIRS)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  PROPERTY INCLUDE_DIRECTORIES)

foreach(dir ${dirs})
  if(NOT ${dir} MATCHES ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND RISTRALL_EXTERNAL_INCLUDE_DIRS ${dir})
  endif()
endforeach()

set(RISTRALL_LIBRARY_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR})
set(RISTRALL_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include
  ${RISTRALL_EXTERNAL_INCLUDE_DIRS})

set(RISTRALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/RistraLL)

#------------------------------------------------------------------------------#
# Extract all project options so they can be exported to the
# ProjectConfig.cmake file.
#------------------------------------------------------------------------------#

get_cmake_property(_variableNames VARIABLES)
string(REGEX MATCHALL "(^|;)RISTRALL_[A-Za-z0-9_]*"
  _matchedVars "${_variableNames}"
)

foreach(_variableName ${_matchedVars})
  set(RISTRALL_CONFIG_CODE
    "${RISTRALL_CONFIG_CODE}\nset(${_variableName} \"${${_variableName}}\")")
endforeach()

#------------------------------------------------------------------------------#
# Export targets and package.
#------------------------------------------------------------------------------#

export(
  TARGETS RistraLL
  FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraLLTargets.cmake
)

export(PACKAGE RistraLL)

#------------------------------------------------------------------------------#
# CMake config file: This should be the last thing to happen.
#------------------------------------------------------------------------------#

configure_file(${PROJECT_SOURCE_DIR}/config/RistraLLConfig.cmake.in
  ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraLLConfig.cmake @ONLY)

install(
  FILES ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraLLConfig.cmake
  DESTINATION ${RISTRALL_CMAKE_DIR}
)

install(
  EXPORT RistraLLTargets
  DESTINATION ${RISTRALL_CMAKE_DIR}
  COMPONENT dev
)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
