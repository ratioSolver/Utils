#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

namespace utils
{
  /**
   * @brief Compute the combinations of the elements of a vector.
   *
   * @tparam T Type of the elements of the vector.
   * @param v The vector.
   * @param n The number of elements of the combinations.
   * @return std::vector<std::vector<T>> Combinations of the elements of the vector.
   */
  template <typename T>
  std::vector<std::vector<T>> combinations(const std::vector<T> &v, const size_t &n) noexcept
  {
    assert(v.size() >= n);
    std::vector<std::vector<T>> combs;
    std::string bitmask(n, 1);   // K leading 1's
    bitmask.resize(v.size(), 0); // N-K trailing 0's

    // permute bitmask..
    do
    {
      std::vector<T> c_comb;
      c_comb.reserve(n);
      // [0..N-1] integers
      for (size_t i = 0; i < v.size(); ++i)
        if (bitmask.at(i))
          c_comb.push_back(v[i]);
      combs.push_back(c_comb);
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    return combs;
  }
} // namespace utils