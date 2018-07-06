/*
  _____________       _____              _____  _________________
  ___  __ \__(_)________  /_____________ __  / / /_  /___(_)__  /_______
  __  /_/ /_  /__  ___/  __/_  ___/  __ `/  / / /_  __/_  /__  /__  ___/
  _  _, _/_  / _(__  )/ /_ _  /   / /_/ // /_/ / / /_ _  / _  / _(__  )
  /_/ |_| /_/  /____/ \__/ /_/    \__,_/ \____/  \__/ /_/  /_/  /____/

  Copyright (c) 2018 Los Alamos National Security, LLC
  All rights reserved.
                                                                              */
#pragma once

/*! @file */

namespace ristra {

} // namespace ristra
#include <ristra-utils/io/interface.h>
#include <ristra-utils/io/registry.h>
#include <ristra-utils/utils/const_string.h>
#include <ristra-utils/utils/macros.h>

/*!
  Create an instance of the registry_t::io_functions_t type suitable
  for passing to ristra_register_io_target.

  @param ... A variadic argument list of io functions.
 */

#define ristra_io_functions(...)                                               \
  /* MACRO IMPLEMENTATION */                                                   \
                                                                               \
  ristra::io::registry_t::io_functions_t(__VA_ARGS__)

/*!
  Register an I/O target with the Ristra runtime. The I/O functions
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

#define ristra_register_io_target(type, name, io_functions)                    \
  /* MACRO IMPLEMENTATION */                                                   \
                                                                               \
  /* Call interface policy to register the target */                           \
  bool ristra_target_##name##_registered =                                     \
    ristra::io::registry_t::instance().register_target(                        \
      ristra::io::registry_t::target_type_t::type,                             \
      ristra::utils::const_string_t{                                           \
        EXPAND_AND_STRINGIFY(name)                                             \
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
  ristra::io::registry_t::instance().checkpoint(path)

/*!
  Invoke the restart method for each of the registered targets.

  @param path The path to the simulation directory.
 */

#define ristra_restart(path)                                                   \
  /* MACRO IMPLEMENTATION */                                                   \
                                                                               \
  ristra::io::registry_t::instance().restart(path)
