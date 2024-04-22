#pragma once

#include <limits>

namespace utils
{
  [[nodiscard]] constexpr INT_TYPE inf() noexcept { return std::numeric_limits<INT_TYPE>::max() / 2 - 1; }
} // namespace utils
