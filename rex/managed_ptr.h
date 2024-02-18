// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <cstddef>
#include <memory>

#include "defines.h"

namespace rex
{
    template <typename T>
    struct managed_delete
    {
        bool managed = true;

        managed_delete() noexcept = default;

        explicit managed_delete(bool m) noexcept
        : managed(m) {}

        void operator() (T* ptr) const noexcept
        {
            if (managed)
            {
                delete ptr;
            }
        }
    };

    template <typename T>
    class managed_ptr
    {
    public:
        managed_ptr() noexcept = default;

        explicit managed_ptr(T* p) noexcept
        : ptr(p) {}

        explicit managed_ptr(T* p, bool m) noexcept
        : ptr(p, managed_delete<T>(m)) {}


        template <typename U>
        managed_ptr(std::unique_ptr<U>&& uptr)
        : ptr(uptr.release()) {}

        managed_ptr(managed_ptr<T>&& rhs) noexcept = default;

        managed_ptr<T>& operator = (managed_ptr<T>&& rhs) noexcept = default;

        ~managed_ptr() noexcept = default;

        bool operator == (std::nullptr_t) const noexcept
        {
            return ptr == nullptr;
        }

        bool operator == (const managed_ptr<T>& rhs) const noexcept
        {
            return ptr == rhs.ptr;
        }

        operator bool () const noexcept
        {
            return ptr != nullptr;
        }

        T& operator * () const noexcept
        {
            assert(ptr.get() != nullptr);
            return *ptr.get();
        }

        T* operator -> () const noexcept
        {
            assert(ptr.get() != nullptr);
            return ptr.get();
        }

        T* get() const noexcept
        {
            return ptr.get();
        }

        bool is_managed() const noexcept
        {
            return ptr.get_deleter().managed;
        }

        void reset(T* p = nullptr) noexcept
        {
            ptr.reset(p);
        }

        T* release() noexcept
        {
            return ptr.release();
        }

        void swap(managed_ptr<T>& rhs) noexcept
        {
            ptr.swap(rhs.ptr);
        }

    private:
        std::unique_ptr<T, managed_delete<T>> ptr;

        managed_ptr(const managed_ptr<T>&) = delete;
        managed_ptr<T>& operator = (const managed_ptr<T>&) = delete;
    };

    template <typename T, typename ... Args>
    managed_ptr<T> make_managed(Args&& ... args)
    {
        return managed_ptr<T>(new T(std::forward<Args>(args) ... ));
    }

    template <typename T>
    managed_ptr<T> wrap_managed(T& value)
    {
        return managed_ptr<T>(&value, false);
    }

    template <typename T>
    managed_ptr<T> wrap_managed(T* value)
    {
        return managed_ptr<T>(value, false);
    }

    template <typename T>
    void swap(managed_ptr<T>& lhs, managed_ptr<T>& rhs) noexcept
    {
        lhs.swap(rhs);
    }
}