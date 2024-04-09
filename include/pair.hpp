#pragma once

namespace utils
{
  template <typename T1, typename T2>
  struct pair
  {
    bool operator<(const pair<T1, T2> &other) const { return first < other.first || (!(other.first < first) && second < other.second); }

    T1 first;
    T2 second;
  };
} // namespace utils