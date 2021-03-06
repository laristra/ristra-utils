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

template<typename T>
struct function_traits__ : function_traits__<decltype(&T::operator())> {};

template<typename R, typename... As>
struct function_traits__<R(As...)> {
  using return_type = R;
  using arguments_type = std::tuple<As...>;
};

template<typename R, typename... As>
struct function_traits__<R (*)(As...)> : public function_traits__<R(As...)> {};

template<typename C, typename R, typename... As>
struct function_traits__<R (C::*)(As...)> : public function_traits__<R(As...)> {
  using owner_type = C;
};

template<typename C, typename R, typename... As>
struct function_traits__<R (C::*)(As...) const>
    : public function_traits__<R(As...)> {
  using owner_type = C;
};

template<typename C, typename R, typename... As>
struct function_traits__<R (C::*)(As...) volatile>
    : public function_traits__<R(As...)> {
  using owner_type = C;
};

template<typename C, typename R, typename... As>
struct function_traits__<R (C::*)(As...) const volatile>
    : public function_traits__<R(As...)> {
  using owner_type = C;
};

template<typename R, typename... As>
struct function_traits__<std::function<R(As...)>>
    : public function_traits__<R(As...)> {};

template<typename T>
struct function_traits__<T &> : public function_traits__<T> {};
template<typename T>
struct function_traits__<const T &> : public function_traits__<T> {};
template<typename T>
struct function_traits__<volatile T &> : public function_traits__<T> {};
template<typename T>
struct function_traits__<const volatile T &> : public function_traits__<T> {};
template<typename T>
struct function_traits__<T &&> : public function_traits__<T> {};
template<typename T>
struct function_traits__<const T &&> : public function_traits__<T> {};
template<typename T>
struct function_traits__<volatile T &&> : public function_traits__<T> {};
template<typename T>
struct function_traits__<const volatile T &&> : public function_traits__<T> {};

} // namespace utils
} // namespace ristra
