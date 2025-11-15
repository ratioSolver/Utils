#pragma once

#include <cstddef>

namespace utils
{
  class differentiable
  {
  public:
    virtual ~differentiable() = default;

    /**
     * @brief Pure virtual function call operator to evaluate a function at a given point.
     *
     * This operator is intended to be overridden by derived classes to provide
     * specific implementations for evaluating a function at a given point.
     *
     * @param x Pointer to an array of double values representing the point at which
     *          the function is to be evaluated.
     * @param n The size of the array pointed to by x.
     * @return Pointer to an array of double values representing the result of the
     *         function evaluation. The caller is responsible for managing the memory
     *         of the returned array.
     */
    virtual double *operator()(const double *x, const std::size_t n) const = 0;

    /**
     * @brief Pure virtual function to compute the derivative of a function.
     *
     * This function should be overridden by derived classes to provide the
     * implementation for computing the derivative of a function at a given
     * point.
     *
     * @param x Pointer to an array of double values representing the point
     *          at which the derivative is to be computed.
     * @param n The size of the array pointed to by x.
     * @return A pointer to an array of double values representing the
     *         computed derivative.
     */
    virtual double *derivative(const double *x, const std::size_t n) const = 0;
  };
} // namespace utils
