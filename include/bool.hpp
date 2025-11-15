#pragma once

namespace utils
{
  using lbool = unsigned short int;
  constexpr lbool False = 0;
  constexpr lbool True = 1;
  constexpr lbool Undefined = 2;
} // namespace utils

[[nodiscard]] inline bool is_undefined(utils::lbool value) noexcept { return value == utils::Undefined; }
[[nodiscard]] inline bool is_false(utils::lbool value) noexcept { return value == utils::False; }
[[nodiscard]] inline bool is_true(utils::lbool value) noexcept { return value == utils::True; }
