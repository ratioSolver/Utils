#pragma once

#include <limits>
#include <string>

namespace utils
{
  /**
   * This class is used for representing propositional literals.
   */
  class lit
  {
  public:
    explicit constexpr lit(VARIABLE_TYPE v = std::numeric_limits<VARIABLE_TYPE>::max(), bool sign = true) : x((v << 1) + sign) {}

    /**
     * @brief Get the variable of the literal.
     *
     * @param p The literal.
     * @return var The variable of the literal.
     */
    inline friend constexpr VARIABLE_TYPE variable(const lit &p) noexcept { return p.x >> 1; }
    /**
     * @brief Get the sign of the literal.
     *
     * @param p The literal.
     * @return bool The sign of the literal.
     */
    inline friend constexpr bool sign(const lit &p) noexcept { return p.x & 1; }

    inline friend constexpr size_t index(const lit &p) noexcept { return p.x; }
    inline friend constexpr bool is_undefined(const lit &p) noexcept { return p.x == std::numeric_limits<VARIABLE_TYPE>::max(); }

    inline constexpr lit operator!() const
    {
      lit p;
      p.x = x ^ 1;
      return p;
    }
    inline constexpr bool operator<(const lit &rhs) const noexcept { return x < rhs.x; }
    inline constexpr bool operator==(const lit &rhs) const noexcept { return x == rhs.x; }
    inline constexpr bool operator!=(const lit &rhs) const noexcept { return x != rhs.x; }

    friend std::string to_string(const lit &p) noexcept { return sign(p) ? ("b" + std::to_string(variable(p))) : ("¬b" + std::to_string(variable(p))); }

  private:
    VARIABLE_TYPE x;
  };

  constexpr VARIABLE_TYPE FALSE_var = 0;
  constexpr lit FALSE_lit(FALSE_var);
  constexpr lit TRUE_lit = !FALSE_lit;
} // namespace utils