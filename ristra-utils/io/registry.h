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

struct registry_t
{

  /*!
    The target_type_t allows coarse-grained sorting of I/O targets
    by type, in addition to the fine-grained key-based sorting that
    is the std::map default. Targets can be loosely sorted into types
    that then have a deterministic ordering because of the const_string_t
    hashing function.
   */

  enum target_type_t : size_t {
    simulation,
    topology,
    package,
    analysis
  }; // enum target_type_t

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

  bool register_target(target_type_t type, size_t key,
    io_functions_t const & iofs) {
    
    std::cout << "(type,key): " << type << " " << key << std::endl;
    targets_[std::make_pair(type, key)] = iofs;

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

  using target_key_t = std::pair<size_t, size_t>;

  /*
    This comparison operator will sort targets by increasing
    target_type_t, and then by hash key.
   */

  struct target_compare_t {
    bool operator () (target_key_t const & a, target_key_t const & b) const {

      return
        a.first < b.first ?
          true
        :
        a.first == b.first ?
          a.second < b.second
        :
          false;
        
    } // operator ()
  }; // struct target_compare_t

  std::map<target_key_t, io_functions_t, target_compare_t> targets_;

}; // struct registry_t

} // namespace io
} // namespace ristra
