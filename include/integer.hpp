#pragma once

#include <limits>

namespace utils
{
  class integer final
  {
  public:
    static const integer zero;
    static const integer one;
    static const integer positive_infinite;
    static const integer negative_infinite;

    explicit integer(INT_TYPE val);
    explicit integer(INT_TYPE val, bool is_inf);

    [[nodiscard]] inline friend bool is_zero(const integer &rhs) noexcept { return !is_infinite(rhs) && rhs.val == 0; }
    [[nodiscard]] inline friend bool is_positive(const integer &rhs) noexcept { return rhs.val > 0; }
    [[nodiscard]] inline friend bool is_positive_or_zero(const integer &rhs) noexcept { return rhs.val >= 0; }
    [[nodiscard]] inline friend bool is_negative(const integer &rhs) noexcept { return rhs.val < 0; }
    [[nodiscard]] inline friend bool is_negative_or_zero(const integer &rhs) noexcept { return rhs.val <= 0; }
    [[nodiscard]] inline friend bool is_infinite(const integer &rhs) noexcept { return rhs.is_inf; }
    [[nodiscard]] inline friend bool is_positive_infinite(const integer &rhs) noexcept { return is_positive(rhs) && is_infinite(rhs); }
    [[nodiscard]] inline friend bool is_negative_infinite(const integer &rhs) noexcept { return is_negative(rhs) && is_infinite(rhs); }
    [[nodiscard]] inline friend INT_TYPE to_int(const integer &rhs) noexcept
    {
      if (rhs.is_inf)
        return rhs.val > 0 ? std::numeric_limits<INT_TYPE>::max() : std::numeric_limits<INT_TYPE>::min();
      return rhs.val;
    }

    [[nodiscard]] bool operator!=(const integer &rhs) const noexcept;
    [[nodiscard]] bool operator<(const integer &rhs) const noexcept;
    [[nodiscard]] bool operator<=(const integer &rhs) const noexcept;
    [[nodiscard]] bool operator==(const integer &rhs) const noexcept;
    [[nodiscard]] bool operator>=(const integer &rhs) const noexcept;
    [[nodiscard]] bool operator>(const integer &rhs) const noexcept;

    [[nodiscard]] bool operator!=(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator<(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator<=(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator==(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator>=(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator>(const INT_TYPE &rhs) const noexcept;

  private:
    INT_TYPE val;
    bool is_inf;
  };

  [[nodiscard]] constexpr INT_TYPE inf() noexcept { return std::numeric_limits<INT_TYPE>::max() / 2 - 1; }
} // namespace utils
