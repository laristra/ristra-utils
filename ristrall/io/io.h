/*
  _____________       _____              ____________ 
  ___  __ \__(_)________  /_____________ ___  /___  / 
  __  /_/ /_  /__  ___/  __/_  ___/  __ `/_  / __  /  
  _  _, _/_  / _(__  )/ /_ _  /   / /_/ /_  /___  /___
  /_/ |_| /_/  /____/ \__/ /_/    \__,_/ /_____/_____/

  Copyright (c) 2018 Los Alamos National Security, LLC
  All rights reserved.
                                                                              */
#pragma once

/*! @file */

#include <ristrall/io/interface.h>

/*!
  Register an I/O target with the RistraIO runtime. The I/O functions
  registered by each target will be invoked during I/O operations to
  generate the appropriate output.

  @param name         The name of the target. This can be any valid
                      C++ variable name, and must be unique. Naming
                      collisions will be detected at compile time, and
                      will generate an error.
  @param io_functions An aggragate instance of the
                      interface_t::io_functions_t type specifying the
                      set of callback functions for the target.
 */

#define ristrall_register_target(name, io_functions)                           \
  /* MACRO IMPLEMENTATION */                                                   \
                                                                               \
  /* Call interface policy to register the target */                           \
  bool ristrall_target_##name##_registered =                                   \
    ristrall::io::interface_t::register_target(                                \
      ristrall::utils::const_string_t{EXPAND_AND_STRINGIFY(nspace)}.hash(),    \
      io_functions)
