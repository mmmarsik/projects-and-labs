#pragma once
#include <atomic>

class SharedMutex
{
public:
    void lock() {
        while (true) {
            int threads_cnt_ = 0;
            if (read_state_.compare_exchange_weak(threads_cnt_, -1))
                break; 
        }
    }

    void unlock()
    {
        read_state_.store(0);
    }

    void lock_shared()
    {
        while (true)
        {
            int threads_cnt_ = read_state_.load();
            if (threads_cnt_ != -1)
            {
                if (read_state_.compare_exchange_weak(threads_cnt_, threads_cnt_ + 1)){
                    break;
                }
            }
        }
    }

    void unlock_shared()
    {
        read_state_.fetch_sub(1);
    }

private:
    std::atomic<int> read_state_{0}; // -1 если кто-то пишет 
};