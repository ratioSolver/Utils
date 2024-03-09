#pragma once

#include "rational.hpp"

namespace utils
{
  class inf_rational
  {
  public:
    constexpr explicit inf_rational() = default;
    constexpr explicit inf_rational(INTEGER_TYPE nun) : rat(nun) {}
    constexpr explicit inf_rational(const rational &rat) : rat(rat) {}
    constexpr explicit inf_rational(INTEGER_TYPE nun, INTEGER_TYPE den) : rat(nun, den) {}
    constexpr explicit inf_rational(const rational &rat, INTEGER_TYPE inf) : rat(rat), inf(inf) {}
    constexpr explicit inf_rational(const rational &rat, const rational &inf) : rat(rat), inf(inf) {}

    [[nodiscard]] constexpr rational get_rational() const noexcept { return rat; }
    [[nodiscard]] constexpr rational get_infinitesimal() const noexcept { return inf; }

    [[nodiscard]] inline friend constexpr bool is_zero(const inf_rational &rhs) noexcept { return is_zero(rhs.rat) && is_zero(rhs.inf); }
    [[nodiscard]] inline friend constexpr bool is_positive(const inf_rational &rhs) noexcept { return is_positive(rhs.rat) || (is_zero(rhs.rat) && is_positive(rhs.inf)); }
    [[nodiscard]] inline friend constexpr bool is_positive_or_zero(const inf_rational &rhs) noexcept { return is_positive(rhs.rat) || (is_zero(rhs.rat) && is_positive_or_zero(rhs.inf)); }
    [[nodiscard]] inline friend constexpr bool is_negative(const inf_rational &rhs) noexcept { return is_negative(rhs.rat) || (is_zero(rhs.rat) && is_negative(rhs.inf)); }
    [[nodiscard]] inline friend constexpr bool is_negative_or_zero(const inf_rational &rhs) noexcept { return is_negative(rhs.rat) || (is_zero(rhs.rat) && is_negative_or_zero(rhs.inf)); }
    [[nodiscard]] inline friend constexpr bool is_infinite(const inf_rational &rhs) noexcept { return is_infinite(rhs.rat); }
    [[nodiscard]] inline friend constexpr bool is_positive_infinite(const inf_rational &rhs) noexcept { return is_positive(rhs) && is_infinite(rhs); }
    [[nodiscard]] inline friend constexpr bool is_negative_infinite(const inf_rational &rhs) noexcept { return is_negative(rhs) && is_infinite(rhs); }

    [[nodiscard]] inline constexpr bool operator!=(const inf_rational &rhs) const noexcept { return rat != rhs.rat || inf != rhs.inf; };
    [[nodiscard]] inline constexpr bool operator<(const inf_rational &rhs) const noexcept { return rat < rhs.rat || (rat == rhs.rat && inf < rhs.inf); };
    [[nodiscard]] inline constexpr bool operator<=(const inf_rational &rhs) const noexcept { return rat < rhs.rat || (rat == rhs.rat && inf <= rhs.inf); };
    [[nodiscard]] inline constexpr bool operator==(const inf_rational &rhs) const noexcept { return rat == rhs.rat && inf == rhs.inf; };
    [[nodiscard]] inline constexpr bool operator>=(const inf_rational &rhs) const noexcept { return rat > rhs.rat || (rat == rhs.rat && inf >= rhs.inf); };
    [[nodiscard]] inline constexpr bool operator>(const inf_rational &rhs) const noexcept { return rat > rhs.rat || (rat == rhs.rat && inf > rhs.inf); };

    [[nodiscard]] inline constexpr bool operator!=(const rational &rhs) const noexcept { return rat != rhs || !is_zero(inf); };
    [[nodiscard]] inline constexpr bool operator<(const rational &rhs) const noexcept { return rat < rhs || (rat == rhs && is_negative(inf)); };
    [[nodiscard]] inline constexpr bool operator<=(const rational &rhs) const noexcept { return rat < rhs || (rat == rhs && is_negative_or_zero(inf)); };
    [[nodiscard]] inline constexpr bool operator==(const rational &rhs) const noexcept { return rat == rhs && is_zero(inf); };
    [[nodiscard]] inline constexpr bool operator>=(const rational &rhs) const noexcept { return rat > rhs || (rat == rhs && is_positive_or_zero(inf)); };
    [[nodiscard]] inline constexpr bool operator>(const rational &rhs) const noexcept { return rat > rhs || (rat == rhs && is_positive(inf)); };

    [[nodiscard]] inline constexpr bool operator!=(const INTEGER_TYPE &rhs) const noexcept { return rat != rhs || !is_zero(inf); };
    [[nodiscard]] inline constexpr bool operator<(const INTEGER_TYPE &rhs) const noexcept { return rat < rhs || (rat == rhs && is_negative(inf)); };
    [[nodiscard]] inline constexpr bool operator<=(const INTEGER_TYPE &rhs) const noexcept { return rat < rhs || (rat == rhs && is_negative_or_zero(inf)); };
    [[nodiscard]] inline constexpr bool operator==(const INTEGER_TYPE &rhs) const noexcept { return rat == rhs && is_zero(inf); };
    [[nodiscard]] inline constexpr bool operator>=(const INTEGER_TYPE &rhs) const noexcept { return rat > rhs || (rat == rhs && is_positive_or_zero(inf)); };
    [[nodiscard]] inline constexpr bool operator>(const INTEGER_TYPE &rhs) const noexcept { return rat > rhs || (rat == rhs && is_positive(inf)); };

    [[nodiscard]] inline constexpr inf_rational operator+(const inf_rational &rhs) const noexcept { return inf_rational(rat + rhs.rat, inf + rhs.inf); };
    [[nodiscard]] inline constexpr inf_rational operator-(const inf_rational &rhs) const noexcept { return inf_rational(rat - rhs.rat, inf - rhs.inf); };

    [[nodiscard]] inline constexpr inf_rational operator+(const rational &rhs) const noexcept { return inf_rational(rat + rhs, inf); };
    [[nodiscard]] inline constexpr inf_rational operator-(const rational &rhs) const noexcept { return inf_rational(rat - rhs, inf); };
    [[nodiscard]] inline constexpr inf_rational operator*(const rational &rhs) const noexcept { return inf_rational(rat * rhs, inf * rhs); };
    [[nodiscard]] inline constexpr inf_rational operator/(const rational &rhs) const noexcept { return inf_rational(rat / rhs, inf / rhs); };

    [[nodiscard]] inline constexpr inf_rational operator+(const INTEGER_TYPE &rhs) const noexcept { return inf_rational(rat + rhs, inf); };
    [[nodiscard]] inline constexpr inf_rational operator-(const INTEGER_TYPE &rhs) const noexcept { return inf_rational(rat - rhs, inf); };
    [[nodiscard]] inline constexpr inf_rational operator*(const INTEGER_TYPE &rhs) const noexcept { return inf_rational(rat * rhs, inf * rhs); };
    [[nodiscard]] inline constexpr inf_rational operator/(const INTEGER_TYPE &rhs) const noexcept { return inf_rational(rat / rhs, inf / rhs); };

    inline constexpr inf_rational &operator+=(const inf_rational &rhs) noexcept
    {
      rat += rhs.rat;
      inf += rhs.inf;
      return *this;
    }
    inline constexpr inf_rational &operator-=(const inf_rational &rhs) noexcept
    {
      rat -= rhs.rat;
      inf -= rhs.inf;
      return *this;
    }

    inline constexpr inf_rational &operator+=(const rational &rhs) noexcept
    {
      rat += rhs;
      return *this;
    }
    inline constexpr inf_rational &operator-=(const rational &rhs) noexcept
    {
      rat -= rhs;
      return *this;
    }
    inline constexpr inf_rational &operator*=(const rational &rhs) noexcept
    {
      rat *= rhs;
      inf *= rhs;
      return *this;
    }
    inline constexpr inf_rational &operator/=(const rational &rhs) noexcept
    {
      rat /= rhs;
      inf /= rhs;
      return *this;
    }

    inline constexpr inf_rational &operator+=(const INTEGER_TYPE &rhs) noexcept
    {
      rat += rhs;
      return *this;
    }
    inline constexpr inf_rational &operator-=(const INTEGER_TYPE &rhs) noexcept
    {
      rat -= rhs;
      return *this;
    }
    inline constexpr inf_rational &operator*=(const INTEGER_TYPE &rhs) noexcept
    {
      rat *= rhs;
      inf *= rhs;
      return *this;
    }
    inline constexpr inf_rational &operator/=(const INTEGER_TYPE &rhs) noexcept
    {
      rat /= rhs;
      inf /= rhs;
      return *this;
    }

    [[nodiscard]] inline constexpr inf_rational operator-() const noexcept { return inf_rational(-rat, -inf); }

    [[nodiscard]] inline friend constexpr inf_rational operator+(const rational &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs + rhs.rat, rhs.inf); }
    [[nodiscard]] inline friend constexpr inf_rational operator-(const rational &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs - rhs.rat, rhs.inf); }
    [[nodiscard]] inline friend constexpr inf_rational operator*(const rational &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs * rhs.rat, lhs * rhs.inf); }
    [[nodiscard]] inline friend constexpr inf_rational operator/(const rational &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs / rhs.rat, lhs / rhs.inf); }

    [[nodiscard]] inline friend constexpr inf_rational operator+(const INTEGER_TYPE &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs + rhs.rat, rhs.inf); }
    [[nodiscard]] inline friend constexpr inf_rational operator-(const INTEGER_TYPE &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs - rhs.rat, rhs.inf); }
    [[nodiscard]] inline friend constexpr inf_rational operator*(const INTEGER_TYPE &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs * rhs.rat, lhs * rhs.inf); }
    [[nodiscard]] inline friend constexpr inf_rational operator/(const INTEGER_TYPE &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs / rhs.rat, lhs / rhs.inf); }

    friend std::string to_string(const inf_rational &rhs) noexcept
    {
      if (is_infinite(rhs.rat) || rhs.inf == rational::zero)
        return to_string(rhs.rat);
      std::string c_str;
      if (rhs.rat != rational::zero)
        c_str += to_string(rhs.rat);
      if (rhs.inf == rational::one)
        if (c_str.empty())
          c_str += "ε";
        else
          c_str += " + ε";
      else if (rhs.inf == -rational::one)
        if (c_str.empty())
          c_str += "-ε";
        else
          c_str += " - ε";
      else if (is_negative(rhs.inf))
        if (c_str.empty())
          c_str += to_string(rhs.inf) + "ε";
        else
          c_str += " " + to_string(rhs.inf) + "ε";
      else if (c_str.empty())
        c_str += to_string(rhs.inf) + "ε";
      else
        c_str += " +" + to_string(rhs.inf) + "ε";
      return c_str;
    };

  private:
    rational rat; // the rational part..
    rational inf; // the infinitesimal part..
  };
} // namespace utils