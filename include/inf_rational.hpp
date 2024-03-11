#pragma once

#include "rational.hpp"

namespace utils
{
  class inf_rational
  {
  public:
    static const inf_rational epsilon;

    explicit inf_rational() = default;
    explicit inf_rational(INTEGER_TYPE nun) noexcept : rat(nun) {}
    explicit inf_rational(const rational &rat) noexcept : rat(rat) {}
    explicit inf_rational(INTEGER_TYPE nun, INTEGER_TYPE den) noexcept : rat(nun, den) {}
    explicit inf_rational(const rational &rat, INTEGER_TYPE inf) noexcept : rat(rat), inf(inf) {}
    explicit inf_rational(const rational &rat, const rational &inf) noexcept : rat(rat), inf(inf) {}

    [[nodiscard]] rational get_rational() const noexcept { return rat; }
    [[nodiscard]] rational get_infinitesimal() const noexcept { return inf; }

    [[nodiscard]] inline friend bool is_zero(const inf_rational &rhs) noexcept { return is_zero(rhs.rat) && is_zero(rhs.inf); }
    [[nodiscard]] inline friend bool is_positive(const inf_rational &rhs) noexcept { return is_positive(rhs.rat) || (is_zero(rhs.rat) && is_positive(rhs.inf)); }
    [[nodiscard]] inline friend bool is_positive_or_zero(const inf_rational &rhs) noexcept { return is_positive(rhs.rat) || (is_zero(rhs.rat) && is_positive_or_zero(rhs.inf)); }
    [[nodiscard]] inline friend bool is_negative(const inf_rational &rhs) noexcept { return is_negative(rhs.rat) || (is_zero(rhs.rat) && is_negative(rhs.inf)); }
    [[nodiscard]] inline friend bool is_negative_or_zero(const inf_rational &rhs) noexcept { return is_negative(rhs.rat) || (is_zero(rhs.rat) && is_negative_or_zero(rhs.inf)); }
    [[nodiscard]] inline friend bool is_infinite(const inf_rational &rhs) noexcept { return is_infinite(rhs.rat); }
    [[nodiscard]] inline friend bool is_positive_infinite(const inf_rational &rhs) noexcept { return is_positive(rhs) && is_infinite(rhs); }
    [[nodiscard]] inline friend bool is_negative_infinite(const inf_rational &rhs) noexcept { return is_negative(rhs) && is_infinite(rhs); }

    [[nodiscard]] inline bool operator!=(const inf_rational &rhs) const noexcept { return rat != rhs.rat || inf != rhs.inf; };
    [[nodiscard]] inline bool operator<(const inf_rational &rhs) const noexcept { return rat < rhs.rat || (rat == rhs.rat && inf < rhs.inf); };
    [[nodiscard]] inline bool operator<=(const inf_rational &rhs) const noexcept { return rat < rhs.rat || (rat == rhs.rat && inf <= rhs.inf); };
    [[nodiscard]] inline bool operator==(const inf_rational &rhs) const noexcept { return rat == rhs.rat && inf == rhs.inf; };
    [[nodiscard]] inline bool operator>=(const inf_rational &rhs) const noexcept { return rat > rhs.rat || (rat == rhs.rat && inf >= rhs.inf); };
    [[nodiscard]] inline bool operator>(const inf_rational &rhs) const noexcept { return rat > rhs.rat || (rat == rhs.rat && inf > rhs.inf); };

    [[nodiscard]] inline bool operator!=(const rational &rhs) const noexcept { return rat != rhs || !is_zero(inf); };
    [[nodiscard]] inline bool operator<(const rational &rhs) const noexcept { return rat < rhs || (rat == rhs && is_negative(inf)); };
    [[nodiscard]] inline bool operator<=(const rational &rhs) const noexcept { return rat < rhs || (rat == rhs && is_negative_or_zero(inf)); };
    [[nodiscard]] inline bool operator==(const rational &rhs) const noexcept { return rat == rhs && is_zero(inf); };
    [[nodiscard]] inline bool operator>=(const rational &rhs) const noexcept { return rat > rhs || (rat == rhs && is_positive_or_zero(inf)); };
    [[nodiscard]] inline bool operator>(const rational &rhs) const noexcept { return rat > rhs || (rat == rhs && is_positive(inf)); };

    [[nodiscard]] inline bool operator!=(const INTEGER_TYPE &rhs) const noexcept { return rat != rhs || !is_zero(inf); };
    [[nodiscard]] inline bool operator<(const INTEGER_TYPE &rhs) const noexcept { return rat < rhs || (rat == rhs && is_negative(inf)); };
    [[nodiscard]] inline bool operator<=(const INTEGER_TYPE &rhs) const noexcept { return rat < rhs || (rat == rhs && is_negative_or_zero(inf)); };
    [[nodiscard]] inline bool operator==(const INTEGER_TYPE &rhs) const noexcept { return rat == rhs && is_zero(inf); };
    [[nodiscard]] inline bool operator>=(const INTEGER_TYPE &rhs) const noexcept { return rat > rhs || (rat == rhs && is_positive_or_zero(inf)); };
    [[nodiscard]] inline bool operator>(const INTEGER_TYPE &rhs) const noexcept { return rat > rhs || (rat == rhs && is_positive(inf)); };

    [[nodiscard]] inline inf_rational operator+(const inf_rational &rhs) const noexcept { return inf_rational(rat + rhs.rat, inf + rhs.inf); };
    [[nodiscard]] inline inf_rational operator-(const inf_rational &rhs) const noexcept { return inf_rational(rat - rhs.rat, inf - rhs.inf); };

    [[nodiscard]] inline inf_rational operator+(const rational &rhs) const noexcept { return inf_rational(rat + rhs, inf); };
    [[nodiscard]] inline inf_rational operator-(const rational &rhs) const noexcept { return inf_rational(rat - rhs, inf); };
    [[nodiscard]] inline inf_rational operator*(const rational &rhs) const noexcept { return inf_rational(rat * rhs, inf * rhs); };
    [[nodiscard]] inline inf_rational operator/(const rational &rhs) const noexcept { return inf_rational(rat / rhs, inf / rhs); };

    [[nodiscard]] inline inf_rational operator+(const INTEGER_TYPE &rhs) const noexcept { return inf_rational(rat + rhs, inf); };
    [[nodiscard]] inline inf_rational operator-(const INTEGER_TYPE &rhs) const noexcept { return inf_rational(rat - rhs, inf); };
    [[nodiscard]] inline inf_rational operator*(const INTEGER_TYPE &rhs) const noexcept { return inf_rational(rat * rhs, inf * rhs); };
    [[nodiscard]] inline inf_rational operator/(const INTEGER_TYPE &rhs) const noexcept { return inf_rational(rat / rhs, inf / rhs); };

    inline inf_rational &operator+=(const inf_rational &rhs) noexcept
    {
      rat += rhs.rat;
      inf += rhs.inf;
      return *this;
    }
    inline inf_rational &operator-=(const inf_rational &rhs) noexcept
    {
      rat -= rhs.rat;
      inf -= rhs.inf;
      return *this;
    }

    inline inf_rational &operator+=(const rational &rhs) noexcept
    {
      rat += rhs;
      return *this;
    }
    inline inf_rational &operator-=(const rational &rhs) noexcept
    {
      rat -= rhs;
      return *this;
    }
    inline inf_rational &operator*=(const rational &rhs) noexcept
    {
      rat *= rhs;
      inf *= rhs;
      return *this;
    }
    inline inf_rational &operator/=(const rational &rhs) noexcept
    {
      rat /= rhs;
      inf /= rhs;
      return *this;
    }

    inline inf_rational &operator+=(const INTEGER_TYPE &rhs) noexcept
    {
      rat += rhs;
      return *this;
    }
    inline inf_rational &operator-=(const INTEGER_TYPE &rhs) noexcept
    {
      rat -= rhs;
      return *this;
    }
    inline inf_rational &operator*=(const INTEGER_TYPE &rhs) noexcept
    {
      rat *= rhs;
      inf *= rhs;
      return *this;
    }
    inline inf_rational &operator/=(const INTEGER_TYPE &rhs) noexcept
    {
      rat /= rhs;
      inf /= rhs;
      return *this;
    }

    [[nodiscard]] inline inf_rational operator-() const noexcept { return inf_rational(-rat, -inf); }

    [[nodiscard]] inline friend inf_rational operator+(const rational &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs + rhs.rat, rhs.inf); }
    [[nodiscard]] inline friend inf_rational operator-(const rational &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs - rhs.rat, rhs.inf); }
    [[nodiscard]] inline friend inf_rational operator*(const rational &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs * rhs.rat, lhs * rhs.inf); }
    [[nodiscard]] inline friend inf_rational operator/(const rational &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs / rhs.rat, lhs / rhs.inf); }

    [[nodiscard]] inline friend inf_rational operator+(const INTEGER_TYPE &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs + rhs.rat, rhs.inf); }
    [[nodiscard]] inline friend inf_rational operator-(const INTEGER_TYPE &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs - rhs.rat, rhs.inf); }
    [[nodiscard]] inline friend inf_rational operator*(const INTEGER_TYPE &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs * rhs.rat, lhs * rhs.inf); }
    [[nodiscard]] inline friend inf_rational operator/(const INTEGER_TYPE &lhs, const inf_rational &rhs) noexcept { return inf_rational(lhs / rhs.rat, lhs / rhs.inf); }

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