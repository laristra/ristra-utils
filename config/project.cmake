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

# After we load the cinch options, we need to capture the configuration
# state for the particular Cinch build configuration and set variables that
# are local to this project. RistraUtils should never directly use the raw
# options, e.g., ENABLE_OPTION should be captured as RISTRA_UTILS_ENABLE_OPTION
# and used as such in the code. This will handle collisions between nested
# projects that use Cinch.

cinch_load_extras()

get_cmake_property(_variableNames VARIABLES)
string (REGEX MATCHALL "(^|;)ENABLE_[A-Za-z0-9_]*"
  _matchedVars "${_variableNames}")

foreach(_variableName ${_matchedVars})
  set(RISTRA_UTILS_${_variableName} ${${_variableName}})
endforeach()

#------------------------------------------------------------------------------#
# Graphviz
#------------------------------------------------------------------------------#

option(ENABLE_GRAPHVIZ "Enable Graphviz Support" OFF)

if(ENABLE_GRAPHVIZ)
  find_package(Graphviz REQUIRED)

  if(GRAPHVIZ_FOUND)
    include_directories(${GRAPHVIZ_INCLUDE_DIRS})
    add_definitions(-DENABLE_GRAPHVIZ)

    list(APPEND RISTRA_UTILS_INCLUDE_DEPENDENCIES ${GRAPHVIZ_INCLUDE_DIR})
    list(APPEND RISTRA_UTILS_LIBRARY_DEPENDENCIES ${GRAPHVIZ_LIBRARIES})
  endif()
endif()

#------------------------------------------------------------------------------#
# Add options for driver selection
#------------------------------------------------------------------------------#

set(RISTRA_UTILS_IO_DRIVERS design hdf5 posix)

if(NOT RISTRA_UTILS_IO_DRIVER)
  list(GET RISTRA_UTILS_IO_DRIVERS 0 RISTRA_UTILS_IO_DRIVER)
endif()

set(RISTRA_UTILS_IO_DRIVER "${RISTRA_UTILS_IO_DRIVER}" CACHE STRING
  "Select the driver")
set_property(CACHE RISTRA_UTILS_IO_DRIVER PROPERTY STRINGS
  ${RISTRA_UTILS_IO_DRIVERS})

#------------------------------------------------------------------------------#
# Boost Filesystem
#------------------------------------------------------------------------------#

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#------------------------------------------------------------------------------#
# Configure header
#------------------------------------------------------------------------------#

set(RISTRA_UTILS_ENABLE_GRAPHVIZ ${ENABLE_GRAPHVIZ})

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

set(RISTRA_UTILS_EXTERNAL_INCLUDE_DIRS)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  PROPERTY INCLUDE_DIRECTORIES)

foreach(dir ${dirs})
  if(NOT ${dir} MATCHES ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND RISTRA_UTILS_EXTERNAL_INCLUDE_DIRS ${dir})
  endif()
endforeach()

set(RISTRA_UTILS_LIBRARY_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR})
set(RISTRA_UTILS_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include
  ${RISTRA_UTILS_EXTERNAL_INCLUDE_DIRS})

set(RISTRA_UTILS_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/RistraUtils)

#------------------------------------------------------------------------------#
# Extract all project options so they can be exported to the
# ProjectConfig.cmake file.
#------------------------------------------------------------------------------#

get_cmake_property(_variableNames VARIABLES)
string(REGEX MATCHALL "(^|;)RISTRA_UTILS_[A-Za-z0-9_]*"
  _matchedVars "${_variableNames}"
)

foreach(_variableName ${_matchedVars})
  set(RISTRA_UTILS_CONFIG_CODE "${RISTRA_UTILS_CONFIG_CODE}\nset(${_variableName} \"${${_variableName}}\")")
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
  DESTINATION ${RISTRA_UTILS_CMAKE_DIR}
)

install(
  EXPORT RistraUtilsTargets
  DESTINATION ${RISTRA_UTILS_CMAKE_DIR}
  COMPONENT dev
)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
