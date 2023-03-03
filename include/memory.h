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
    countable(bool self = false) : m_count(self) {}
    virtual ~countable() = default;

  private:
    size_t m_count;
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
    c_ptr(T *m_ptr = nullptr) : m_ptr(m_ptr)
    {
      if (m_ptr)
        m_ptr->m_count++;
    }
    c_ptr(const c_ptr &other) : m_ptr(other.m_ptr)
    {
      if (m_ptr)
        m_ptr->m_count++;
    }
    ~c_ptr()
    {
      if (!m_ptr)
        return;
      m_ptr->m_count--;
      if (!m_ptr->m_count)
        delete m_ptr;
    }

    /**
     * @brief Returns true if the pointer is not null.
     *
     * @return true If the pointer is not null.
     * @return false If the pointer is null.
     */
    operator bool() const { return m_ptr != nullptr; }

    /**
     * @brief Returns true if the pointers are equal.
     *
     * @param other The other pointer.
     * @return true If the pointers are equal.
     * @return false If the pointers are not equal.
     */
    bool operator==(const c_ptr &other) const { return m_ptr == other.m_ptr; }

    /**
     * @brief Dereference the pointer.
     *
     * @return T& The object pointed to.
     */
    T &operator*() const { return *m_ptr; }
    /**
     * @brief Returns the pointer.
     *
     * @return T* The pointer.
     */
    T *operator->() const { return m_ptr; }

    c_ptr &operator=(const c_ptr &other)
    {
      if (this != &other)
      {
        if (m_ptr)
        {
          m_ptr->m_count--;
          if (!m_ptr->m_count)
            delete m_ptr;
        }
        m_ptr = other.m_ptr;
        if (m_ptr)
          m_ptr->m_count++;
      }
      return *this;
    }

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
    u_ptr(T *m_ptr = nullptr) : m_ptr(m_ptr) {}
    u_ptr(const u_ptr &) = delete;
    u_ptr(u_ptr &&other) : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
    ~u_ptr() { delete m_ptr; }

    void reset(T *ptr)
    {
      delete m_ptr;
      m_ptr = ptr;
    }

    void swap(u_ptr<T> &other)
    {
      T *tmp = m_ptr;
      m_ptr = other.m_ptr;
      other.m_ptr = tmp;
    }

    u_ptr &operator=(const u_ptr &) = delete;
    u_ptr &operator=(u_ptr &&other)
    {
      if (this != &other)
      {
        delete m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
      }
      return *this;
    }

    operator bool() const { return m_ptr != nullptr; }

    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }

  private:
    T *m_ptr = nullptr;
  };
} // namespace utils