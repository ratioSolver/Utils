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
    explicit rational(INT_TYPE n) noexcept;
    explicit rational(INT_TYPE n, INT_TYPE d) noexcept;

    [[nodiscard]] INT_TYPE numerator() const noexcept { return num; }
    [[nodiscard]] INT_TYPE denominator() const noexcept { return den; }

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

    [[nodiscard]] bool operator!=(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator<(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator<=(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator==(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator>=(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] bool operator>(const INT_TYPE &rhs) const noexcept;

    [[nodiscard]] rational operator+(const rational &rhs) const noexcept;
    [[nodiscard]] rational operator-(const rational &rhs) const noexcept;
    [[nodiscard]] rational operator*(const rational &rhs) const noexcept;
    [[nodiscard]] rational operator/(const rational &rhs) const noexcept;

    [[nodiscard]] rational operator+(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] rational operator-(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] rational operator*(const INT_TYPE &rhs) const noexcept;
    [[nodiscard]] rational operator/(const INT_TYPE &rhs) const noexcept;

    rational &operator+=(const rational &rhs) noexcept;
    rational &operator-=(const rational &rhs) noexcept;
    rational &operator*=(const rational &rhs) noexcept;
    rational &operator/=(const rational &rhs) noexcept;

    rational &operator+=(const INT_TYPE &rhs) noexcept;
    rational &operator-=(const INT_TYPE &rhs) noexcept;
    rational &operator*=(const INT_TYPE &rhs) noexcept;
    rational &operator/=(const INT_TYPE &rhs) noexcept;

    [[nodiscard]] friend rational operator+(const INT_TYPE &lhs, const rational &rhs) noexcept;
    [[nodiscard]] friend rational operator-(const INT_TYPE &lhs, const rational &rhs) noexcept;
    [[nodiscard]] friend rational operator*(const INT_TYPE &lhs, const rational &rhs) noexcept;
    [[nodiscard]] friend rational operator/(const INT_TYPE &lhs, const rational &rhs) noexcept;

    [[nodiscard]] friend bool operator!=(const INT_TYPE &lhs, const rational &rhs) noexcept;
    [[nodiscard]] friend bool operator<(const INT_TYPE &lhs, const rational &rhs) noexcept;
    [[nodiscard]] friend bool operator<=(const INT_TYPE &lhs, const rational &rhs) noexcept;
    [[nodiscard]] friend bool operator==(const INT_TYPE &lhs, const rational &rhs) noexcept;
    [[nodiscard]] friend bool operator>=(const INT_TYPE &lhs, const rational &rhs) noexcept;
    [[nodiscard]] friend bool operator>(const INT_TYPE &lhs, const rational &rhs) noexcept;

    [[nodiscard]] rational operator-() const noexcept;

    /**
     * @brief Computes the floor value of the given rational number.
     *
     * This function returns the largest integer value that is less than or equal to the given rational number.
     *
     * @param rhs The rational number for which the floor value is to be computed.
     * @return INT_TYPE The floor value of the given rational number.
     */
    [[nodiscard]] friend INT_TYPE floor(const rational &rhs) noexcept;
    /**
     * @brief Computes the ceiling value of the given rational number.
     *
     * This function returns the smallest integer value that is greater than or equal to the given rational number.
     *
     * @param rhs The rational number for which the ceiling value is to be computed.
     * @return INT_TYPE The ceiling value of the given rational number.
     */
    [[nodiscard]] friend INT_TYPE ceil(const rational &rhs) noexcept;

  private:
    void normalize() noexcept;

    friend std::string to_string(const rational &rhs) noexcept;

  private:
    INT_TYPE num; // the numerator..
    INT_TYPE den; // the denominator..
  };
} // namespace utils