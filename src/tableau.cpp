#include <cassert>
#include "tableau.hpp"

namespace utils
{
    VARIABLE_TYPE tableau::new_var()
    {
        watches.push_back(std::set<VARIABLE_TYPE>());
        return watches.size() - 1;
    }

    void tableau::add_row(const VARIABLE_TYPE x_i, lin &&expr)
    {
        for (const auto &x : expr.vars)
            watches[x.first].insert(x_i);
        table.emplace(x_i, std::move(expr));
    }

    void tableau::pivot(const VARIABLE_TYPE x_i, const VARIABLE_TYPE x_j)
    {
        for (const auto &x : table[x_i].vars)
            watches[x.first].erase(x_i);

        // we rewrite the linear expression of the leaving variable x_i
        lin l = std::move(table[x_i]);
        rational c = l.vars.at(x_j);
        l.vars.erase(x_j);
        l /= -c;
        l.vars.emplace(x_i, rational::one / c);
        table.erase(x_i);

        for (auto &x : watches[x_j])
        {
            rational &c = table[x].vars.at(x_j);
            for (const auto &term : l.vars)
                if (const auto trm_it = table[x].vars.find(term.first); trm_it == table[x].vars.cend())
                {
                    table[x].vars.emplace(term.first, c * term.second);
                    watches[term.first].insert(x);
                }
                else
                {
                    trm_it->second += c * term.second;
                    if (trm_it->second == 0)
                    {
                        table[x].vars.erase(trm_it);
                        watches[term.first].erase(x);
                    }
                }
            table[x].known_term += c * l.known_term;
        }

        add_row(x_j, std::move(l));
    }

    std::string to_string(const tableau &t) noexcept
    {
        std::string s;
        for (const auto &row : t.table)
            s += "x" + std::to_string(row.first) + " = " + to_string(row.second) + "\n";
        return s;
    }
} // namespace utils