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
    explicit lin() = default;

    /**
     * @brief Construct a new linear expression object with a known term.
     *
     * @param known_term known term.
     */
    explicit lin(const rational &known_term) : known_term(known_term) {}
    /**
     * @brief Construct a new linear expression object given the `v` variable and the `c` coefficient.
     *
     * @param v the variable of the linear expression.
     * @param c the coefficient of the `v` variable.
     */
    explicit lin(const VARIABLE_TYPE v, const rational &c) { vars.emplace(v, c); }

  public:
    [[nodiscard]] lin operator+(const lin &rhs) const noexcept;
    [[nodiscard]] lin operator+(const rational &rhs) const noexcept;
    [[nodiscard]] friend lin operator+(const rational &lhs, const lin &rhs) noexcept;

    [[nodiscard]] lin operator-(const lin &rhs) const noexcept;
    [[nodiscard]] lin operator-(const rational &rhs) const noexcept;
    [[nodiscard]] friend lin operator-(const rational &lhs, const lin &rhs) noexcept;

    [[nodiscard]] lin operator*(const rational &rhs) const noexcept;
    [[nodiscard]] friend lin operator*(const rational &lhs, const lin &rhs) noexcept;

    [[nodiscard]] lin operator/(const rational &rhs) const noexcept;

    lin &operator+=(const lin &rhs) noexcept;
    lin &operator+=(const rational &rhs) noexcept;

    lin &operator-=(const lin &rhs) noexcept;
    lin &operator-=(const rational &rhs) noexcept;

    lin &operator*=(const rational &rhs) noexcept;

    lin &operator/=(const rational &rhs) noexcept;

    [[nodiscard]] lin operator-() const noexcept;

    /**
     * @brief Substitute the variable `v` with the linear expression `rhs`.
     */
    [[nodiscard]] lin &substitute(const VARIABLE_TYPE v, const lin &rhs) noexcept;

    [[nodiscard]] friend std::string to_string(const lin &rhs) noexcept;

  public:
    std::map<const VARIABLE_TYPE, rational> vars;
    rational known_term;
  };
} // namespace utils
