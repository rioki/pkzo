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

#ifndef _PKZO_ASYNC_H_
#define _PKZO_ASYNC_H_

#include "config.h"

#include <cassert>
#include <functional>
#include <thread>
#include <future>
#include <mutex>

namespace pkzo::async
{
    //!
    //! Thread Safe Queue
    //!
    //! This is a thread safe implementation of a queue.
    //!
    //! @note There is no really safe way to copy a queue, so this
    //! queue is not copyable or asingable.
    template <typename T, class Container = std::deque<T>>
    class queue
    {
    public:
        typedef Container                           container_type;
        typedef typename Container::value_type      value_type;
        typedef typename Container::size_type       size_type;
        typedef typename Container::reference       reference;
        typedef typename Container::const_reference const_reference;

        //! Create an empty queue.
        queue() {}

        //! Initialize the queue with values.
        //!
        //! @param c the container to initialize the queue with
        explicit queue(const Container& c)
        : container(c) {}

        //! Initialize the queue with a reange of values.
        //!
        //! @param begin an iterator to the beginning of the range
        //! @param end an iterator to the one beond the end of the range
        template <class Iterator>
        queue(const Iterator& begin, const Iterator& end)
        : container(begin, end) {}

        queue(const queue& other) = delete;

        //! Destructor
        ~queue()
        {
            wake();
        }

        queue& operator = (const queue& other) = delete;

        //! Push a value onto the queue.
        //!
        //! @param value the value to push onto the queue
        //!
        //! This method will push the value onto the queue and
        //! wake up a thread that is wating in pop_wait.
        void push(const value_type& value)
        {
            auto lock = std::unique_lock<std::mutex>{mutex};
            container.push_back(value);
            cond.notify_one();
        }

        //! Pop a value of the queue.
        //!
        //! @param value the value of the pop
        //! @return true if a value was poped of the queue
        //!
        //! This method will try to pop a value off the queue. If no value is
        //! in the queue, it will return false.
        bool pop(value_type& value)
        {
            auto lock = std::unique_lock<std::mutex>{mutex};
            if (!container.empty())
            {
                value = container.front();
                container.pop_front();
                return true;
            }
            else
            {
                return false;
            }
        }

        //! Pop a value of the queue, wait for a defined duration if nessesary.
        //!
        //! @param value the value of the pop
        //! @param duration the duration to wait for
        //! @return true if a value was poped of the queue
        //!
        //! This method will try to pop a value off the queue. If no value is
        //! in the queue, it will wait until either a value is pushed onto the
        //! queue or wake is called.
        bool pop_wait(value_type& value, std::chrono::milliseconds duration)
        {
            auto lock = std::unique_lock<std::mutex>{mutex};

            if (container.empty())
            {
                cond.wait_for(lock, duration);
            }

            if (!container.empty())
            {
                value = container.front();
                container.pop_front();
                return true;
            }
            else
            {
                return false;
            }
        }

        //! Wake up any threads that are wating in pop_wait.
        void wake()
        {
            cond.notify_all();
        }

    private:
        std::mutex              mutex;
        std::condition_variable cond;
        Container               container;
    };

    //! Thread Pool
    class PKZO_EXPORT thread_pool
    {
    public:
        //! Contruct empty thread pool.
        //!
        //! The default constructor will create a thread pool, but with no threads.
        //! It can be used to create an instance on the stack that can later accept
        //! a running thread pool with move assignment.
        thread_pool() noexcept;

        //! Create a thread pool.
        //!
        //! @param thread_func The thread function each thread in the pool executes.
        //! @param concurency The number of threads to run concurently.
        //!
        //! This constructor will create @arg concurency threads that execute @arg thread_func.
        thread_pool(std::function<void ()> thread_func, size_t concurency);

        thread_pool(const thread_pool&) = delete;

        //! Move Constructor
        thread_pool(thread_pool&& other) noexcept;

        //! Destructor
        //!
        //! @warning If the thread pool is not joined, the underlying std::thread
        //! objects will invoke std::terminate.
        ~thread_pool();

        thread_pool& operator = (const thread_pool&) = delete;

        //! Move Asignment
        thread_pool& operator = (thread_pool&& other) noexcept;

        //! Get the concurency of the thread pool.
        size_t get_concurency() const;

        //! Join each thread in the pool.
        //!
        //! Calling join ensures that each thread function terminates and
        //! the coresponsing memory is freed.
        void join();

        //! Swap thread pool.
        void swap(thread_pool& other) noexcept;

    private:
        std::vector<std::thread> threads;
    };

    //! Set the main thead id.
    //!
    //! The main thread id is used to queue taks that should be execytued
    //! in the main thread, such as sync.
    PKZO_EXPORT void set_main_thread_id(const std::thread::id& id) noexcept;
    PKZO_EXPORT std::thread::id get_main_thread_id() noexcept;

    //! Execture action asynconously.
    PKZO_EXPORT void async(const std::function<void ()>& func) noexcept;

    //! Execture action asyncronously with result.
    template <typename T>
    std::future<T> async(const std::function<T()>& func) noexcept
    {
        auto task = std::make_unique<std::packaged_task>(func);
        auto future = task->get_future();
        async([move(task)] () {
            task();
        });
        return future;
    }

    //! Delay action until next time tick is called on this thread.
    PKZO_EXPORT void delay(const std::function<void ()>& func) noexcept;

    //! Queue action to be executed by the main thread.
    PKZO_EXPORT void sync(const std::function<void ()>& func) noexcept;

    //! Queue action to be exectued by the given thread.
    //!
    //! This function will take the given function ans shedule it to be executed
    //! the given thread. The thread will need to prediodically call sync_point.
    //!
    //! @param thread the tread to call the function on.
    //! @param func the function to call.
    PKZO_EXPORT void sync(const std::thread::id& thread, const std::function<void ()>& func) noexcept;

    //! Queue action to be exectued by the given thread with result.
    template <typename T>
    std::future<T> sync(const std::thread::id& thread, const std::function<T()>& func) noexcept
    {
        assert(thread != std::this_thread::get_id());
        auto task = std::make_unique<std::packaged_task>(func);
        auto future = task->get_future();
        sync(thread, [move(task)] () {
            task();
        });
        return future;
    }

    //! Execute alle queueed tasks for this thread.
    //!
    //! This function will execute any outstanding sync calls.
    PKZO_EXPORT void sync_point();
}

#endif
