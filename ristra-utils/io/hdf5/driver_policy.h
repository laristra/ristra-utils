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
namespace io {

struct hdf5_driver_policy_t {

  bool initialize_simulation(std::string path, std::string name) {
    path_ = path;
    name_ = name;
    return true;
  } // initialize_simulation

  void add_simulation_parameter(record_t & record) {
  } // add_simulation_parameter

private:

  std::string path_;
  std::string name_;

}; // struct hdf5_driver_policy_t

} // namespace io
} // namespace ristra
