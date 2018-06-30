/*
  _____________       _____              ____________
  ___  __ \__(_)________  /_____________ ___  /___  /
  __  /_/ /_  /__  ___/  __/_  ___/  __ `/_  / __  /
  _  _, _/_  / _(__  )/ /_ _  /   / /_/ /_  /___  /___
  /_/ |_| /_/  /____/ \__/ /_/    \__,_/ /_____/_____/

  Copyright (c) 2018 Los Alamos National Security, LLC
  All rights reserved.
                                                                              */

#include <cinchtest.h>

#include <ristrall/io/io.h>

//----------------------------------------------------------------------------//
// Create a type with components implemented as static methods.
//----------------------------------------------------------------------------//

struct test_target_t {

  static bool checkpoint(std::string & path) {
    std::cout << "test_target_t calling checkpoint with " << path << std::endl;
    return true;
  } // checkpoint

  static bool restart(std::string & path) {
    std::cout << "test_target_t calling restart with " << path << std::endl;
    return true;
  } // checkpoint

}; // struct test_target_t

//----------------------------------------------------------------------------//
// Implement components as functions.
//----------------------------------------------------------------------------//

bool untyped_checkpoint(std::string & path) {
    std::cout << "untyped_checkpoint with " << path << std::endl;
    return true;
} // untyped_checkpoint

bool untyped_restart(std::string & path) {
    std::cout << "untyped_restart with " << path << std::endl;
    return true;
} // untyped_checkpoint

using namespace ristrall::io;

//----------------------------------------------------------------------------//
// Register static method version.
//----------------------------------------------------------------------------//

ristra_register_io_target(topology, test_target,
  ristra_io_functions(
    test_target_t::checkpoint,
    test_target_t::restart
  )
);

//----------------------------------------------------------------------------//
// Register function version.
//----------------------------------------------------------------------------//

ristra_register_io_target(topology, untyped,
  ristra_io_functions(
    untyped_checkpoint,
    untyped_restart
  )
);

//----------------------------------------------------------------------------//
// Unit test demonstrating runtime call to components.
//----------------------------------------------------------------------------//

TEST(registry, sanity) {

  std::string path("/home/bergen/test");

  ristra_checkpoint(path);

  ristra_restart(path);

} // TEST
