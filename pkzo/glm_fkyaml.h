// glm nlohemann FK-YAML adapters
// Copyright 2025 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <glm/glm.hpp>
#include <fkYAML/node.hpp>
#include <tinyformat.h>
#include <vector>

namespace glm
{
    template<glm::length_t N, typename T, qualifier Q>
    void from_node(const fkyaml::node& node, vec<N, T, Q>& v)
    {
        const auto& seq = node.get_value<std::vector<fkyaml::node>>();
        if (seq.size() != N)
        {
            throw std::runtime_error(tfm::format("Expected %d elements, got %d.", N, seq.size()));
        }

        for (auto i = 0u; i < N; i++)
        {
            v[i] = seq[i].get_value<T>();
        }
    }

    template<glm::length_t N, typename T, qualifier Q>
    void to_node(fkyaml::node& node, const vec<N, T, Q>& v)
    {
        auto seq = fkyaml::node::sequence_type{};
        for (auto i = 0u; i < N; i++)
        {
            seq.push_back(v[i]);
        }
        node = fkyaml::node::sequence(seq);
    }
}