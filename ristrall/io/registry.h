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

struct registry_t
{

  //--------------------------------------------------------------------------//
  // Define function types for I/O registry.
  //--------------------------------------------------------------------------//

  using checkpoint_function_t = std::function<bool(std::string &)>;
  using restart_function_t = std::function<bool(std::string &)>;

  /*!
    Function types for registration and callbacks.
   */

  struct io_functions_t {

    checkpoint_function_t checkpoint;
    restart_function_t restart;

    io_functions_t(
      checkpoint_function_t checkpoint_ = {},
      restart_function_t restart_ = {}
    )
      :
    checkpoint(checkpoint_),
    restart(restart_)
    {}

  }; // functions_t

  /*!
    Return the singleton instance of the registry_t type.
   */

  static registry_t & instance() {
    static registry_t _if;
    return _if;
  } // instance

  /*!
    Register an I/O target.

    @param key  The hash key for the target.
    @param iofs The set of callback functions for the target.
   */

  bool register_target(size_t key, io_functions_t const & iofs) {
    
    targets_[key] = iofs;

    return true;
  } // register_target

  /*!
    Checkpoint the simulation.

    @param path The path to the simulation directory.
   */

  bool checkpoint(std::string & path) {
    bool returns{true};

    for(auto target: targets_) {
      returns = returns && target.second.checkpoint(path);
    } // for

    return returns;
  } // checkpoint

  /*!
    Restart the simulation.

    @param path The path to the simulation directory.
   */

  bool restart(std::string & path) {
    bool returns{true};

    for(auto target: targets_) {
      returns = returns && target.second.restart(path);
    } // for

    return returns;
  } // restart

private:

  std::map<size_t, io_functions_t> targets_;

}; // struct registry_t

} // namespace io
} // namespace ristrall
