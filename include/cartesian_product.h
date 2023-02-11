#pragma once

#include <vector>
#include <algorithm>
#include <cassert>

namespace utils
{
  /**
   * @brief Compute the cartesian product of a set of vectors.
   *
   * @tparam T Type of the elements of the vectors.
   * @param vs Set of vectors.
   * @return std::vector<std::vector<T>> Cartesian product of the vectors.
   */
  template <typename T>
  std::vector<std::vector<T>> cartesian_product(const std::vector<std::vector<T>> &vs) noexcept
  {
    assert(std::none_of(vs.cbegin(), vs.cend(), [](const auto &v)
                        { return v.empty(); }));
    std::vector<typename std::vector<T>::const_iterator> it;
    it.reserve(vs.size());
    for (const auto &v : vs)
      it.push_back(v.cbegin());

    std::vector<std::vector<T>> s;
    while (it[0] != vs[0].cend())
    {
      std::vector<T> c_v;
      for (const auto &i : it)
        c_v.push_back(*i);
      s.push_back(c_v);

      ++it[vs.size() - 1];
      for (size_t i = vs.size() - 1; (i > 0) && (it[i] == vs[i].cend()); --i)
      {
        it[i] = vs[i].cbegin();
        ++it[i - 1];
      }
    }
    return s;
  }
} // namespace utils