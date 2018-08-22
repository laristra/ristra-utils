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

#include <bitset>
#include <functional>
#include <iostream>

namespace ristra {
namespace control {
namespace test {

struct node_t {

  using bitset_t = std::bitset<8>;
  using action_t = std::function<int(int, char **)>;

  node_t(action_t const & action = {}, bitset_t const & bitset = {})
    : action_(action), bitset_(bitset) {}

  bool initialize(node_t const & node) {
    action_ = node.action_;
    bitset_ = node.bitset_;
    return true;
  } // initialize

  action_t const & action() const { return action_; }
  action_t & action() { return action_; }

  bitset_t const & bitset() const { return bitset_; }
  bitset_t & bitset() { return bitset_; }

private:

  action_t action_;
  bitset_t bitset_;

}; // struct node_t

std::ostream &
operator << (std::ostream & stream, node_t const & node) {
  stream << "bitset: " << node.bitset() << std::endl;
  stream << "action: " << &node.action() << std::endl;
  return stream;
} // operator <<

} // namespace test
} // namespace control
} // namespace ristra
