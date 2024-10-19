#pragma once

#include <cstddef>

namespace utils
{
  /**
   * @brief Computes the Mean Squared Error (MSE) between two arrays.
   *
   * This function calculates the MSE, which is a measure of the average squared difference
   * between the predicted values and the actual values. It is commonly used in regression
   * analysis to assess the accuracy of a model.
   *
   * @param y_true Pointer to the array of true values.
   * @param y_pred Pointer to the array of predicted values.
   * @param n The number of elements in the arrays.
   * @return The mean squared error between the true and predicted values.
   */
  double mse(const double *y_true, const double *y_pred, const std::size_t n)
  {
    double sum = 0;
    for (std::size_t i = 0; i < n; i++)
      sum += (y_true[i] - y_pred[i]) * (y_true[i] - y_pred[i]);
    return sum / n;
  }
} // namespace utils
