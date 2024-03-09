#include "lin.hpp"

namespace utils
{
    constexpr lin lin::operator+(const lin &right) const noexcept
    {
        lin result = *this;
        result += right;
        return result;
    }

    constexpr lin lin::operator+(const rational &right) const noexcept
    {
        lin result = *this;
        result += right;
        return result;
    }

    constexpr lin operator+(const rational &left, const lin &right) noexcept
    {
        lin result = right;
        result += left;
        return result;
    }

    constexpr lin lin::operator-(const lin &right) const noexcept
    {
        lin result = *this;
        result -= right;
        return result;
    }

    constexpr lin lin::operator-(const rational &right) const noexcept
    {
        lin result = *this;
        result -= right;
        return result;
    }

    constexpr lin operator-(const rational &left, const lin &right) noexcept
    {
        lin result = -right;
        result += left;
        return result;
    }

    constexpr lin lin::operator*(const rational &right) const noexcept
    {
        lin result = *this;
        result *= right;
        return result;
    }

    constexpr lin operator*(const rational &left, const lin &right) noexcept
    {
        lin result = right;
        result *= left;
        return result;
    }

    constexpr lin lin::operator/(const rational &right) const noexcept
    {
        lin result = *this;
        result /= right;
        return result;
    }

    constexpr lin &lin::operator+=(const lin &right) noexcept
    {
        for (const auto &term : right.vars)
            if (const auto trm_it = vars.find(term.first); trm_it == vars.cend())
                vars.emplace(term.first, term.second);
            else
            {
                trm_it->second += term.second;
                if (trm_it->second == 0)
                    vars.erase(trm_it);
            }
        known_term += right.known_term;
        return *this;
    }

    constexpr lin &lin::operator+=(const rational &right) noexcept
    {
        known_term += right;
        return *this;
    }

    constexpr lin &lin::operator-=(const lin &right) noexcept
    {
        for (const auto &term : right.vars)
            if (const auto trm_it = vars.find(term.first); trm_it == vars.cend())
                vars.emplace(term.first, -term.second);
            else
            {
                trm_it->second -= term.second;
                if (trm_it->second == 0)
                    vars.erase(trm_it);
            }
        known_term -= right.known_term;
        return *this;
    }

    constexpr lin &lin::operator-=(const rational &right) noexcept
    {
        known_term -= right;
        return *this;
    }

    constexpr lin &lin::operator*=(const rational &right) noexcept
    {
        if (right == 0)
        {
            vars.clear();
            known_term = rational::zero;
        }
        else
        {
            for (auto &term : vars)
                term.second *= right;
            known_term *= right;
        }
        return *this;
    }

    constexpr lin &lin::operator/=(const rational &right) noexcept
    {
        if (is_infinite(right))
        {
            vars.clear();
            known_term = rational::zero;
        }
        else
        {
            for (auto &term : vars)
                term.second /= right;
            known_term /= right;
        }
        return *this;
    }

    constexpr lin lin::operator-() const noexcept
    {
        lin result = *this;
        result *= -rational::one;
        return result;
    }

    constexpr lin &lin::substitute(const VARIABLE_TYPE v, const lin &right) noexcept
    {
        rational c = vars.at(v);
        vars.erase(v);
        for (const auto &term : right.vars)
            if (const auto trm_it = vars.find(term.first); trm_it == vars.cend())
                vars.emplace(term.first, c * term.second);
            else
            {
                trm_it->second += c * term.second;
                if (trm_it->second == 0)
                    vars.erase(trm_it);
            }
        known_term += c * right.known_term;
        return *this;
    }

    std::string to_string(const lin &rhs) noexcept
    {
        if (rhs.vars.empty())
            return to_string(rhs.known_term);

        std::string s;
        for (auto it = rhs.vars.cbegin(); it != rhs.vars.cend(); ++it)
            if (it == rhs.vars.cbegin())
            {
                if (it->second == rational::one)
                    s += "x" + std::to_string(it->first);
                else if (it->second == -rational::one)
                    s += "-x" + std::to_string(it->first);
                else
                    s += to_string(it->second) + "*x" + std::to_string(it->first);
            }
            else
            {
                if (it->second == rational::one)
                    s += " + x" + std::to_string(it->first);
                else if (it->second == -rational::one)
                    s += " - x" + std::to_string(it->first);
                else if (is_positive(it->second))
                    s += " + " + to_string(it->second) + "*x" + std::to_string(it->first);
                else
                    s += " - " + to_string(-it->second) + "*x" + std::to_string(it->first);
            }

        if (is_positive(rhs.known_term))
            s += " + " + to_string(rhs.known_term);
        if (is_negative(rhs.known_term))
            s += " - " + to_string(-rhs.known_term);
        return s;
    }
} // namespace utils
