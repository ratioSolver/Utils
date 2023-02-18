#pragma once

#include <limits>

namespace utils
{
#ifdef INTEGER_TYPE_INT
  using I = int;
#endif
#ifdef INTEGER_TYPE_LONG
  using I = long;
#endif
#ifdef INTEGER_TYPE_LONG_LONG
  using I = long long;
#endif

  constexpr I inf() noexcept
  {
    return std::numeric_limits<I>::max() / 2 - 1;
  }
} // namespace utils
