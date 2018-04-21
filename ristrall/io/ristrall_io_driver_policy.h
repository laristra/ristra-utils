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

#include <ristrall-config.h>

//----------------------------------------------------------------------------//
// This section works with the build system to select the correct driver
// implemenation for the I/O model. If you add to the possible drivers,
// remember to edit config/packages.cmake to include a definition using
// the same convention, e.g., -DRISTRALL_IO_DRIVER_new_driver.
//----------------------------------------------------------------------------//

// HDF5 Policy
#if RISTRALL_IO_DRIVER == RISTRALL_IO_DRIVER_hdf5

#include <ristrall/io/hdf5/driver_policy.h>

namespace ristrall {
namespace io {

using RISTRALL_IO_DRIVER_POLICY = hdf5_driver_policy_t;

} // namespace io
} // namespace ristrall

#elif RISTRALL_IO_DRIVER == RISTRALL_IO_DRIVER_design

//----------------------------------------------------------------------------//
// THIS DRIVER IS INCLUDED TO AID IN INTERFACE DESIGN AND DEVELOPMENT. IT IS
// NOT A REAL DRIVER! THIS IS ONLY A PLACE HOLDER TO BE USED FOR TESTING!!!
// IF I CATCH ANYONE ACTUALLY TRYING TO USE THIS DRIVER, I WILL FLAY THE SKIN
// FROM THEIR BODY!!!
//----------------------------------------------------------------------------//

#include <ristrall/io/design/driver_policy.h>

namespace ristrall {
namespace io {

using RISTRALL_IO_DRIVER_POLICY = design_driver_policy_t;

} // namespace io
} // namespace ristrall

#endif
