#include <cassert>
#include "tableau.hpp"

namespace utils
{
    VARIABLE_TYPE tableau::new_var()
    {
        watches.push_back(std::set<VARIABLE_TYPE>());
        return static_cast<VARIABLE_TYPE>(watches.size() - 1);
    }

    void tableau::add_row(const VARIABLE_TYPE x_i, lin &&expr)
    {
        assert(table.find(x_i) == table.cend());
        for (const auto &x : expr.vars)
            watches[x.first].insert(x_i);
        table.emplace(x_i, std::move(expr));
    }

    void tableau::pivot(const VARIABLE_TYPE x_i, const VARIABLE_TYPE y_j) noexcept
    { // `x_i` is the leaving variable, `y_j` is the entering variable
        assert(table.find(x_i) != table.cend() && "x_i is not a basic variable");
        assert(watches[x_i].empty() && "x_i is should not be in any other row of the tableau");
        assert(table.find(y_j) == table.cend() && "y_j is not a non-basic variable");

        // we remove the leaving variable `x_i` from the watches
        for (const auto &x : table[x_i].vars)
            watches[x.first].erase(x_i);

        // we rewrite `x_i = ...` as `y_j = ...`
        lin l = std::move(table[x_i]);
        rational c = l.vars.at(y_j);
        l.vars.erase(y_j);
        l /= -c;
        l.vars.emplace(x_i, rational::one / c);
        table.erase(x_i);

        // we update the rows that contain `y_j`
        for (auto &x : watches[y_j])
        {
            rational &c = table[x].vars.at(y_j);
            for (const auto &term : l.vars)
                if (const auto trm_it = table[x].vars.find(term.first); trm_it == table[x].vars.cend())
                {                                                       // `term.first` is not in the linear expression of `x`, so we add it
                    table[x].vars.emplace(term.first, c * term.second); // we add `c * term.second` to the linear expression of `x`
                    watches[term.first].insert(x);                      // we add `x` to the watches of `term.first`
                }
                else
                {
                    trm_it->second += c * term.second;
                    if (trm_it->second == 0)
                    {                                 // if the coefficient of `term.first` is zero, we remove the term from the linear expression
                        table[x].vars.erase(trm_it);  // we remove `term.first` from the linear expression of `x`
                        watches[term.first].erase(x); // we remove `x` from the watches of `term.first`
                    }
                }
            table[x].known_term += c * l.known_term;
        }

        // we add the new row `y_j = ...`
        add_row(y_j, std::move(l));
    }

    std::string to_string(const tableau &t) noexcept
    {
        std::string s;
        for (const auto &row : t.table)
            s += "x" + std::to_string(row.first) + " = " + to_string(row.second) + "\n";
        return s;
    }
} // namespace utils