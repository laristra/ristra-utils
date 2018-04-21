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
# Add header and source files.
#------------------------------------------------------------------------------#

set(io_HEADERS
  interface.h
  ristrall_io_driver_policy.h
  PARENT_SCOPE
)

set(io_SOURCES
  interface.cc
  PARENT_SCOPE
)

if(RISTRALL_IO_DRIVER STREQUAL "design")

  set(io_HEADERS
    ${io_HEADERS}
    design/driver_policy.h
  )

  set(io_SOURCES
    ${io_SOURCES}
    design/driver_policy.cc
  )

elseif(RISTRALL_IO_DRIVER STREQUAL "hdf5")

  set(io_HEADERS
    ${io_HEADERS}
    hdf5/driver_policy.h
  )

  set(io_SOURCES
    ${io_SOURCES}
    hdf5/driver_policy.cc
  )

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
    RistraLL
  POLICY
    SERIAL
  THREADS 1
)
