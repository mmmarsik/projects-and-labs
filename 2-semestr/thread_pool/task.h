#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <chrono>
#include <future>

/*
 * Требуется написать класс ThreadPool, реализующий пул потоков, которые выполняют задачи из общей очереди.
 * С помощью метода PushTask можно положить новую задачу в очередь
 * С помощью метода Terminate можно завершить работу пула потоков.
 * Если в метод Terminate передать флаг wait = true,
 *  то пул подождет, пока потоки разберут все оставшиеся задачи в очереди, и только после этого завершит работу потоков.
 * Если передать wait = false, то все невыполненные на момент вызова Terminate задачи, которые остались в очереди,
 *  никогда не будут выполнены.
 * После вызова Terminate в поток нельзя добавить новые задачи.
 * Метод IsActive позволяет узнать, работает ли пул потоков. Т.е. можно ли подать ему на выполнение новые задачи.
 * Метод GetQueueSize позволяет узнать, сколько задач на данный момент ожидают своей очереди на выполнение.
 * При создании нового объекта ThreadPool в аргументах конструктора указывается количество потоков в пуле. Эти потоки
 *  сразу создаются конструктором.
 * Задачей может являться любой callable-объект, обернутый в std::function<void()>.
 */

class ThreadPool
{
public:
    ThreadPool(size_t threadCount) : is_active(true), is_available_for_new_tasks(true)
    {
        for (size_t i = 0; i < threadCount; ++i)
        {
            threads.emplace_back(&ThreadPool::process_work, this);
        }
    }

    void PushTask(const std::function<void()> &task)
    {
        std::lock_guard<std::mutex> lock(q_mtx);
        if (!is_available_for_new_tasks)
        {
            throw std::exception();
        }
        q_tasks.emplace(std::move(task));
        q_cv.notify_one();
    }

    void Terminate(bool wait_)
    {
        std::unique_lock<std::mutex> lock(q_mtx);
        is_available_for_new_tasks = false;
        if (wait_)
        {
            q_cv.notify_all();
            t_cv.wait(lock, [this]()
                      { return q_tasks.empty(); });
        }
        is_active = false;
        q_cv.notify_all();
        
        lock.unlock();
        for (std::thread &thread : threads)
        {
            thread.join();
        }
    }

    bool IsActive() const
    {
        std::lock_guard<std::mutex> lock(q_mtx);
        return is_available_for_new_tasks;
    }

    size_t QueueSize() const
    {
        std::lock_guard<std::mutex> lock(q_mtx);
        return q_tasks.size();
    }

private:
    std::atomic<bool> is_active;
    std::atomic<bool> is_available_for_new_tasks;
    std::condition_variable q_cv;
    std::condition_variable t_cv;
    mutable std::mutex q_mtx;
    std::queue<std::function<void()>> q_tasks;
    std::vector<std::thread> threads;

    void process_work()
    {
        while (is_active)
        {
            std::unique_lock<std::mutex> lock(q_mtx);

            if (q_tasks.empty() && !is_available_for_new_tasks && is_active)
            {
                t_cv.notify_one();
            }

            q_cv.wait(lock, [this]()
                      { return !q_tasks.empty() || !is_active; });
            if (!is_active)
            {
                return;
            }

            if (!q_tasks.empty() && is)
            {
                std::function<void()> task = std::move(q_tasks.front());
                q_tasks.pop();
                lock.unlock();
                task();
            }
        }
    }
};

