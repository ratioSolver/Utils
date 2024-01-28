#include "rational.hpp"
#include <numeric>
#include <cassert>

namespace utils
{
    const rational rational::zero(0);
    const rational rational::one(1);
    const rational rational::negative_infinite(-1, 0);
    const rational rational::positive_infinite(1, 0);

    rational::rational() : num(0), den(1) {}
    rational::rational(INTEGER_TYPE n) : num(n), den(1) {}
    rational::rational(INTEGER_TYPE n, INTEGER_TYPE d) : num(n), den(d)
    {
        assert(n != 0 || d != 0);
        normalize();
    }

    bool rational::operator!=(const rational &rhs) const noexcept { return num != rhs.num || den != rhs.den; }
    bool rational::operator<(const rational &rhs) const noexcept { return (den == rhs.den) ? num < rhs.num : num * rhs.den < den * rhs.num; }
    bool rational::operator<=(const rational &rhs) const noexcept { return num * rhs.den <= den * rhs.num; }
    bool rational::operator==(const rational &rhs) const noexcept { return num == rhs.num && den == rhs.den; }
    bool rational::operator>=(const rational &rhs) const noexcept { return num * rhs.den >= den * rhs.num; }
    bool rational::operator>(const rational &rhs) const noexcept { return (den == rhs.den) ? num > rhs.num : num * rhs.den > den * rhs.num; }

    bool rational::operator!=(const INTEGER_TYPE &rhs) const noexcept { return num != rhs || den != 1; }
    bool rational::operator<(const INTEGER_TYPE &rhs) const noexcept { return num < den * rhs; }
    bool rational::operator<=(const INTEGER_TYPE &rhs) const noexcept { return num <= den * rhs; }
    bool rational::operator==(const INTEGER_TYPE &rhs) const noexcept { return num == rhs && den == 1; }
    bool rational::operator>=(const INTEGER_TYPE &rhs) const noexcept { return num >= den * rhs; }
    bool rational::operator>(const INTEGER_TYPE &rhs) const noexcept { return num > den * rhs; }

    rational rational::operator+(const rational &rhs) const noexcept
    {
        assert(den != 0 || rhs.den != 0 || num == rhs.num); // inf + -inf or -inf + inf..

        // special cases..
        if (num == 0 || is_infinite(rhs))
            return rhs;
        if (rhs.num == 0 || is_infinite(*this))
            return *this;
        if (den == 1 && rhs.den == 1)
            return rational(num + rhs.num);

        INTEGER_TYPE f = std::gcd(num, rhs.num);
        INTEGER_TYPE g = std::gcd(den, rhs.den);

        rational res((num / f) * (rhs.den / g) + (rhs.num / f) * (den / g), std::lcm(den, rhs.den));
        res.num *= f;
        return res;
    }

    rational rational::operator-(const rational &rhs) const noexcept { return operator+(-rhs); }

    rational rational::operator*(const rational &rhs) const noexcept
    {
        assert(num != 0 || rhs.den != 0); // 0*inf..
        assert(den != 0 || rhs.num != 0); // inf*0..

        // special cases..
        if (rhs == one)
            return *this;
        if (operator==(one))
            return rhs;
        if (den == 1 && rhs.den == 1)
            return rational(num * rhs.num);
        if (is_infinite(*this) || is_infinite(rhs))
            return ((num >= 0 && rhs.num >= 0) || (num <= 0 && rhs.num <= 0)) ? positive_infinite : negative_infinite;

        rational c(num, rhs.den);
        rational d(rhs.num, den);
        return rational(c.num * d.num, c.den * d.den);
    }

    rational rational::operator/(const rational &rhs) const noexcept
    {
        assert(rhs.num != 0 || rhs.den != 0 || num == 0); // 0/0..
        assert(rhs.num != 0 || rhs.den != 0 || den == 0); // inf/inf..

        rational rec;
        if (rhs.num >= 0)
        {
            rec.num = rhs.den;
            rec.den = rhs.num;
        }
        else
        {
            rec.num = -rhs.den;
            rec.den = -rhs.num;
        }
        return operator*(rec);
    }

    rational rational::operator+(const INTEGER_TYPE &rhs) const noexcept
    {
        // special cases..
        if (num == 0)
            return rational(rhs);
        if (rhs == 0 || is_infinite(*this))
            return *this;
        if (den == 1)
            return rational(num + rhs);

        rational res;
        res.num = num + rhs * den;
        res.den = den;
        return res;
    }

    rational rational::operator-(const INTEGER_TYPE &rhs) const noexcept { return operator+(-rhs); }

    rational rational::operator*(const INTEGER_TYPE &rhs) const noexcept
    {
        assert(den != 0 || rhs != 0); // inf*0..
        assert(rhs != 0 || den != 0); // 0*inf..

        // special cases..
        if (rhs == 1)
            return *this;
        if (operator==(one))
            return rational(rhs);
        if (den == 1)
            return rational(num * rhs);
        if (is_infinite(*this))
            return ((num >= 0 && rhs >= 0) || (num <= 0 && rhs <= 0)) ? positive_infinite : negative_infinite;

        return rational(num * rhs, den);
    }

    rational rational::operator/(const INTEGER_TYPE &rhs) const noexcept
    {
        assert(rhs != 0 || num == 0); // 0/0..
        assert(rhs != 0 || den == 0); // inf/inf..

        rational rec;
        rec.num = 1;
        rec.den = rhs;
        if (rhs >= 0)
        {
            rec.num = 1;
            rec.den = rhs;
        }
        else
        {
            rec.num = -1;
            rec.den = -rhs;
        }
        return operator*(rec);
    }

    rational &rational::operator+=(const rational &rhs) noexcept
    {
        assert(den != 0 || rhs.den != 0 || num == rhs.num); // inf + -inf or -inf + inf..

        // special cases..
        if (num == 0 || is_infinite(rhs))
        {
            num = rhs.num;
            den = rhs.den;
            return *this;
        }
        if (rhs.num == 0 || is_infinite(*this))
            return *this;
        if (den == 1 && rhs.den == 1)
        {
            num += rhs.num;
            return *this;
        }

        INTEGER_TYPE f = std::gcd(num, rhs.num);
        INTEGER_TYPE g = std::gcd(den, rhs.den);

        num = (num / f) * (rhs.den / g) + (rhs.num / f) * (den / g);
        den = std::lcm(den, rhs.den);
        normalize();
        num *= f;
        return *this;
    }

    rational &rational::operator-=(const rational &rhs) noexcept { return operator+=(-rhs); }

    rational &rational::operator*=(const rational &rhs) noexcept
    {
        assert(num != 0 || rhs.den != 0); // 0*inf..
        assert(den != 0 || rhs.num != 0); // inf*0..

        // special cases..
        if (rhs == one)
            return *this;
        if (operator==(one))
        {
            num = rhs.num;
            den = rhs.den;
            return *this;
        }
        if (den == 1 && rhs.den == 1)
        {
            num *= rhs.num;
            return *this;
        }
        if (is_infinite(*this) || is_infinite(rhs))
        {
            num = ((num >= 0 && rhs.num >= 0) || (num <= 0 && rhs.num <= 0)) ? 1 : -1;
            den = 0;
            return *this;
        }

        rational c(num, rhs.den);
        rational d(rhs.num, den);

        num = c.num * d.num;
        den = c.den * d.den;
        normalize();
        return *this;
    }

    rational &rational::operator/=(const rational &rhs) noexcept
    {
        assert(rhs.num != 0 || rhs.den != 0 || num == 0); // 0/0..
        assert(rhs.num != 0 || rhs.den != 0 || den == 0); // inf/inf..

        rational rec;
        rec.num = rhs.den;
        rec.den = rhs.num;
        if (rhs.num >= 0)
        {
            rec.num = rhs.den;
            rec.den = rhs.num;
        }
        else
        {
            rec.num = -rhs.den;
            rec.den = -rhs.num;
        }
        return operator*=(rec);
    }

    rational &rational::operator+=(const INTEGER_TYPE &rhs) noexcept
    {
        // special cases..
        if (num == 0)
        {
            num = rhs;
            return *this;
        }
        if (rhs == 0 || is_infinite(*this))
            return *this;
        if (den == 1)
        {
            num += rhs;
            return *this;
        }

        num += rhs * den;
        return *this;
    }

    rational &rational::operator-=(const INTEGER_TYPE &rhs) noexcept { return operator+=(-rhs); }

    rational &rational::operator*=(const INTEGER_TYPE &rhs) noexcept
    {
        assert(den != 0 || rhs != 0); // inf*0..
        assert(rhs != 0 || den != 0); // 0*inf..

        // special cases..
        if (rhs == 1)
            return *this;
        if (operator==(one))
        {
            num = rhs;
            return *this;
        }
        if (is_infinite(*this))
        {
            num = ((num >= 0 && rhs >= 0) || (num <= 0 && rhs <= 0)) ? 1 : -1;
            return *this;
        }

        num *= rhs;
        if (den != 1)
            normalize();

        return *this;
    }

    rational &rational::operator/=(const INTEGER_TYPE &rhs) noexcept
    {
        assert(rhs != 0 || num == 0); // 0/0..
        assert(rhs != 0 || den == 0); // inf/inf..

        rational rec;
        rec.num = 1;
        rec.den = rhs;
        if (rhs >= 0)
        {
            rec.num = 1;
            rec.den = rhs;
        }
        else
        {
            rec.num = -1;
            rec.den = -rhs;
        }
        return operator*=(rec);
    }

    rational operator+(const INTEGER_TYPE &lhs, const rational &rhs) noexcept { return rational(lhs) + rhs; }
    rational operator-(const INTEGER_TYPE &lhs, const rational &rhs) noexcept { return rational(lhs) - rhs; }
    rational operator*(const INTEGER_TYPE &lhs, const rational &rhs) noexcept { return rational(lhs) * rhs; }
    rational operator/(const INTEGER_TYPE &lhs, const rational &rhs) noexcept { return rational(lhs) / rhs; }

    rational rational::operator-() const noexcept
    {
        rational res(*this);
        res.num = -res.num;
        return res;
    }

    void rational::normalize() noexcept
    {
        if (den != 1)
        {
            INTEGER_TYPE c_gcd = std::gcd(num, den);
            num /= c_gcd;
            den /= c_gcd;
            if (den < 0)
            {
                den = -den;
                num = -num;
            }
        }
    }

    std::string to_string(const rational &rhs) noexcept
    {
        switch (rhs.den)
        {
        case 0:
            return rhs.num > 0 ? "+inf" : "-inf";
        case 1:
            return std::to_string(rhs.num);
        default:
            return std::to_string(rhs.num) + "/" + std::to_string(rhs.den);
        }
    }
} // namespace utils