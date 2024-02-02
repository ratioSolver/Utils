#pragma once

#include <vector>
#include <set>
#include "lin.hpp"

namespace utils
{
  class tableau final
  {
  public:
    /**
     * @brief Create a new variable.
     */
    VARIABLE_TYPE new_var();

    /**
     * @brief Add a new row to the tableau.
     *
     * @param x_i the variable of the row.
     * @param expr the linear expression of the row.
     */
    void add_row(const VARIABLE_TYPE x_i, lin &&expr);

    /**
     * @brief Pivot the tableau using the variable `x_i` and the variable `x_j`.
     *
     * @param x_i the leaving variable.
     * @param x_j the entering variable.
     */
    void pivot(const VARIABLE_TYPE x_i, const VARIABLE_TYPE x_j);

    friend std::string to_string(const tableau &t) noexcept;

  private:
    std::map<const VARIABLE_TYPE, lin> table;
    std::vector<std::set<VARIABLE_TYPE>> watches;
  };
} // namespace utils
