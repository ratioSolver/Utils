#pragma once

#include <map>
#include "rational.hpp"

namespace utils
{
  /**
   * @brief Linear expression
   */
  class lin final
  {
  public:
    /**
     * @brief Construct a new linear expression object.
     */
    explicit constexpr lin() = default;

    /**
     * @brief Construct a new linear expression object with a known term.
     *
     * @param known_term known term.
     */
    explicit constexpr lin(const rational &known_term) : known_term(known_term) {}
    /**
     * @brief Construct a new linear expression object given the `v` variable and the `c` coefficient.
     *
     * @param v the variable of the linear expression.
     * @param c the coefficient of the `v` variable.
     */
    explicit constexpr lin(const VARIABLE_TYPE v, const rational &c) { vars.emplace(v, c); }

  public:
    [[nodiscard]] constexpr lin operator+(const lin &rhs) const noexcept;
    [[nodiscard]] constexpr lin operator+(const rational &rhs) const noexcept;
    friend constexpr lin operator+(const rational &lhs, const lin &rhs) noexcept;

    [[nodiscard]] constexpr lin operator-(const lin &rhs) const noexcept;
    [[nodiscard]] constexpr lin operator-(const rational &rhs) const noexcept;
    friend constexpr lin operator-(const rational &lhs, const lin &rhs) noexcept;

    [[nodiscard]] constexpr lin operator*(const rational &rhs) const noexcept;
    friend constexpr lin operator*(const rational &lhs, const lin &rhs) noexcept;

    [[nodiscard]] constexpr lin operator/(const rational &rhs) const noexcept;

    constexpr lin &operator+=(const lin &rhs) noexcept;
    constexpr lin &operator+=(const rational &rhs) noexcept;

    constexpr lin &operator-=(const lin &rhs) noexcept;
    constexpr lin &operator-=(const rational &rhs) noexcept;

    constexpr lin &operator*=(const rational &rhs) noexcept;

    constexpr lin &operator/=(const rational &rhs) noexcept;

    [[nodiscard]] constexpr lin operator-() const noexcept;

    /**
     * @brief Substitute the variable `v` with the linear expression `rhs`.
     */
    [[nodiscard]] constexpr lin &substitute(const VARIABLE_TYPE v, const lin &rhs) noexcept;

    friend std::string to_string(const lin &rhs) noexcept;

  public:
    std::map<const VARIABLE_TYPE, rational> vars;
    rational known_term;
  };
} // namespace utils
