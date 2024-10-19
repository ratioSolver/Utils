#pragma once

#include <array>

namespace utils
{
  /**
   * @brief Computes the loss between the true values and the predicted values.
   *
   * This function calculates the sum of squared differences between the elements
   * of the true values array (`y_true`) and the predicted values array (`y_pred`).
   *
   * @tparam Fn Number of features.
   * @tparam Sn Number of samples.
   * @param y_true A 2D array containing the true values.
   * @param y_pred A 2D array containing the predicted values.
   * @return The computed loss as a double.
   */
  template <std::size_t Sn, std::size_t Fn>
  double loss(const std::array<std::array<double, Fn>, Sn> &y_true, const std::array<std::array<double, Fn>, Sn> &y_pred)
  {
    double loss = 0.0;
    for (std::size_t i = 0; i < Sn; ++i)
      for (std::size_t j = 0; j < Fn; ++j)
        loss += (y_true[i][j] - y_pred[i][j]) * (y_true[i][j] - y_pred[i][j]);
    return loss;
  }
} // namespace utils
