// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <functional>
#include <map>
#include <mutex>

#include "debug.h"

namespace rex
{
    //! Handle to a signal / observer connection.
    //!
    //! @note The connection struct is to be considered opaque to the user.
    struct connection
    {
        size_t id = 0;
        void* signal = nullptr;
    };

    //! A thread safe signal multiplexer.
    //!
    //! @note The signal class is thread safe. You can connect, disconnect and
    //! emit from multiple threads, just keep the object alive. The thread that
    //! emits the signal is the same that will call the functions. The signal
    //! is secured by a mutex, thus it may create contention when emitting
    //! a signal with a function that runs long.
    template <typename... Args>
    class signal
    {
    public:
        signal() noexcept = default;
        ~signal() = default;

        //! Connect an observer to the signal.
        //!
        //! @param fun the lambda function that will be called when emit is called.
        //! @return the connection for this observer
        //!
        //! @warning If the context, like lambda captures, lifetime is shorter
        //! than the signal, the observer must be disconnected.
        connection connect(const std::function<void(Args...)>& fun) noexcept;

        //! Disconnect an observer.
        //!
        //! @param id the connection returned by connect
        void disconnect(connection id) noexcept;

        //! Emit a signal.
        //!
        //! Calls all observer functions with the given arguments and returns
        //! the number of called functions.
        //!
        //! @param args the values of this signal event
        //! @return the number of called functions
        size_t emit(Args... args) const;

        connection operator () (const std::function<void(Args...)>& fun)
        {
            return connect(fun);
        }

        void operator () (Args... args) const
        {
            emit(args...);
        }

    private:
        mutable
        std::mutex mutex;
        size_t last_id = 0;
        std::map<size_t, std::function<void (Args...)>> observers;

        signal(const signal<Args...>&) = delete;
        signal<Args...>& operator = (const signal<Args...>&) = delete;
    };

    template <typename... Args>
    connection signal<Args...>::connect(const std::function<void(Args...)>& fun) noexcept
    {
        check(fun);
        std::scoped_lock<std::mutex> sl(mutex);
        auto id = ++last_id;
        observers[id] = fun;
        return {id, this};
    }

    template <typename... Args>
    void signal<Args...>::disconnect(connection id) noexcept
    {
        check(id.signal == this);

        std::scoped_lock<std::mutex> sl(mutex);
        auto i = observers.find(id.id);
        assert(i != end(observers));
        observers.erase(i);
    }

    template <typename... Args>
    size_t signal<Args...>::emit(Args... args) const
    {
        std::scoped_lock<std::mutex> sl(mutex);
        for (auto& [id, fun] : observers)
        {
            assert(fun);
            fun(args...);
        }
        return observers.size();
    }
}
