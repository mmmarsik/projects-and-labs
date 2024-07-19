#pragma once

#include <cstdint>
#include <mutex>
#include <set>
#include <atomic>
#include <stdexcept>
#include <vector>
#include <thread>

/*
 * Класс PrimeNumbersSet -- множество простых чисел в каком-то диапазоне
 */
class PrimeNumbersSet {
public:
    PrimeNumbersSet() : nanoseconds_under_mutex_(0), nanoseconds_waiting_mutex_(0) {}

    // Проверка, что данное число присутствует в множестве простых чисел
    bool IsPrime(uint64_t number) const {
        return primes_.find(number) != primes_.end();
    }

    // Получить следующее по величине простое число из множества
    uint64_t GetNextPrime(uint64_t number) const {
        auto it = primes_.upper_bound(number);
        if (it == primes_.end()) {
            throw std::invalid_argument("no such value");
        }
        return *it;
    }

    /*
     * Найти простые числа в диапазоне [from, to) и добавить в множество
     * Во время работы этой функции нужно вести учет времени, затраченного на ожидание лока мюьтекса,
     * а также времени, проведенного в секции кода под локом
     */
    void AddPrimesInRange(uint64_t from, uint64_t to) {
        std::vector<uint64_t> addpr;

        for (uint64_t val = std::max(from, (uint64_t) 2); val < to; ++val) {
            bool is_prime = true;

            for (uint64_t i = 2; i * i <= val; ++i) {
                if (val % i == 0) {
                    is_prime = false;
                    break;
                }
            }

            if (is_prime) {
                addpr.push_back(val);
            }
        }

        if (!addpr.empty()) {
            std::chrono::time_point start_time_waiting_mutex = std::chrono::high_resolution_clock::now();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::lock_guard<std::mutex> lock(set_mutex_);
            std::chrono::time_point end_time_waiting_mutex = std::chrono::high_resolution_clock::now();
            primes_.insert(addpr.begin(), addpr.end());
            auto end_time_working_under_mutex = std::chrono::high_resolution_clock::now();
            nanoseconds_waiting_mutex_ += (end_time_waiting_mutex - start_time_waiting_mutex).count();
            nanoseconds_under_mutex_ += (end_time_working_under_mutex - end_time_waiting_mutex).count();


        }
    }


    // Посчитать количество простых чисел в диапазоне [from, to)
    size_t GetPrimesCountInRange(uint64_t from, uint64_t to) const {
        std::unique_lock<std::mutex> lock(set_mutex_);
        return std::distance(primes_.lower_bound(from), primes_.upper_bound(to));
    }


    // Получить наибольшее простое число из множества
    uint64_t GetMaxPrimeNumber() const {
        {
            std::lock_guard<std::mutex> lock(set_mutex_);
            if (!primes_.empty()) {
                return *(primes_.rbegin());
            }
        }

        return 0;
    }


    // Получить суммарное время, проведенное в ожидании лока мьютекса во время работы функции AddPrimesInRange
    std::chrono::nanoseconds GetTotalTimeWaitingForMutex() const {
        return std::chrono::nanoseconds(nanoseconds_waiting_mutex_);
    }

    // Получить суммарное время, проведенное в коде под локом во время работы функции AddPrimesInRange
    std::chrono::nanoseconds GetTotalTimeUnderMutex() const {
        return std::chrono::nanoseconds(nanoseconds_under_mutex_);
    }

private:
    std::set<uint64_t> primes_;
    mutable std::mutex set_mutex_;
    std::atomic<uint64_t> nanoseconds_under_mutex_, nanoseconds_waiting_mutex_;
};
