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

project(RistraIO)

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

set(RISTRAIO_DRIVERS design hdf5)

if(NOT RISTRAIO_DRIVER)
  list(GET RISTRAIO_DRIVERS 0 RISTRAIO_DRIVER)
endif()

set(RISTRAIO_DRIVER "${RISTRAIO_DRIVER}" CACHE STRING "Select the driver")
set_property(CACHE RISTRAIO_DRIVER PROPERTY STRINGS ${RISTRAIO_DRIVERS})

#------------------------------------------------------------------------------#
# Boost Filesystem
#------------------------------------------------------------------------------#

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#------------------------------------------------------------------------------#
# Add library targets
#------------------------------------------------------------------------------#

cinch_add_library_target(RistraIO ristraio EXPORT_TARGET RistraIOTargets)
target_link_libraries(RistraIO ${Boost_LIBRARIES})

#------------------------------------------------------------------------------#
# Prepare variables for RistraIOConfig file.
#------------------------------------------------------------------------------#

# FIXME

#------------------------------------------------------------------------------#
# Configure header
#------------------------------------------------------------------------------#

configure_file(${PROJECT_SOURCE_DIR}/config/ristraio-config.h.in
  ${CMAKE_BINARY_DIR}/ristraio-config.h @ONLY)

include_directories(${CMAKE_BINARY_DIR})

install(
  FILES ${CMAKE_BINARY_DIR}/ristraio-config.h
  DESTINATION include
)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
