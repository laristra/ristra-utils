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

#include <tuple>

#include <ristra-utils/control/control.h>
#include <ristra-utils/utils/typeify.h>
#include <ristra-utils/control/test/node_type.h>

namespace ristra {
namespace control {
namespace test {

/*----------------------------------------------------------------------------*
 * Define simulation phases.
 *----------------------------------------------------------------------------*/

enum simulation_phases_t : size_t {
  initialize,
  advance,
  analyze,
  io,
  mesh,
  finalize
}; // enum simulation_phases_t

/*----------------------------------------------------------------------------*
 * Define action attributes.
 *----------------------------------------------------------------------------*/

enum action_attributes_t : size_t {
  time_advance_half = 0x01,
  time_advance_whole = 0x02,
  updated_eos_at_faces = 0x04
}; // enum action_attributes_t

/*----------------------------------------------------------------------------*
 * Control policy.
 *----------------------------------------------------------------------------*/

struct control_policy_t {

  using control_t = ristra::control::control__<control_policy_t>;

  using node_t = ristra::control::test::node_t;

  static bool evolve_control() {
    return control_t::instance().step()++ < 5;
  } // evolve

  #define phase(name) ristra::control::phase_<name>

  using evolve = ristra::control::cycle__<
    evolve_control, // stopping predicate
    phase(advance),
    phase(analyze),
    phase(io),
    phase(mesh)
  >;

  using phases = std::tuple<
    phase(initialize),
    evolve,
    phase(finalize)
  >;

  size_t & step() { return step_; }

private:

  size_t step_;

}; // struct control_policy_t

} // namespace test
} // namespace control
} // namespace ristra

using control_t =
  ristra::control::control__<ristra::control::test::control_policy_t>;
