#include "timer.hpp"
#include <chrono>

namespace utils
{
    timer::timer(const size_t &tick_dur, std::function<void(void)> f) : tick_duration(tick_dur), fun(f) {}

    void timer::start()
    {
        executing.store(true, std::memory_order_release);
        tick_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(tick_duration);
        th = std::thread([this]()
                         {
            while (executing.load(std::memory_order_acquire)) {
                fun(); // execute the callback function
                std::this_thread::sleep_until(tick_time); // sleep until the next tick
                tick_time += std::chrono::milliseconds(tick_duration); // update the tick time
            } });
    }

    void timer::stop()
    {
        executing.store(false, std::memory_order_release);
        std::lock_guard<std::mutex> _(mtx);
        if (th.joinable())
            th.join();
    }
} // namespace utils