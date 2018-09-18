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
