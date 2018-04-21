/*
           _____       _____              _____       
    __________(_)________  /_____________ ___(_)_____ 
    __  ___/_  /__  ___/  __/_  ___/  __ `/_  /_  __ \
    _  /   _  / _(__  )/ /_ _  /   / /_/ /_  / / /_/ /
    /_/    /_/  /____/ \__/ /_/    \__,_/ /_/  \____/ 

                                                                              */
#pragma once

/*! @file */

#include <ristraio-config.h>

//----------------------------------------------------------------------------//
// This section works with the build system to select the correct driver
// implemenation for the I/O model. If you add to the possible drivers,
// remember to edit config/packages.cmake to include a definition using
// the same convention, e.g., -DRISTRAIO_DRIVER_new_driver.
//----------------------------------------------------------------------------//

// HDF5 Policy
#if RISTRAIO_DRIVER == RISTRAIO_DRIVER_hdf5

#include <ristraio/io/hdf5/driver_policy.h>

namespace ristraio {
namespace io {

using RISTRAIO_DRIVER_POLICY = hdf5_driver_policy_t;

} // namespace io
} // namespace ristraio

#elif RISTRAIO_DRIVER == RISTRAIO_DRIVER_design

//----------------------------------------------------------------------------//
// THIS DRIVER IS INCLUDED TO AID IN INTERFACE DESIGN AND DEVELOPMENT. IT IS
// NOT A REAL DRIVER! THIS IS ONLY A PLACE HOLDER TO BE USED FOR TESTING!!!
// IF I CATCH ANYONE ACTUALLY TRYING TO USE THIS DRIVER, I WILL FLAY THE SKIN
// FROM YOUR BODY!!!
//----------------------------------------------------------------------------//

#include <ristraio/io/design/driver_policy.h>

namespace ristraio {
namespace io {

using RISTRAIO_DRIVER_POLICY = design_driver_policy_t;

} // namespace io
} // namespace ristraio

#endif
