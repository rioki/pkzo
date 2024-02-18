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

namespace rex
{
    template<typename Class, class Ret, class... Args>
    using method_pointer = Ret(Class::*)(Args...);

    template<typename Class, class Ret, class... Args>
    using method_pointer_const = Ret(Class::*)(Args...) const;

    template<typename Class, class Ret, class... Args>
    using method_pointer_ne = Ret(Class::*)(Args...) noexcept;

    template<typename Class, class Ret, class... Args>
    using method_pointer_const_ne = Ret(Class::*)(Args...) const noexcept;

    //! Member function adapter.
    //!
    //! This adapter allows simple member function to work as standalone functions.
    //!
    //! @param that the this pointer to use
    //! @param method the class method to call.
    //!
    //! Example:
    //! @code
    //! some_signal.connect(rsig::mem_fun(this, &MyClass::my_method));
    //! @endcode
    //! @{
    template <typename Class, typename Ret, typename... Args>
    std::function<Ret (Args...)> mem_fun(Class* that, method_pointer<Class, Ret, Args...> method)
    {
        return [that, method] (Args... args) {
            return (that->*method)(args...);
        };
    }

    template <typename Class, typename Ret, typename... Args>
    std::function<Ret (Args...)> mem_fun(Class* that, method_pointer_const<Class, Ret, Args...> method)
    {
        return [that, method] (Args... args) {
            return (that->*method)(args...);
        };
    }

    template <typename Class, typename Ret, typename... Args>
    std::function<Ret (Args...)> mem_fun(Class* that, method_pointer_ne<Class, Ret, Args...> method)
    {
        return [that, method] (Args... args) {
            return (that->*method)(args...);
        };
    }

    template <typename Class, typename Ret, typename... Args>
    std::function<Ret (Args...)> mem_fun(Class* that, method_pointer_const_ne<Class, Ret, Args...> method)
    {
        return [that, method] (Args... args) {
            return (that->*method)(args...);
        };
    }
    //! @}

    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

    template<typename T>
    void noop(T*) {}
}
