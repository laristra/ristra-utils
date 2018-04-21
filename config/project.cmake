#------------------------------------------------------------------------------#
#           _____       _____              _____
#    __________(_)________  /_____________ ___(_)_____
#    __  ___/_  /__  ___/  __/_  ___/  __ `/_  /_  __ \
#    _  /   _  / _(__  )/ /_ _  /   / /_/ /_  / / /_/ /
#    /_/    /_/  /____/ \__/ /_/    \__,_/ /_/  \____/
#
# Copyright (c) 2018 Los Alamos National Security, LLC
# All rights reserved.
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
# Add library targets
#------------------------------------------------------------------------------#

cinch_add_library_target(RistraLL ristrall EXPORT_TARGET RistraLLTargets)
target_link_libraries(RistraLL ${Boost_LIBRARIES})

#------------------------------------------------------------------------------#
# Prepare variables for RistraLLConfig file.
#------------------------------------------------------------------------------#

# FIXME

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

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
