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

#include <ristra-utils-config.h>

//----------------------------------------------------------------------------//
// This section works with the build system to select the correct driver
// implemenation for the I/O model. If you add to the possible drivers,
// remember to edit config/packages.cmake to include a definition using
// the same convention, e.g., -DRISTRAUTILS_IO_DRIVER_new_driver.
//----------------------------------------------------------------------------//

// HDF5 Policy
#if RISTRAUTILS_IO_DRIVER == RISTRAUTILS_IO_DRIVER_hdf5

#include <ristra-utils/io/hdf5/driver_policy.h>

namespace ristra {
namespace io {

using RISTRAUTILS_IO_DRIVER_POLICY = hdf5_driver_policy_t;

} // namespace io
} // namespace ristra

#elif RISTRAUTILS_IO_DRIVER == RISTRAUTILS_IO_DRIVER_design

//----------------------------------------------------------------------------//
// THIS DRIVER IS INCLUDED TO AID IN INTERFACE DESIGN AND DEVELOPMENT. IT IS
// NOT A REAL DRIVER! THIS IS ONLY A PLACE HOLDER TO BE USED FOR TESTING!!!
// IF I CATCH ANYONE ACTUALLY TRYING TO USE THIS DRIVER, I WILL FLAY THE SKIN
// FROM THEIR BODY!!!
//----------------------------------------------------------------------------//

#include <ristra-utils/io/design/driver_policy.h>

namespace ristra {
namespace io {

using RISTRAUTILS_IO_DRIVER_POLICY = design_driver_policy_t;

} // namespace io
} // namespace ristra

#endif
