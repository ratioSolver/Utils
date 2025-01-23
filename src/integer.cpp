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
} // namespace utils
