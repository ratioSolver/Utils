#pragma once

namespace utils
{
  template <typename T1, typename T2>
  struct pair
  {
    template <typename U1, typename U2>
    bool operator<(const pair<U1, U2> &x, const pair<U1, U2> &y) { return x.first < y.first || (!(y.first < x.first) && x.second < y.second); }

    T1 first;
    T2 second;
  };
} // namespace utils