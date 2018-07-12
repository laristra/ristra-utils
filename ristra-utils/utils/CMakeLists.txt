#------------------------------------------------------------------------------#
# Copyright (c) 2014 Los Alamos National Security, LLC
# All rights reserved.
#------------------------------------------------------------------------------#

set(utils_HEADERS
  hash.h
  const_string.h
  debruijn.h
  dag.h
  demangle.h
  function_traits.h
  graphviz.h
  macros.h
  tuple_visit.h
  tuple_walker.h
  typeify.h
  PARENT_SCOPE
)

set(utils_SOURCES
  debruijn.cc
  demangle.cc
  PARENT_SCOPE
)

#------------------------------------------------------------------------------#
# Unit tests.
#------------------------------------------------------------------------------#

#cinch_add_unit(dag
#  SOURCES test/dag.cc
#  LIBRARIES ${FLECSI_LIBRARY_DEPENDENCIES}
#)

#cinch_add_unit(const_string
#  SOURCES test/const_string.cc common.cc
#  FOLDER "Tests/Util"
#)

#cinch_add_unit(hash
#  SOURCES test/hash.cc
#  FOLDER "Tests/Util"
#)

cinch_add_unit(debruijn
  SOURCES
    debruijn.cc
    test/debruijn.cc
  FOLDER
    "Tests/Util"
)

cinch_add_unit(tuple_walker
  SOURCES
    test/tuple_walker.cc
  INPUTS
    test/tuple_walker.blessed
  FOLDER
    "Tests/Util"
)
