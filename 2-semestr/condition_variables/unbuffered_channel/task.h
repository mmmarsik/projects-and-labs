#pragma once

#include <mutex>
#include <condition_variable>
#include <optional>

class TimeOut : public std::exception {
    const char *what() const noexcept override {
        return "Timeout";
    }
};

template<typename T>
class UnbufferedChannel {
public:

    void Put(const T &data) {
        std::unique_lock<std::mutex> lock(storage_mutex);

        while (storage.has_value()) {
            cv_for_writer.wait(lock);
        }

        storage.emplace(data);
        cv_for_reader.notify_one();

        cv_for_exchange.wait(lock);
        cv_for_writer.notify_one();

    }

    T Get(std::chrono::milliseconds timeout = std::chrono::milliseconds(0)) {
        std::unique_lock<std::mutex> lock(storage_mutex);

        if (!cv_for_reader.wait_until(lock, std::chrono::high_resolution_clock::now() + timeout,
                                      [this]() { return storage.has_value(); })) {
            throw TimeOut();
        }

        T result = storage.value();
        storage.reset();
        cv_for_exchange.notify_one();

        return result;
    }

private:
    std::optional<T> storage;
    std::mutex storage_mutex;
    std::condition_variable cv_for_writer;
    std::condition_variable cv_for_reader;
    std::condition_variable cv_for_exchange;
};
