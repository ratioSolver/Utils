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
    explicit constexpr lit(std::size_t v = std::numeric_limits<std::size_t>::max(), bool sign = true) : x((v << 1) + sign) {}

    /**
     * @brief Get the variable of the literal.
     *
     * @param p The literal.
     * @return var The variable of the literal.
     */
    inline friend constexpr std::size_t variable(const lit &p) noexcept { return p.x >> 1; }
    /**
     * @brief Get the sign of the literal.
     *
     * @param p The literal.
     * @return bool The sign of the literal.
     */
    [[nodiscard]] inline friend constexpr bool sign(const lit &p) noexcept { return p.x & 1; }

    [[nodiscard]] inline friend constexpr size_t index(const lit &p) noexcept { return p.x; }
    [[nodiscard]] inline friend constexpr bool is_undefined(const lit &p) noexcept { return p.x == std::numeric_limits<std::size_t>::max(); }

    [[nodiscard]] inline constexpr lit operator!() const
    {
      lit p;
      p.x = x ^ 1;
      return p;
    }
    [[nodiscard]] inline constexpr bool operator<(const lit &rhs) const noexcept { return x < rhs.x; }
    [[nodiscard]] inline constexpr bool operator==(const lit &rhs) const noexcept { return x == rhs.x; }
    [[nodiscard]] inline constexpr bool operator!=(const lit &rhs) const noexcept { return x != rhs.x; }

    friend std::string to_string(const lit &p) noexcept { return sign(p) ? ("b" + std::to_string(variable(p))) : ("¬b" + std::to_string(variable(p))); }

  private:
    std::size_t x;
  };

  constexpr std::size_t FALSE_var = 0;
  constexpr lit FALSE_lit(FALSE_var);
  constexpr lit TRUE_lit = !FALSE_lit;
} // namespace utils