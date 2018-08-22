/*
   _____________       _____              _____  _________________
   ___  __ \__(_)________  /_____________ __  / / /_  /___(_)__  /_______
   __  /_/ /_  /__  ___/  __/_  ___/  __ `/  / / /_  __/_  /__  /__  ___/
   _  _, _/_  / _(__  )/ /_ _  /   / /_/ // /_/ / / /_ _  / _  / _(__  )
   /_/ |_| /_/  /____/ \__/ /_/    \__,_/ \____/  \__/ /_/  /_/  /____/

   Copyright (c) 2016, Los Alamos National Security, LLC
   All rights reserved.
                                                                              */
#pragma once

/*! @file */

#include <functional>
#include <string>
#include <vector>

namespace ristra {
namespace control {

enum runtime_exit_mode_t : size_t {
  success,
  unrecognized_option,
  help
}; // enum runtime_exit_mode_t

/*!
 */

struct runtime_t {

  static runtime_t & instance() {
    static runtime_t r;
    return r;
  } // instance

  std::string const & program() const { return program_; }
  std::string & program() { return program_; }

  bool register_driver(std::function<int(int, char **)> const & driver) {
    driver_ = driver;
    return true;
  } // register_driver

  std::function<int(int, char **)> const & driver() const {
    return driver_;
  } // driver

  /*!
    Type to define runtime initialization and finalization handlers.
   */

  struct runtime_handler_t {
    std::function<int(int, char **)> initialize;
    std::function<int(int, char **, runtime_exit_mode_t)> finalize;
    std::function<bool(int, char **)> output;
  }; // struct runtime_handler_t

  /*!
    Access the runtime handler vector.
   */

  std::vector<runtime_handler_t> & runtimes() {
    return runtimes_;
  } // runtimes

  /*!
    Invoke runtime intiailzation callbacks.
   */

  void initialize_runtimes(int argc, char ** argv) {
    for(auto r: runtimes_) {
      r.initialize(argc, argv);
    } // for
  } // initialize_runtimes

  /*!
    Invoke runtime finalization callbacks.
   */

  int finalize_runtimes(int argc, char ** argv, runtime_exit_mode_t mode) {
    int result{0};

    for(auto r: runtimes_) {
      result |= r.finalize(argc, argv, mode);
    } // for

    return result;
  } // finalize_runtimes

  /*!
    Return a boolean value indicating whether or not this runtime instance
    should participate in output.
   */

  bool participate_in_output(int argc, char ** argv) {
    bool result{true};

    for(auto r: runtimes_) {
      result = r.output(argc, argv) ? result : false;
    } // for

    return result;
  } // participate_in_output

private:

  std::string program_;
  std::function<int(int, char **)> driver_;
  std::vector<runtime_handler_t> runtimes_;

}; // runtime_t

} // namespace ristra
} // namespace control
