#include "integer.hpp"
#include <cassert>

namespace utils
{
    const integer integer::zero(0);
    const integer integer::one(1);
    const integer integer::negative_infinite(-1, true);
    const integer integer::positive_infinite(1, true);

    integer::integer(INT_TYPE val) : val(val), is_inf(false) {}
    integer::integer(INT_TYPE val, bool is_inf) : val(val), is_inf(is_inf)
    {
        if (is_inf)
        {
            assert(val != 0);
            val = val > 0 ? 1 : -1;
        }
    }

    bool integer::operator!=(const integer &rhs) const noexcept { return is_inf != rhs.is_inf || val != rhs.val; }
    bool integer::operator<(const integer &rhs) const noexcept { return (is_inf && !rhs.is_inf) || (!is_inf && !rhs.is_inf && val < rhs.val); }
    bool integer::operator<=(const integer &rhs) const noexcept { return (is_inf && !rhs.is_inf) || (!is_inf && !rhs.is_inf && val <= rhs.val); }
    bool integer::operator==(const integer &rhs) const noexcept { return val == rhs.val && is_inf == rhs.is_inf; }
    bool integer::operator>=(const integer &rhs) const noexcept { return (is_inf && !rhs.is_inf) || (!is_inf && !rhs.is_inf && val >= rhs.val); }
    bool integer::operator>(const integer &rhs) const noexcept { return (!is_inf && !rhs.is_inf && val > rhs.val) || (!is_inf && rhs.is_inf); }

    bool integer::operator!=(const INT_TYPE &rhs) const noexcept { return !is_inf || val != rhs; }
    bool integer::operator<(const INT_TYPE &rhs) const noexcept { return is_inf || val < rhs; }
    bool integer::operator<=(const INT_TYPE &rhs) const noexcept { return is_inf || val <= rhs; }
    bool integer::operator==(const INT_TYPE &rhs) const noexcept { return !is_inf && val == rhs; }
    bool integer::operator>=(const INT_TYPE &rhs) const noexcept { return !is_inf || val >= rhs; }
    bool integer::operator>(const INT_TYPE &rhs) const noexcept { return !is_inf && val > rhs; }

    integer integer::operator+(const integer &rhs) const noexcept
    {
        assert(!is_positive_infinite(*this) || !is_negative_infinite(rhs)); // indeterminant form +inf + -inf
        assert(!is_negative_infinite(*this) || !is_positive_infinite(rhs)); // indeterminant form -inf + +inf
        if (is_inf || rhs.is_inf)
            return is_inf ? *this : rhs;
        return integer(val + rhs.val);
    }
    integer integer::operator-(const integer &rhs) const noexcept
    {
        assert(!is_positive_infinite(*this) || !is_positive_infinite(rhs)); // indeterminant form +inf - +inf
        assert(!is_negative_infinite(*this) || !is_negative_infinite(rhs)); // indeterminant form -inf - -inf
        if (is_inf || rhs.is_inf)
            return is_inf ? *this : rhs;
        return integer(val - rhs.val);
    }
    integer integer::operator*(const integer &rhs) const noexcept
    {
        assert(!is_infinite(*this) || !is_zero(rhs)); // indeterminant form inf * 0
        assert(!is_zero(*this) || !is_infinite(rhs)); // indeterminant form 0 * inf
        if (is_inf || rhs.is_inf)
            return is_inf ? *this : rhs;
        return integer(val * rhs.val);
    }
    integer integer::operator/(const integer &rhs) const noexcept
    {
        assert(!is_infinite(*this) || !is_infinite(rhs)); // indeterminant form inf / inf
        assert(!is_zero(*this) || !is_zero(rhs));         // indeterminant form 0 / 0
        if (is_inf || rhs.is_inf)
            return is_inf ? *this : rhs;
        return integer(val / rhs.val);
    }

    integer integer::operator+(const INT_TYPE &rhs) const noexcept
    {
        if (is_inf)
            return *this;
        return integer(val + rhs);
    }
    integer integer::operator-(const INT_TYPE &rhs) const noexcept
    {
        if (is_inf)
            return *this;
        return integer(val - rhs);
    }
    integer integer::operator*(const INT_TYPE &rhs) const noexcept
    {
        assert(!is_infinite(*this) || rhs != 0); // indeterminant form inf * 0
        if (is_inf)
            return *this;
        return integer(val * rhs);
    }
    integer integer::operator/(const INT_TYPE &rhs) const noexcept
    {
        assert(!is_zero(*this) || rhs != 0); // indeterminant form 0 / 0
        if (is_inf)
            return *this;
        if (rhs == 0)
            return is_inf ? *this : integer(val > 0 ? 1 : -1, true);
        return integer(val / rhs);
    }

    integer &integer::operator+=(const integer &rhs) noexcept
    {
        assert(!is_positive_infinite(*this) || !is_negative_infinite(rhs)); // indeterminant form +inf + -inf
        assert(!is_negative_infinite(*this) || !is_positive_infinite(rhs)); // indeterminant form -inf + +inf
        if (is_inf || rhs.is_inf)
            return *this = is_inf ? *this : rhs;
        val += rhs.val;
        return *this;
    }
    integer &integer::operator-=(const integer &rhs) noexcept
    {
        assert(!is_positive_infinite(*this) || !is_positive_infinite(rhs)); // indeterminant form +inf - +inf
        assert(!is_negative_infinite(*this) || !is_negative_infinite(rhs)); // indeterminant form -inf - -inf
        if (is_inf || rhs.is_inf)
            return *this = is_inf ? *this : rhs;
        val -= rhs.val;
        return *this;
    }
    integer &integer::operator*=(const integer &rhs) noexcept
    {
        assert(!is_infinite(*this) || !is_zero(rhs)); // indeterminant form inf * 0
        assert(!is_zero(*this) || !is_infinite(rhs)); // indeterminant form 0 * inf
        if (is_inf || rhs.is_inf)
            return *this = is_inf ? *this : rhs;
        val *= rhs.val;
        return *this;
    }
    integer &integer::operator/=(const integer &rhs) noexcept
    {
        assert(!is_infinite(*this) || !is_infinite(rhs)); // indeterminant form inf / inf
        assert(!is_zero(*this) || !is_zero(rhs));         // indeterminant form 0 / 0
        if (is_inf || rhs.is_inf)
            return *this = is_inf ? *this : rhs;
        if (rhs.val == 0)
        {
            is_inf = true;
            val = val > 0 ? 1 : -1;
        }
        else
            val /= rhs.val;
        return *this;
    }

    integer &integer::operator+=(const INT_TYPE &rhs) noexcept
    {
        if (is_inf)
            return *this;
        val += rhs;
        return *this;
    }
    integer &integer::operator-=(const INT_TYPE &rhs) noexcept
    {
        if (is_inf)
            return *this;
        val -= rhs;
        return *this;
    }
    integer &integer::operator*=(const INT_TYPE &rhs) noexcept
    {
        if (is_inf)
            return *this;
        val *= rhs;
        return *this;
    }
    integer &integer::operator/=(const INT_TYPE &rhs) noexcept
    {
        assert(!is_zero(*this) || rhs != 0); // indeterminant form 0 / 0
        if (is_inf)
            return *this;
        if (rhs == 0)
        {
            is_inf = true;
            val = val > 0 ? 1 : -1;
        }
        else
            val /= rhs;
        return *this;
    }

    integer operator+(const INT_TYPE &lhs, const integer &rhs) noexcept { return rhs + lhs; }
    integer operator-(const INT_TYPE &lhs, const integer &rhs) noexcept { return -rhs + lhs; }
    integer operator*(const INT_TYPE &lhs, const integer &rhs) noexcept { return rhs * lhs; }
    integer operator/(const INT_TYPE &lhs, const integer &rhs) noexcept { return integer(lhs) / rhs; }

    bool operator!=(const INT_TYPE &lhs, const integer &rhs) noexcept { return rhs != lhs; }
    bool operator<(const INT_TYPE &lhs, const integer &rhs) noexcept { return rhs > lhs; }
    bool operator<=(const INT_TYPE &lhs, const integer &rhs) noexcept { return rhs >= lhs; }
    bool operator==(const INT_TYPE &lhs, const integer &rhs) noexcept { return rhs == lhs; }
    bool operator>=(const INT_TYPE &lhs, const integer &rhs) noexcept { return rhs <= lhs; }
    bool operator>(const INT_TYPE &lhs, const integer &rhs) noexcept { return rhs < lhs; }

    integer integer::operator-() const noexcept { return integer(-val, is_inf); }

    std::string to_string(const integer &rhs) noexcept
    {
        if (rhs.is_inf)
            return rhs.val > 0 ? "inf" : "-inf";
        return std::to_string(rhs.val);
    }
} // namespace utils
