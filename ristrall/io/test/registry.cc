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

struct test_target_t {

  static bool checkpoint(std::string & path) {
    std::cout << "test_target_t calling checkpoint with " << path << std::endl;
  } // checkpoint

  static bool restart(std::string & path) {
    std::cout << "test_target_t calling restart with " << path << std::endl;
  } // checkpoint

}; // struct test_target_t

using namespace ristrall::io;

ristra_register_io_target(test_target,
  ristra_io_functions(
    test_target_t::checkpoint,
    test_target_t::restart
  )
);

TEST(registry, sanity) {

  std::string path("/home/bergen/test");

  ristra_checkpoint(path);

  ristra_restart(path);

} // TEST
