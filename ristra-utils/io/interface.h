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

#include <map>
#include <string>

namespace ristra {
namespace io {

struct record_t {
  size_t id;
}; // struct record_t

template<typename IO_DRIVER_POLICY>
struct interface__ : public IO_DRIVER_POLICY
{

  /*!
    Initialize the directory structure and required header information
    for a ristra simulation.

    @param path The directory path to the location where the simulation
                structure should reside.
    @param name The name of the simulation. This sill be the name of the
                subdirectory of \ref path where the simulation files and
                directory strcuture will be created.

    @return This method returns true if the initialization is successful,
            false otherwise.
   */

  bool initialize_simulation(std::string path, std::string name) {
    return IO_DRIVER_POLICY::initialize_simulation(path, name);
  } // initialize_simulation

  /*!
   */

  void add_simulation_parameter(record_t & record) {
    return IO_DRIVER_POLICY::add_simulation_parameter(record);
  } // add_simulation_parameter

}; // struct interface__

} // namespace io
} // namespace ristra

// This include file defines the IO_DRIVER_POLICY used below.

#include <ristra-utils/io/ristra_io_driver_policy.h>

namespace ristra {
namespace io {
  
/*!
 */

using interface_t = interface__<RISTRA_UTILS_IO_DRIVER_POLICY>;

} // namespace io
} // namespace ristra
