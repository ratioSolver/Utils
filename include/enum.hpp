#pragma once

#include <string>

namespace utils
{
  /**
   * @brief Base class for enum values.
   *
   */
  class enum_val
  {
  public:
    virtual ~enum_val() = default;

    virtual std::string to_string() const { return std::to_string(reinterpret_cast<uintptr_t>(this)); }
  };
} // namespace utils
