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
# Add header and source files.
#------------------------------------------------------------------------------#

set(io_HEADERS
  interface.h
  PARENT_SCOPE
)

set(io_SOURCES
  interface.cc
  PARENT_SCOPE
)

if(RISTRAIO_DRIVER STREQUAL "design")

  set(io_HEADERS
    ${io_HEADERS}
    design/driver_policy.h
  )

  set(io_SOURCES
    ${io_SOURCES}
    design/driver_policy.cc
  )

elseif(RISTRAIO_DRIVER STREQUAL "hdf5")

endif()

#------------------------------------------------------------------------------#
# Export header list to parent scope.
#------------------------------------------------------------------------------#

set(io_HEADERS
  ${io_HEADERS}
  PARENT_SCOPE
)

#------------------------------------------------------------------------------#
# Export source list to parent scope.
#------------------------------------------------------------------------------#

set(io_SOURCES
  ${io_SOURCES}
  PARENT_SCOPE
)

#------------------------------------------------------------------------------#
# Unit tests
#------------------------------------------------------------------------------#

cinch_add_unit(interface
  SOURCES
    test/interface.cc
  LIBRARIES
    RistraIO
  POLICY
    SERIAL
  THREADS 1
)
