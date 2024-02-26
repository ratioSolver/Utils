#pragma once

#include <limits>

namespace utils
{
  [[nodiscard]] constexpr INTEGER_TYPE inf() noexcept { return std::numeric_limits<INTEGER_TYPE>::max() / 2 - 1; }
} // namespace utils
