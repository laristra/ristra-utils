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
#include <ristrall/io/registry.h>
#include <ristrall/utils/const_string.h>

/*!
  Create an instance of the registry_t::io_functions_t type suitable
  for passing to ristra_register_io_target.

  @param ... A variadic argument list of io functions.
 */

#define ristra_io_functions(...)                                               \
  /* MACRO IMPLEMENTATION */                                                   \
                                                                               \
  ristrall::io::registry_t::io_functions_t(__VA_ARGS__)

/*!
  Register an I/O target with the RistraLL runtime. The I/O functions
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

#define ristra_register_io_target(name, io_functions)                          \
  /* MACRO IMPLEMENTATION */                                                   \
                                                                               \
  /* Call interface policy to register the target */                           \
  bool ristrall_target_##name##_registered =                                   \
    ristrall::io::registry_t::instance().register_target(                      \
      ristrall::utils::const_string_t{                                         \
        RISTRALL_EXPAND_AND_STRINGIFY(name)                                    \
      }.hash(),                                                                \
      io_functions                                                             \
    )

/*!
  Invoke the checkpoint method for each of the registered targets.

  @param path The path to the simulation directory.
 */

#define ristra_checkpoint(path)                                                \
  /* MACRO IMPLEMENTATION */                                                   \
                                                                               \
  ristrall::io::registry_t::instance().checkpoint(path)

/*!
  Invoke the restart method for each of the registered targets.

  @param path The path to the simulation directory.
 */

#define ristra_restart(path)                                                   \
  /* MACRO IMPLEMENTATION */                                                   \
                                                                               \
  ristrall::io::registry_t::instance().restart(path)
