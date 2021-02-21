//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "pch.h"
#include "async.h"

namespace pkzo::async
{
    using namespace std::literals::chrono_literals;

    // Thread Pool

    thread_pool::thread_pool() noexcept {}

    thread_pool::thread_pool(std::function<void()> thread_func, size_t concurency)
    {
        assert(thread_func);
        assert(concurency > 0);
        for (size_t i = 0; i < concurency; i++)
        {
            threads.emplace_back(std::thread(thread_func));
        }
    }

    thread_pool::thread_pool(thread_pool&& other) noexcept
    {
        swap(other);
    }

    thread_pool::~thread_pool() = default;

    thread_pool& thread_pool::operator = (thread_pool&& other) noexcept
    {
        swap(other);
        return *this;
    }

    size_t thread_pool::get_concurency() const
    {
        return threads.size();
    }

    void thread_pool::join()
    {
        for (auto& thread : threads)
        {
            thread.join();
        }
        threads.clear();
    }

    void thread_pool::swap(thread_pool& other) noexcept
    {
        threads.swap(other.threads);
    }

    // Main Thread

    std::atomic<std::thread::id> main_thread_id;
    void set_main_thread_id(const std::thread::id& id) noexcept
    {
        main_thread_id = id;
    }

    std::thread::id get_main_thread_id() noexcept
    {
        return main_thread_id;
    }

    // Async

    class TaskPool
    {
    public:
        TaskPool() = default;

        ~TaskPool()
        {
            running = false;
            thread_pool.join();
        }

        void push(const std::function<void()>& func)
        {
            task_queue.push(func);
        }

    private:
        std::atomic<bool> running = true;
        thread_pool thread_pool = {[this] () {thread_func();}, std::thread::hardware_concurrency()};
        queue<std::function<void ()>> task_queue;

        void thread_func()
        {
            while (running)
            {
                try
                {
                    std::function<void ()> task;
                    if (task_queue.pop_wait(task, 100ms))
                    {
                        task();
                    }
                    sync_point();
                }
                catch (std::exception& /*ex*/)
                {
                    // TODO Trace?
                    assert(false);
                }
                catch (...)
                {
                    assert(false);
                }
            }
        }
    };
    TaskPool task_pool;

    void async(const std::function<void()>& func) noexcept
    {
        assert(func);
        task_pool.push(func);
    }

    // Sync

    std::mutex tasks_mutex;
    std::map<std::thread::id, std::vector<std::function<void ()>>> tasks;

    void delay(const std::function<void()>& func) noexcept
    {
        sync(std::this_thread::get_id(), func);
    }

    void sync(const std::function<void()>& func) noexcept
    {
        assert(main_thread_id != std::thread::id());
        sync(main_thread_id, func);
    }

    void sync(const std::thread::id& thread, const std::function<void()>& func) noexcept
    {
        assert(func);
        std::scoped_lock<std::mutex> sl(tasks_mutex);
        tasks[thread].push_back(func);
    }

    std::vector<std::function<void()>> get_this_threads_tasks() noexcept
    {
        std::scoped_lock<std::mutex> sl(tasks_mutex);
        auto this_threads_tasks = tasks[std::this_thread::get_id()];
        tasks[std::this_thread::get_id()] = std::vector<std::function<void ()>>();
        return this_threads_tasks;
    }

    void sync_point()
    {
        auto tasks = get_this_threads_tasks();
        for (const auto& task : tasks)
        {
            task();
        }
    }
}
