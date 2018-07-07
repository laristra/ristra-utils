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

#include <cstddef>
#include <utility>

namespace ristra {
namespace utils {

//----------------------------------------------------------------------------//
//----------------------------------------------------------------------------//

template<typename T, typename U>
constexpr T
string_hash__(U && str, const T h, const std::size_t i, const std::size_t n) {
  // An unstated assumption appears to be that n is the length of str, which is
  // a string type, and that i <= n. Otherwise, we're going to have problems.
  return i == n
    ? h
      : string_hash__(
        str,
        h ^ static_cast<T>(std::forward<U>(str)[i]) << 8 * (i % 8),
        i + 1, n);
} // string_hash__

template<typename T, typename U>
constexpr T
string_hash(U && str, const std::size_t n) {
  return string_hash__<T>(str, 0, 0, n);
} // string_hash

} // namespace utils
} // namespace ristra
