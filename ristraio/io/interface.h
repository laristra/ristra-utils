/*
           _____       _____              _____
    __________(_)________  /_____________ ___(_)_____
    __  ___/_  /__  ___/  __/_  ___/  __ `/_  /_  __ \
    _  /   _  / _(__  )/ /_ _  /   / /_/ /_  / / /_/ /
    /_/    /_/  /____/ \__/ /_/    \__,_/ /_/  \____/

                                                                              */
#pragma once

/*! @file */

#include <map>
#include <string>

namespace ristraio {
namespace io {

template<typename DRIVER_POLICY>
struct interface__ : public DRIVER_POLICY
{

  //--------------------------------------------------------------------------//
  // Define function types for I/O interface.
  //--------------------------------------------------------------------------//

  using checkpoint_function_t = std::function<bool(std::string &)>;
  using restart_function_t = std::function<bool(std::string &)>;

  /*!
    Function types for registration interface and callbacks.
   */

  struct io_functions_t {
    checkpoint_function_t checkpoint;
    restart_function_t restart;
  }; // functions_t

  /*!
    Return the singleton instance of the interface__ type.
   */

  static interface__ & instance() {
    static interface__ _if;
    return _if;
  } // instance

  /*!
    Initialize the directory structure and required header information
    for a ristraio simulation.

    @param path The directory path to the location where the simulation
                structure should reside.
    @param name The name of the simulation. This sill be the name of the
                subdirectory of \ref path where the simulation files and
                directory strcuture will be created.

    @return This method returns true if the initialization is successful,
            false otherwise.
   */

  bool register_target(size_t key, io_functions_t & iofs) {
    
    targets_[key] = iofs;

    return true;
  } // register_target

  bool initialize_simulation(std::string path, std::string name) {
  } // initialize_simulation

private:

  std::map<size_t, io_functions_t> targets_;

}; // struct interface__

} // namespace io
} // namespace ristraio

// This include file defines the DRIVER_POLICY used below.

#include <ristraio/driver/ristraio_driver_policy.h>

namespace ristraio {
namespace io {
  
/*!
 */

using interface_t = interface__<RISTRAIO_DRIVER_POLICY>;

} // namespace io
} // namespace ristraio
