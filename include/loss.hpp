#pragma once

#include <cmath>

namespace utils
{
  /**
   * @brief Computes the Mean Squared Error (MSE) between two arrays.
   *
   * This function calculates the MSE, which is a measure of the average of the squares of the errors
   * between the true values and the predicted values.
   *
   * @tparam T The data type of the input arrays.
   * @param y_true Pointer to the array of true values.
   * @param y_pred Pointer to the array of predicted values.
   * @param n The number of elements in the arrays.
   * @return The computed Mean Squared Error.
   */
  template <typename T>
  [[nodiscard]] T mse(const T *y_true, const T *y_pred, const std::size_t n)
  {
    double sum = 0;
    for (std::size_t i = 0; i < n; i++)
      sum += (y_true[i] - y_pred[i]) * (y_true[i] - y_pred[i]);
    return sum / n;
  }

  /**
   * @brief Computes the Mean Absolute Error (MAE) between two arrays.
   *
   * This function calculates the MAE, which is a measure of the average of the absolute differences
   * between the true values and the predicted values.
   *
   * @tparam T The data type of the input arrays.
   * @param y_true Pointer to the array of true values.
   * @param y_pred Pointer to the array of predicted values.
   * @param n The number of elements in the arrays.
   * @return The computed Mean Absolute Error.
   */
  template <typename T>
  [[nodiscard]] T mae(const T *y_true, const T *y_pred, const std::size_t n)
  {
    double sum = 0;
    for (std::size_t i = 0; i < n; i++)
      sum += std::abs(y_true[i] - y_pred[i]);
    return sum / n;
  }
} // namespace utils
