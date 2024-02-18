// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include "defines.h"

namespace rex
{
    template <typename SOURCE, typename TARGET>
    class cache
    {
    public:

        cache(const std::function<TARGET (const SOURCE&)>& generator, size_t initial_life = 10u);

        ~cache() = default;

        TARGET get(const SOURCE& source);

        void collect();

    private:
        std::hash<SOURCE>                     hasher;
        std::function<TARGET (const SOURCE&)> generator;
        size_t                                initial_life;

        struct Entry
        {
            TARGET object;
            size_t life;
        };

        std::map<size_t, Entry> entries;

        cache(const cache<SOURCE, TARGET>&) = delete;
        cache<SOURCE, TARGET>& operator = (const cache<SOURCE, TARGET>&) = delete;
    };

    template <typename SOURCE, typename TARGET>
    cache<SOURCE, TARGET>::cache(const std::function<TARGET (const SOURCE&)>& g, size_t il)
    : generator(g), initial_life(il) {}

    template <typename SOURCE, typename TARGET>
    TARGET cache<SOURCE, TARGET>::get(const SOURCE& source)
    {
        auto hash = hasher(source);
        auto i = entries.find(hash);
        if (i == entries.end())
        {
            auto entry = Entry{generator(source), initial_life};
            entries[hash] = entry;
            return entry.object;
        }
        else
        {
            i->second.life = initial_life;
            return i->second.object;
        }
    }

    template <typename SOURCE, typename TARGET>
    void cache<SOURCE, TARGET>::collect()
    {
        std::erase_if(entries, [](const auto& entry) {
            return entry.second.life == 0;
        });

        std::ranges::for_each(entries, [](auto& entry) {
            entry.second.life--;
        });
    }
}
