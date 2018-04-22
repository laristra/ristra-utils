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

#include <map>
#include <string>

namespace ristrall {
namespace io {

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
  } // initialize_simulation

}; // struct interface__

} // namespace io
} // namespace ristrall

// This include file defines the IO_DRIVER_POLICY used below.

#include <ristrall/io/ristrall_io_driver_policy.h>

namespace ristrall {
namespace io {
  
/*!
 */

using interface_t = interface__<RISTRALL_IO_DRIVER_POLICY>;

} // namespace io
} // namespace ristrall
