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

    explicit rational() noexcept;
    explicit rational(INTEGER_TYPE n) noexcept;
    explicit rational(INTEGER_TYPE n, INTEGER_TYPE d) noexcept;

    [[nodiscard]] INTEGER_TYPE numerator() const noexcept { return num; }
    [[nodiscard]] INTEGER_TYPE denominator() const noexcept { return den; }

    [[nodiscard]] inline friend bool is_integer(const rational &rhs) noexcept { return rhs.den == 1; }
    [[nodiscard]] inline friend bool is_zero(const rational &rhs) noexcept { return rhs.num == 0; }
    [[nodiscard]] inline friend bool is_positive(const rational &rhs) noexcept { return rhs.num > 0; }
    [[nodiscard]] inline friend bool is_positive_or_zero(const rational &rhs) noexcept { return rhs.num >= 0; }
    [[nodiscard]] inline friend bool is_negative(const rational &rhs) noexcept { return rhs.num < 0; }
    [[nodiscard]] inline friend bool is_negative_or_zero(const rational &rhs) noexcept { return rhs.num <= 0; }
    [[nodiscard]] inline friend bool is_infinite(const rational &rhs) noexcept { return rhs.den == 0; }
    [[nodiscard]] inline friend bool is_positive_infinite(const rational &rhs) noexcept { return is_positive(rhs) && is_infinite(rhs); }
    [[nodiscard]] inline friend bool is_negative_infinite(const rational &rhs) noexcept { return is_negative(rhs) && is_infinite(rhs); }
    [[nodiscard]] inline friend double to_double(const rational &rhs) noexcept { return static_cast<double>(rhs.num) / rhs.den; }

    [[nodiscard]] bool operator!=(const rational &rhs) const noexcept;
    [[nodiscard]] bool operator<(const rational &rhs) const noexcept;
    [[nodiscard]] bool operator<=(const rational &rhs) const noexcept;
    [[nodiscard]] bool operator==(const rational &rhs) const noexcept;
    [[nodiscard]] bool operator>=(const rational &rhs) const noexcept;
    [[nodiscard]] bool operator>(const rational &rhs) const noexcept;

    [[nodiscard]] bool operator!=(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator<(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator<=(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator==(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator>=(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator>(const INTEGER_TYPE &rhs) const noexcept;

    [[nodiscard]] rational operator+(const rational &rhs) const noexcept;
    [[nodiscard]] rational operator-(const rational &rhs) const noexcept;
    [[nodiscard]] rational operator*(const rational &rhs) const noexcept;
    [[nodiscard]] rational operator/(const rational &rhs) const noexcept;

    [[nodiscard]] rational operator+(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] rational operator-(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] rational operator*(const INTEGER_TYPE &rhs) const noexcept;
    [[nodiscard]] rational operator/(const INTEGER_TYPE &rhs) const noexcept;

    rational &operator+=(const rational &rhs) noexcept;
    rational &operator-=(const rational &rhs) noexcept;
    rational &operator*=(const rational &rhs) noexcept;
    rational &operator/=(const rational &rhs) noexcept;

    rational &operator+=(const INTEGER_TYPE &rhs) noexcept;
    rational &operator-=(const INTEGER_TYPE &rhs) noexcept;
    rational &operator*=(const INTEGER_TYPE &rhs) noexcept;
    rational &operator/=(const INTEGER_TYPE &rhs) noexcept;

    friend rational operator+(const INTEGER_TYPE &lhs, const rational &rhs) noexcept;
    friend rational operator-(const INTEGER_TYPE &lhs, const rational &rhs) noexcept;
    friend rational operator*(const INTEGER_TYPE &lhs, const rational &rhs) noexcept;
    friend rational operator/(const INTEGER_TYPE &lhs, const rational &rhs) noexcept;

    [[nodiscard]] rational operator-() const noexcept;

  private:
    void normalize() noexcept;

    friend std::string to_string(const rational &rhs) noexcept;

  private:
    INTEGER_TYPE num; // the numerator..
    INTEGER_TYPE den; // the denominator..
  };
} // namespace utils