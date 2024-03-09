#pragma once

#include <string>

namespace utils
{
  class rational final
  {
  public:
    static const rational zero;
    static const rational one;
    static const rational positive_infinite;
    static const rational negative_infinite;

    constexpr explicit rational() noexcept;
    constexpr explicit rational(INTEGER_TYPE n) noexcept;
    constexpr explicit rational(INTEGER_TYPE n, INTEGER_TYPE d) noexcept;

    [[nodiscard]] constexpr INTEGER_TYPE numerator() const noexcept { return num; }
    [[nodiscard]] constexpr INTEGER_TYPE denominator() const noexcept { return den; }

    [[nodiscard]] inline friend constexpr bool is_integer(const rational &rhs) noexcept { return rhs.den == 1; }
    [[nodiscard]] inline friend constexpr bool is_zero(const rational &rhs) noexcept { return rhs.num == 0; }
    [[nodiscard]] inline friend constexpr bool is_positive(const rational &rhs) noexcept { return rhs.num > 0; }
    [[nodiscard]] inline friend constexpr bool is_positive_or_zero(const rational &rhs) noexcept { return rhs.num >= 0; }
    [[nodiscard]] inline friend constexpr bool is_negative(const rational &rhs) noexcept { return rhs.num < 0; }
    [[nodiscard]] inline friend constexpr bool is_negative_or_zero(const rational &rhs) noexcept { return rhs.num <= 0; }
    [[nodiscard]] inline friend constexpr bool is_infinite(const rational &rhs) noexcept { return rhs.den == 0; }
    [[nodiscard]] inline friend constexpr bool is_positive_infinite(const rational &rhs) noexcept { return is_positive(rhs) && is_infinite(rhs); }
    [[nodiscard]] inline friend constexpr bool is_negative_infinite(const rational &rhs) noexcept { return is_negative(rhs) && is_infinite(rhs); }
    [[nodiscard]] inline friend constexpr double to_double(const rational &rhs) noexcept { return static_cast<double>(rhs.num) / rhs.den; }

    [[nodiscard]] constexpr bool operator!=(const rational &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator<(const rational &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator<=(const rational &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator==(const rational &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator>=(const rational &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator>(const rational &rhs) const noexcept;

    [[nodiscard]] constexpr bool operator!=(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator<(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator<=(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator==(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator>=(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] constexpr bool operator>(const INTEGER_TYPE &rhs) const noexcept;

    [[nodiscard]] constexpr rational operator+(const rational &rhs) const noexcept;
    [[nodiscard]] constexpr rational operator-(const rational &rhs) const noexcept;
    [[nodiscard]] constexpr rational operator*(const rational &rhs) const noexcept;
    [[nodiscard]] constexpr rational operator/(const rational &rhs) const noexcept;

    [[nodiscard]] constexpr rational operator+(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] constexpr rational operator-(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] constexpr rational operator*(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] constexpr rational operator/(const INTEGER_TYPE &rhs) const noexcept;

    constexpr rational &operator+=(const rational &rhs) noexcept;
    constexpr rational &operator-=(const rational &rhs) noexcept;
    constexpr rational &operator*=(const rational &rhs) noexcept;
    constexpr rational &operator/=(const rational &rhs) noexcept;

    constexpr rational &operator+=(const INTEGER_TYPE &rhs) noexcept;
    constexpr rational &operator-=(const INTEGER_TYPE &rhs) noexcept;
    constexpr rational &operator*=(const INTEGER_TYPE &rhs) noexcept;
    constexpr rational &operator/=(const INTEGER_TYPE &rhs) noexcept;

    friend constexpr rational operator+(const INTEGER_TYPE &lhs, const rational &rhs) noexcept;
    friend constexpr rational operator-(const INTEGER_TYPE &lhs, const rational &rhs) noexcept;
    friend constexpr rational operator*(const INTEGER_TYPE &lhs, const rational &rhs) noexcept;
    friend constexpr rational operator/(const INTEGER_TYPE &lhs, const rational &rhs) noexcept;

    [[nodiscard]] constexpr rational operator-() const noexcept;

  private:
    void normalize() noexcept;

    friend std::string to_string(const rational &rhs) noexcept;

  private:
    INTEGER_TYPE num; // the numerator..
    INTEGER_TYPE den; // the denominator..
  };

  constexpr rational rational::zero(0);
  constexpr rational rational::one(1);
  constexpr rational rational::negative_infinite(-1, 0);
  constexpr rational rational::positive_infinite(1, 0);
} // namespace utils