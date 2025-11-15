#pragma once

#include <map>
#include "rational.hpp"

namespace utils
{
  using var = std::size_t;

  /**
   * @brief Linear expression
   */
  class lin final
  {
  public:
    /**
     * @brief Construct a new linear expression object.
     */
    lin() = default;

    /**
     * @brief Construct a new linear expression object with a known term.
     *
     * @param n known term as an integer.
     */
    lin(INT_TYPE n) : known_term(n) {}
    /**
     * @brief Construct a new linear expression object with a known term.
     *
     * @param known_term known term.
     */
    lin(const rational &known_term) : known_term(known_term) {}
    /**
     * @brief Construct a new linear expression object given the `v` variable and the `c` coefficient.
     *
     * @param v the variable of the linear expression.
     * @param c the coefficient of the `v` variable.
     */
    lin(const var v, const rational &c) { vars.emplace(v, c); }
    /**
     * @brief Construct a new linear expression object from an initializer list of variable-coefficient pairs and an optional known term.
     *
     * @param init An initializer list of pairs, where each pair consists of a variable and its corresponding coefficient.
     * @param known_term An optional known term for the linear expression (default is zero).
     */
    lin(std::initializer_list<std::pair<const var, rational>> init, const rational &known_term = rational::zero) : vars(init), known_term(known_term) {}

  public:
    [[nodiscard]] lin operator+(const lin &rhs) const noexcept;
    [[nodiscard]] lin operator+(const rational &rhs) const noexcept;
    friend lin operator+(const rational &lhs, const lin &rhs) noexcept;

    [[nodiscard]] lin operator-(const lin &rhs) const noexcept;
    [[nodiscard]] lin operator-(const rational &rhs) const noexcept;
    friend lin operator-(const rational &lhs, const lin &rhs) noexcept;

    [[nodiscard]] lin operator*(const rational &rhs) const noexcept;
    friend lin operator*(const rational &lhs, const lin &rhs) noexcept;

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
    [[nodiscard]] lin &substitute(const var v, const lin &rhs) noexcept;

    friend std::string to_string(const lin &rhs) noexcept;

  public:
    std::map<const var, rational> vars;
    rational known_term;
  };

  [[nodiscard]] std::string to_string(const lin &rhs) noexcept;
} // namespace utils
