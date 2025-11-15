#include "inf_rational.hpp"

namespace utils
{
    const inf_rational inf_rational::zero = inf_rational();
    const inf_rational inf_rational::epsilon = inf_rational(rational::zero, 1);

    std::string to_string(const inf_rational &rhs) noexcept
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
} // namespace utils