#pragma once

#include <utility>
#include <cstddef>

namespace utils
{
  /**
   * @class u_ptr
   * @brief A simple unique pointer implementation.
   *
   * This class provides a basic implementation of a unique pointer, which ensures
   * that only one instance of the pointer can own a given resource at a time.
   *
   * @tparam T The type of the object being managed.
   */
  template <typename T>
  class u_ptr
  {
    template <typename U>
    friend class u_ptr; // Allows s_ptr<U> to access s_ptr<T>'s private members
  public:
    /**
     * @brief Constructs a unique pointer with the given raw pointer.
     *
     * @param ptr The raw pointer to manage.
     */
    u_ptr(T *ptr = nullptr) : ptr(ptr) {}
    /**
     * @brief Deleted copy constructor to prevent copying.
     *
     * @param other The other unique pointer to copy from.
     */
    u_ptr(const u_ptr &other) = delete;
    /**
     * @brief Move constructor to transfer ownership from another unique pointer.
     *
     * @param other The other unique pointer to move from.
     */
    u_ptr(u_ptr &&other) : ptr(other.ptr) { other.ptr = nullptr; }
    /**
     * @brief Move constructor to transfer ownership from another unique pointer.
     *
     * @tparam U The type of the object being managed by the other unique pointer.
     * @param other The other unique pointer to move from.
     */
    template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
    u_ptr(u_ptr<U> &&other) : ptr(other.ptr) { other.ptr = nullptr; }
    /**
     * @brief Destructor that deletes the managed object.
     */
    ~u_ptr() { delete ptr; }

    /**
     * @brief Retrieves the raw pointer to the managed object.
     *
     * @return T* Pointer to the managed object.
     */
    T *get() const { return ptr; }

    /**
     * @brief Overloaded arrow operator to access the managed object.
     *
     * @return T* Pointer to the managed object.
     */
    T *operator->() const { return ptr; }
    /**
     * @brief Overloaded dereference operator to access the managed object.
     *
     * @return T& Reference to the managed object.
     */
    T &operator*() const { return *ptr; }

    /**
     * @brief Conversion operator to check if the unique pointer is valid.
     *
     * @return bool True if the unique pointer is valid, false otherwise.
     */
    operator bool() const { return ptr != nullptr; }

    /**
     * @brief Deleted copy assignment operator to prevent copying.
     *
     * @param other The other unique pointer to copy from.
     * @return u_ptr& Reference to this unique pointer.
     */
    u_ptr &operator=(const u_ptr &other) = delete;
    /**
     * @brief Move assignment operator to transfer ownership from another unique pointer.
     *
     * @param other The other unique pointer to move from.
     * @return u_ptr& Reference to this unique pointer.
     */
    u_ptr &operator=(u_ptr &&other)
    {
      if (this != &other)
      {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
      }
      return *this;
    }

  private:
    T *ptr;
  };

  /**
   * @brief Creates a unique pointer to an object of type Tp.
   *
   * This function constructs an object of type Tp and wraps it in a unique pointer.
   * It forwards the provided arguments to the constructor of Tp.
   *
   * @tparam Tp The type of the object to create.
   * @tparam Args The types of the arguments to pass to the constructor of Tp.
   * @param args The arguments to pass to the constructor of Tp.
   * @return u_ptr<Tp> A unique pointer to the newly created object of type Tp.
   */
  template <typename Tp, typename... Args>
  u_ptr<Tp> make_u_ptr(Args &&...args) { return u_ptr<Tp>(new Tp(std::forward<Args>(args)...)); }

  /**
   * @class s_ptr
   * @brief A simple shared pointer implementation.
   *
   * This class provides a basic implementation of a shared pointer, which allows
   * multiple instances of the pointer to own a given resource at the same time.
   *
   * @tparam T The type of the object being managed.
   */
  template <typename T>
  class s_ptr
  {
    template <typename U>
    friend class s_ptr; // Allows s_ptr<U> to access s_ptr<T>'s private members

  public:
    /**
     * @brief Constructs a shared pointer with the given raw pointer.
     *
     * @param ptr The raw pointer to manage.
     */
    s_ptr(T *ptr = nullptr) : ptr(ptr), ref_count(new size_t(0))
    {
      if (ptr)
        *ref_count = 1;
    }
    /**
     * @brief Copy constructor to share ownership with another shared pointer.
     *
     * @param other The other shared pointer to copy from.
     */
    s_ptr(const s_ptr &other) : ptr(other.ptr), ref_count(other.ref_count)
    {
      if (ptr)
        ++(*ref_count);
    }
    /**
     * @brief Copy constructor to share ownership with another shared pointer.
     *
     * @tparam U The type of the object being managed by the other shared pointer.
     * @param other The other shared pointer to copy from.
     */
    template <typename U, typename = std::enable_if_t<std::is_base_of_v<U, T>>>
    s_ptr(const s_ptr<U> &other) : ptr(static_cast<T *>(other.ptr)), ref_count(other.ref_count)
    {
      if (ptr)
        ++(*ref_count);
    }
    /**
     * @brief Move constructor to transfer ownership from another shared pointer.
     *
     * @param other The other shared pointer to move from.
     */
    s_ptr(s_ptr &&other) : ptr(other.ptr), ref_count(other.ref_count)
    {
      other.ptr = nullptr;
      other.ref_count = nullptr;
    }
    /**
     * @brief Move constructor to transfer ownership from another shared pointer.
     *
     * @tparam U The type of the object being managed by the other shared pointer.
     * @param other The other shared pointer to move from.
     */
    template <typename U, typename = std::enable_if_t<std::is_base_of_v<T, U>>>
    s_ptr(s_ptr<U> &&other) : ptr(other.ptr), ref_count(other.ref_count)
    {
      other.ptr = nullptr;
      other.ref_count = nullptr;
    }
    /**
     * @brief Destructor that deletes the managed object if no other shared pointers own it.
     */
    ~s_ptr() { release(); }

    /**
     * @brief Copy assignment operator to share ownership with another shared pointer.
     *
     * @param other The other shared pointer to copy from.
     * @return s_ptr& Reference to this shared pointer.
     */
    s_ptr &operator=(const s_ptr &other)
    {
      if (this != &other)
      {
        release();
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ptr)
          ++(*ref_count);
      }
      return *this;
    }

    /**
     * @brief Move assignment operator to transfer ownership from another shared pointer.
     *
     * @param other The other shared pointer to move from.
     * @return s_ptr& Reference to this shared pointer.
     */
    s_ptr &operator=(s_ptr &&other)
    {
      if (this != &other)
      {
        release();
        ptr = other.ptr;
        ref_count = other.ref_count;
        other.ptr = nullptr;
        other.ref_count = nullptr;
      }
      return *this;
    }

    /**
     * @brief Retrieves the raw pointer to the managed object.
     *
     * @return T* Pointer to the managed object.
     */
    T *get() const { return ptr; }

    /**
     * @brief Overloaded arrow operator to access the managed object.
     *
     * @return T* Pointer to the managed object.
     */
    T *operator->() const { return ptr; }
    /**
     * @brief Overloaded dereference operator to access the managed object.
     *
     * @return T& Reference to the managed object.
     */
    T &operator*() const { return *ptr; }

    /**
     * @brief Conversion operator to check if the shared pointer is valid.
     *
     * @return bool True if the shared pointer is valid, false otherwise.
     */
    operator bool() const { return ptr != nullptr; }

    /**
     * @brief Returns the number of shared pointers owning the managed object.
     *
     * @return size_t The number of shared pointers owning the managed object.
     */
    size_t use_count() { return *ref_count; }

  private:
    inline void release()
    {
      if (ptr && --(*ref_count) == 0)
      {
        delete ptr;
        delete ref_count;
      }
    }

  private:
    T *ptr;
    size_t *ref_count;
  };

  template <typename Tp, typename... Args>
  s_ptr<Tp> make_s_ptr(Args &&...args) { return s_ptr<Tp>(new Tp(std::forward<Args>(args)...)); }

  template <class To, class From>
  s_ptr<To> s_ptr_cast(const s_ptr<From> &sp) { return s_ptr<To>(sp); }

  /**
   * @class ref_wrapper
   * @brief A simple reference wrapper implementation.
   *
   * This class provides a basic implementation of a reference wrapper, which allows
   * a reference to be treated as an object.
   *
   * @tparam T The type of the reference being wrapped.
   */
  template <typename T>
  class ref_wrapper
  {
  public:
    /**
     * @brief Constructs a reference wrapper with the given reference.
     *
     * @param ref The reference to wrap.
     */
    ref_wrapper(T &ref) : ref(&ref) {}
    /**
     * @brief Copy constructor to share ownership with another reference wrapper.
     *
     * @param other The other reference wrapper to copy from.
     */
    ref_wrapper(const ref_wrapper &other) : ref(other.ref) {}
    /**
     * @brief Copy assignment operator to share ownership with another reference wrapper.
     *
     * @param other The other reference wrapper to copy from.
     * @return ref_wrapper& Reference to this reference wrapper.
     */
    ref_wrapper &operator=(const ref_wrapper &other)
    {
      ref = other.ref;
      return *this;
    }

    /**
     * @brief Equality operator for ref_wrapper.
     *
     * This operator compares the current ref_wrapper object with another ref_wrapper object.
     *
     * @param other The ref_wrapper object to compare with.
     * @return true if both ref_wrapper objects are equal, false otherwise.
     */
    bool operator==(const ref_wrapper &other) const { return ref == other.ref; }

    /**
     * @brief Retrieves the reference being wrapped.
     *
     * @return T& Reference being wrapped.
     */
    T *operator->() const { return ref; }
    /**
     * @brief Retrieves the reference being wrapped.
     *
     * @return T& Reference being wrapped.
     */
    T &operator*() const { return *ref; }

  private:
    T *ref;
  };
} // namespace utils
