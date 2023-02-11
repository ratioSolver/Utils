#pragma once

#include <cstddef>

namespace utils
{
  template <typename T>
  class c_ptr;

  /**
   * @brief A countable object that can be used to count the number of references.
   * 
   */
  class countable
  {
    template <typename T>
    friend class c_ptr;

  public:
    countable(bool count = false) : m_count(count) {}
    virtual ~countable() = default;

  private:
    size_t m_count;
  };

  /**
   * @brief A countable object that can be used to count the number of references.
   * 
   */
  template <typename T>
  class self_countable : public countable
  {
  public:
    self_countable() : countable(true), m_self(static_cast<T *>(this)) {}

  protected:
    c_ptr<T> &self() { return m_self; }

  private:
    c_ptr<T> m_self;
  };

  /**
   * @brief A countable pointer that deletes the object when the last reference is
   * deleted.
   *
   * @tparam T The type of the object to be deleted.
   */
  template <typename T>
  class c_ptr
  {
  public:
    explicit c_ptr(T *m_ptr) : m_ptr(m_ptr) { m_ptr->m_count++; }
    explicit c_ptr(const c_ptr &other) : m_ptr(other.m_ptr) { m_ptr->m_count++; }
    ~c_ptr()
    {
      m_ptr->m_count--;
      if (!m_ptr->m_count)
      {
        delete m_ptr;
        m_ptr = nullptr;
      }
    }

    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }

  private:
    T *m_ptr = nullptr;
  };

  /**
   * @brief A unique pointer that deletes the object when it goes out of scope.
   *
   * @tparam T The type of the object to be deleted.
   */
  template <typename T>
  class u_ptr
  {
  public:
    u_ptr(T *m_ptr) : m_ptr(m_ptr) {}
    u_ptr(const u_ptr &) = delete;
    u_ptr(u_ptr &&other) : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
    ~u_ptr() { delete m_ptr; }

    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }

  private:
    T *m_ptr = nullptr;
  };
} // namespace utils
