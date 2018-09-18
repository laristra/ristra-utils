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
  Type to define runtime initialization and finalization handlers.
 */

struct runtime_handler_t {
  std::function<int(int, char **)> initialize;
  std::function<int(int, char **, runtime_exit_mode_t)> finalize;
  std::function<bool(int, char **)> output;
}; // struct runtime_handler_t

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
    Append the given runtime handler to the vector of handlers. Handlers
    will be executed in the order in which they are appended.
   */
  bool append_runtime_handler(runtime_handler_t const & handler) {
    handlers_.push_back(handler);
    return true;
  } // register_runtime_handler

  /*!
    Access the runtime handler vector.
   */

  std::vector<runtime_handler_t> & runtimes() {
    return handlers_;
  } // runtimes

  /*!
    Invoke runtime intiailzation callbacks.
   */

  void initialize_runtimes(int argc, char ** argv) {
    for(auto r: handlers_) {
      r.initialize(argc, argv);
    } // for
  } // initialize_runtimes

  /*!
    Invoke runtime finalization callbacks.
   */

  int finalize_runtimes(int argc, char ** argv, runtime_exit_mode_t mode) {
    int result{0};

    for(auto r: handlers_) {
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

    for(auto r: handlers_) {
      result = r.output(argc, argv) ? result : false;
    } // for

    return result;
  } // participate_in_output

private:

  // FIXME: Make the singleton safe.
  runtime_t() {}

  std::string program_;
  std::function<int(int, char **)> driver_;
  std::vector<runtime_handler_t> handlers_;

}; // runtime_t

} // namespace ristra
} // namespace control

/*!
  @def ristra_register_runtime_driver(driver)

  Register the primary runtime driver function.

  @param driver The primary driver with a 'int(int, char **)' signature
                that should be invoked by the Ristra runtime.
 */

#define ristra_register_runtime_driver(driver)                                 \
  /* MACRO IMPLEMENTATION */                                                   \
                                                                               \
  inline bool ristra_registered_driver_##driver =                              \
    ristra::control::runtime_t::instance().register_driver(driver)

/*!
  @def ristra_register_runtime_handler(handler)

  Register a runtime handler with the Ristra runtime. Runtime handlers
  are invoked at fixed control points in the Ristra control model for
  initialization, finalization, and output participation. The finalization
  function has an additional argument that specifies the exit mode.

  @param handler A runtime_handler_t that references the appropriate
                 initialize, finalize, and output functions.                
 */

#define ristra_append_runtime_handler(handler)                                 \
  /* MACRO DEFINITION */                                                       \
                                                                               \
  inline bool ristra_append_runtime_handler_##handler =                        \
    ristra::control::runtime_t::instance().append_runtime_handler(handler)
