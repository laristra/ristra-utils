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
namespace utils {

/*!
  Create a C++ type from a non-type value, e.g., an integer literal.

  @tparam T The literal type.
  @tparam M The literal value.

  @ingroup utils
 */

template<typename T, T M>
struct typeify__ {
  using TYPE = T;
  static constexpr T value = M;
};

template<typename T, T M>
constexpr T typeify__<T, M>::value;

} // namespace utils
} // namespace ristra
