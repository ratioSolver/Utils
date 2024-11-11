#pragma once

#include <vector>
#include <set>
#include "lin.hpp"

namespace utils
{
  /**
   * @brief Manage a tableau of linear expressions.
   *
   * The tableau is a map of linear expressions, where each expression is associated with a variable.
   * Formally, the tableau represents the following system of linear equations:
   *
   * `x = Ay + b`
   *
   * where `x` is the vector of variables representing the base of the tableau, `A` is the matrix of coefficients, `y` is the vector of non-basic variables, and `b` is the vector of known terms.
   * Since the tableau is usually very sparse, we use a map to represent it, having the basic variables as keys and the linear expressions as values.
   * We also keep track, for each non-basic variable, of the linear expressions that contain it, indexed by their corresponding basic variable, in order to speed up the pivot operation.
   */
  class tableau final
  {
  public:
    /**
     * @brief Create a new variable.
     */
    [[nodiscard]] std::size_t new_var();

    /**
     * @brief Add a new row to the tableau.
     *
     * @param x_i the variable of the row.
     * @param expr the linear expression of the row.
     */
    void add_row(const std::size_t x_i, lin &&expr);

    /**
     * @brief Pivot the tableau using the variable `x_i` and the variable `y_j`.
     *
     * The pivot operation is used to transform the tableau in order to solve the linear system of equations.
     * The `x = Ay + b` system is transformed into `x' = A'y' + b'`, where `x'` is the new base of the tableau, `A'` is the new matrix of coefficients, `y'` is the new vector of non-basic variables, and `b'` is the new vector of known terms.
     * The `x_i = ...` row is replaced by the `y_j = ...` row, updating all the rows that contain `y_j` in their linear expression.
     *
     * @param x_i the leaving variable.
     * @param y_j the entering variable.
     */
    void pivot(const std::size_t x_i, const std::size_t y_j) noexcept;

    friend std::string to_string(const tableau &t) noexcept;

  private:
    std::map<const std::size_t, lin> table;
    std::vector<std::set<std::size_t>> watches;
  };
} // namespace utils
