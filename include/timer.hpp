#pragma once

#include <functional>
#include <atomic>
#include <thread>
#include <mutex>

namespace utils
{
  class timer final
  {
  public:
    timer(const size_t &tick_dur, std::function<void(void)> f);
    ~timer() { stop(); }

    /**
     * @brief Starts the timer.
     */
    void start();
    /**
     * @brief Stops the timer.
     */
    void stop();

  private:
    const size_t tick_duration; // the duration of each tick in milliseconds..
    std::function<void(void)> fun;
    std::chrono::steady_clock::time_point tick_time;
    std::atomic<bool> executing;
    std::thread th;
    std::mutex mtx;
  };
} // namespace utils
