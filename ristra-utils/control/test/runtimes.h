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

#include <ristra-utils/control/runtime.h>

#include <iostream>

using namespace ristra::control;

inline int initialize(int argc, char ** argv) {
  std::cout << "Executing initialize" << std::endl;
  return 0;
} // initialize

inline int finalize(int argc, char ** argv, runtime_exit_mode_t mode) {
  std::cout << "Executing finalize with mode " << size_t{mode} << std::endl;
  return 0;
} // initialize

inline bool output(int argc, char ** argv) {
  std::cout << "Executing output" << std::endl;
  return true;
} // output

inline runtime_handler_t handler{ initialize, finalize, output };

ristra_append_runtime_handler(handler);

inline int runtime_test_runtime_driver(int argc, char ** argv) {
  std::cout << "Executing runtime driver" << std::endl;
  return 0;
} // runtime_test_runtime_driver

ristra_register_runtime_driver(runtime_test_runtime_driver);
