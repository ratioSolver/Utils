#pragma once

#include "utils_export.h"
#include "integer.h"
#include <string>

namespace utils
{
  class rational final
  {
  public:
    UTILS_EXPORT static const rational ZERO;
    UTILS_EXPORT static const rational ONE;
    UTILS_EXPORT static const rational POSITIVE_INFINITY;
    UTILS_EXPORT static const rational NEGATIVE_INFINITY;

    UTILS_EXPORT explicit rational();
    UTILS_EXPORT explicit rational(I n);
    UTILS_EXPORT explicit rational(I n, I d);

    inline I numerator() const noexcept { return num; }
    inline I denominator() const noexcept { return den; }

    inline friend bool is_integer(const rational &rhs) noexcept { return rhs.den == 1; }
    inline friend bool is_zero(const rational &rhs) noexcept { return rhs.num == 0; }
    inline friend bool is_positive(const rational &rhs) noexcept { return rhs.num > 0; }
    inline friend bool is_positive_or_zero(const rational &rhs) noexcept { return rhs.num >= 0; }
    inline friend bool is_negative(const rational &rhs) noexcept { return rhs.num < 0; }
    inline friend bool is_negative_or_zero(const rational &rhs) noexcept { return rhs.num <= 0; }
    inline friend bool is_infinite(const rational &rhs) noexcept { return rhs.den == 0; }
    inline friend bool is_positive_infinite(const rational &rhs) noexcept { return is_positive(rhs) && is_infinite(rhs); }
    inline friend bool is_negative_infinite(const rational &rhs) noexcept { return is_negative(rhs) && is_infinite(rhs); }
    inline friend double to_double(const rational &rhs) noexcept { return static_cast<double>(rhs.num) / rhs.den; }

    UTILS_EXPORT bool operator!=(const rational &rhs) const noexcept;
    UTILS_EXPORT bool operator<(const rational &rhs) const noexcept;
    UTILS_EXPORT bool operator<=(const rational &rhs) const noexcept;
    UTILS_EXPORT bool operator==(const rational &rhs) const noexcept;
    UTILS_EXPORT bool operator>=(const rational &rhs) const noexcept;
    UTILS_EXPORT bool operator>(const rational &rhs) const noexcept;

    UTILS_EXPORT bool operator!=(const I &rhs) const noexcept;
    UTILS_EXPORT bool operator<(const I &rhs) const noexcept;
    UTILS_EXPORT bool operator<=(const I &rhs) const noexcept;
    UTILS_EXPORT bool operator==(const I &rhs) const noexcept;
    UTILS_EXPORT bool operator>=(const I &rhs) const noexcept;
    UTILS_EXPORT bool operator>(const I &rhs) const noexcept;

    UTILS_EXPORT rational operator+(const rational &rhs) const noexcept;
    UTILS_EXPORT rational operator-(const rational &rhs) const noexcept;
    UTILS_EXPORT rational operator*(const rational &rhs) const noexcept;
    UTILS_EXPORT rational operator/(const rational &rhs) const noexcept;

    UTILS_EXPORT rational operator+(const I &rhs) const noexcept;
    UTILS_EXPORT rational operator-(const I &rhs) const noexcept;
    UTILS_EXPORT rational operator*(const I &rhs) const noexcept;
    UTILS_EXPORT rational operator/(const I &rhs) const noexcept;

    UTILS_EXPORT rational &operator+=(const rational &rhs) noexcept;
    UTILS_EXPORT rational &operator-=(const rational &rhs) noexcept;
    UTILS_EXPORT rational &operator*=(const rational &rhs) noexcept;
    UTILS_EXPORT rational &operator/=(const rational &rhs) noexcept;

    UTILS_EXPORT rational &operator+=(const I &rhs) noexcept;
    UTILS_EXPORT rational &operator-=(const I &rhs) noexcept;
    UTILS_EXPORT rational &operator*=(const I &rhs) noexcept;
    UTILS_EXPORT rational &operator/=(const I &rhs) noexcept;

    UTILS_EXPORT friend rational operator+(const I &lhs, const rational &rhs) noexcept;
    UTILS_EXPORT friend rational operator-(const I &lhs, const rational &rhs) noexcept;
    UTILS_EXPORT friend rational operator*(const I &lhs, const rational &rhs) noexcept;
    UTILS_EXPORT friend rational operator/(const I &lhs, const rational &rhs) noexcept;

    UTILS_EXPORT rational operator-() const noexcept;

  private:
    void normalize() noexcept;

    friend UTILS_EXPORT std::string to_string(const rational &rhs) noexcept;

  private:
    I num; // the numerator..
    I den; // the denominator..
  };
} // namespace utils