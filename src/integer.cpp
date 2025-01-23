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
        if (is_inf || rhs.is_inf)
            return is_inf ? *this : rhs;
        return integer(val + rhs.val);
    }
    integer integer::operator-(const integer &rhs) const noexcept
    {
        if (is_inf || rhs.is_inf)
            return is_inf ? *this : rhs;
        return integer(val - rhs.val);
    }
    integer integer::operator*(const integer &rhs) const noexcept
    {
        if (is_inf || rhs.is_inf)
            return is_inf ? *this : rhs;
        return integer(val * rhs.val);
    }
    integer integer::operator/(const integer &rhs) const noexcept
    {
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
        if (is_inf)
            return *this;
        return integer(val * rhs);
    }
    integer integer::operator/(const INT_TYPE &rhs) const noexcept
    {
        if (is_inf)
            return *this;
        return integer(val / rhs);
    }

    integer &integer::operator+=(const integer &rhs) noexcept
    {
        if (is_inf || rhs.is_inf)
            return *this = is_inf ? *this : rhs;
        val += rhs.val;
        return *this;
    }
    integer &integer::operator-=(const integer &rhs) noexcept
    {
        if (is_inf || rhs.is_inf)
            return *this = is_inf ? *this : rhs;
        val -= rhs.val;
        return *this;
    }
    integer &integer::operator*=(const integer &rhs) noexcept
    {
        if (is_inf || rhs.is_inf)
            return *this = is_inf ? *this : rhs;
        val *= rhs.val;
        return *this;
    }
    integer &integer::operator/=(const integer &rhs) noexcept
    {
        if (is_inf || rhs.is_inf)
            return *this = is_inf ? *this : rhs;
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
        if (is_inf)
            return *this;
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

    integer integer::operator-() const noexcept { return integer(-val); }
} // namespace utils
