#include "timer.hpp"
#include <chrono>

namespace utils
{
    timer::timer(const size_t &tick_dur, std::function<void(void)> f) : tick_duration(tick_dur), fun(f) {}

    void timer::start()
    {
        if (executing.exchange(true, std::memory_order_acq_rel))
            stop();
        tick_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(tick_duration);
        th = std::thread([this]()
                         {
            while (executing.load(std::memory_order_acquire)) {
                fun();
                std::this_thread::sleep_until(tick_time);
                tick_time += std::chrono::milliseconds(tick_duration);
            } });
    }
extern/plexa/src/timer.cpp
    void timer::stop()
    {
        executing.store(false, std::memory_order_release);
        std::lock_guard<std::mutex> lock(mtx);
        if (th.joinable())
            th.join();
    }
} // namespace utils