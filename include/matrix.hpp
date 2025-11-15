#pragma once

#include <array>

namespace utils
{
  template <std::size_t nr, std::size_t nc, typename T>
  using matrix = std::array<std::array<T, nc>, nr>;

  template <std::size_t nr, std::size_t nc, typename T>
  matrix<nc, nr, T> transpose(const matrix<nr, nc, T> &m)
  {
    matrix<nc, nr, T> res;
    for (std::size_t i = 0; i < nr; ++i)
      for (std::size_t j = 0; j < nc; ++j)
        res[j][i] = m[i][j];
    return res;
  }

  template <size_t nr, size_t inner, size_t nc, typename T>
  matrix<nr, nc, T> matmul(const matrix<nr, inner, T> &A, const matrix<nc, inner, T> &B)
  {
    matrix<nr, nc, T> res;

    for (std::size_t r = 0; r < nr; r++)
    {
      const auto &A_row = A[r];
      auto &result_row = res[r];
      for (std::size_t c = 0; c < nc; c++)
      {
        const auto &B_col = B[c];

        T accum = 0;
        for (std::size_t i = 0; i < inner; i++)
          accum += A_row[i] * B_col[i];
        result_row[c] = accum;
      }
    }

    return res;
  }
} // namespace utils
