#------------------------------------------------------------------------------#
# Copyright (c) 2014 Los Alamos National Security, LLC
# All rights reserved.
#------------------------------------------------------------------------------#

set(utils_HEADERS
  hash.h
  const_string.h
  dag.h
  graphviz.h
  tuple_walker.h
  typeify.h
  PARENT_SCOPE
)

set(utils_SOURCES
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
