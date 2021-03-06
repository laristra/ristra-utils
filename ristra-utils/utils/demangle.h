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
  Return the demangled name.

  @param name The string to demangle.

  @ingroup utils
 */

std::string demangle(const char * const name);

/*!
  Return the demangled name of the type T.

  @tparam T The type.

  @ingroup utils
 */

template<class T>
inline std::string
type() {
  return demangle(typeid(T).name());
} // type

/*!
  Return the demangled name of the type identified by type_info.

  @param std::type_info The type.

  @ingroup utils
 */

inline std::string
type(const std::type_info & type_info) {
  return demangle(type_info.name());
} // type

} // namespace utils
} // namespace ristra
