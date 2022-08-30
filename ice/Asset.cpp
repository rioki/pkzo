// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "Asset.h"

namespace ice
{
    std::atomic<unsigned int> Asset::last_id = 0;

    Asset::Asset() noexcept
    : id(++last_id) {}

    Asset::~Asset() = default;

    unsigned int Asset::get_id() const noexcept
    {
        return id;
    }
}
