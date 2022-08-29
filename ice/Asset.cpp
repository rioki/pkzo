// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "Asset.h"

namespace ice
{
    std::atomic<unsigned int> Asset::last_id = 0;

    Asset::Asset(const std::filesystem::path& _file) noexcept
    : id(++last_id), file(_file) {}

    Asset::~Asset() = default;

    unsigned int Asset::get_id() const noexcept
    {
        return id;
    }

    const std::filesystem::path& Asset::get_file() const noexcept
    {
        return file;
    }
}
