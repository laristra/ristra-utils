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
# Automatic version creation.
#------------------------------------------------------------------------------#

include(version)
message(STATUS "VERSION: ${${PROJECT_NAME}_VERSION}")

#------------------------------------------------------------------------------#
# Set header suffix regular expression
#------------------------------------------------------------------------------#

set(CINCH_HEADER_SUFFIXES "\\.h")

#------------------------------------------------------------------------------#
# Set required C++ standard
#------------------------------------------------------------------------------#

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

#------------------------------------------------------------------------------#
# Create developer guide header with version information
#------------------------------------------------------------------------------#

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/ristra_dg_header.tex.in
#    ${CMAKE_BINARY_DIR}/doc/ristra_dg_header.tex
#)

#------------------------------------------------------------------------------#
# Pandoc options for developer guide
#------------------------------------------------------------------------------#

#set(dg_pandoc_options
#    "--toc"
#    "--include-in-header=${CMAKE_SOURCE_DIR}/cinch/tex/addtolength.tex"
#    "--include-in-header=${CMAKE_BINARY_DIR}/doc/ristra_dg_header.tex"
#    "--include-before-body=${CMAKE_CURRENT_SOURCE_DIR}/doc/ristra_dg_title.tex"
#    "--include-before-body=${CMAKE_SOURCE_DIR}/cinch/tex/firstpageempty.tex"
#)

#set(dg_image_list "${CMAKE_SOURCE_DIR}/doc/medium-ristra.png")

#------------------------------------------------------------------------------#
# Add developer guide target
#------------------------------------------------------------------------------#

#cinch_add_doc(ristra-developer-guide ristra_dg.py "ristra;auxiliary"
#    ristra-developer-guide-${${PROJECT_NAME}_VERSION}.pdf
#    PANDOC_OPTIONS ${dg_pandoc_options}
#    # IMAGE_GLOB "*.pdf"
#    #    IMAGE_LIST ${dg_image_list}
#)

#------------------------------------------------------------------------------#
# Load cinch extras
#------------------------------------------------------------------------------#

cinch_load_extras()

#------------------------------------------------------------------------------#
# Add options for driver selection
#------------------------------------------------------------------------------#

set(RISTRAUTILS_IO_DRIVERS design hdf5)

if(NOT RISTRAUTILS_IO_DRIVER)
  list(GET RISTRAUTILS_IO_DRIVERS 0 RISTRAUTILS_IO_DRIVER)
endif()

set(RISTRAUTILS_IO_DRIVER "${RISTRAUTILS_IO_DRIVER}" CACHE STRING
  "Select the driver")
set_property(CACHE RISTRAUTILS_IO_DRIVER PROPERTY STRINGS
  ${RISTRAUTILS_IO_DRIVERS})

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

set(RISTRAUTILS_EXTERNAL_INCLUDE_DIRS)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  PROPERTY INCLUDE_DIRECTORIES)

foreach(dir ${dirs})
  if(NOT ${dir} MATCHES ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND RISTRAUTILS_EXTERNAL_INCLUDE_DIRS ${dir})
  endif()
endforeach()

set(RISTRAUTILS_LIBRARY_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR})
set(RISTRAUTILS_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include
  ${RISTRAUTILS_EXTERNAL_INCLUDE_DIRS})

set(RISTRAUTILS_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/RistraUtils)

#------------------------------------------------------------------------------#
# Extract all project options so they can be exported to the
# ProjectConfig.cmake file.
#------------------------------------------------------------------------------#

get_cmake_property(_variableNames VARIABLES)
string(REGEX MATCHALL "(^|;)RISTRAUTILS_[A-Za-z0-9_]*"
  _matchedVars "${_variableNames}"
)

foreach(_variableName ${_matchedVars})
  set(RISTRAUTILS_CONFIG_CODE
    "${RISTRAUTILS_CONFIG_CODE}\nset(${_variableName} \"${${_variableName}}\")")
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
  DESTINATION ${RISTRAUTILS_CMAKE_DIR}
)

install(
  EXPORT RistraUtilsTargets
  DESTINATION ${RISTRAUTILS_CMAKE_DIR}
  COMPONENT dev
)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
