// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#include "pch.h"
#include "AssetLibrary.h"

#include "Asset.h"

namespace ice
{
    AssetLibrary::AssetLibrary() noexcept = default;
    AssetLibrary::~AssetLibrary() = default;

    void AssetLibrary::add_directory(const std::filesystem::path& dir)
    {
        assert(std::ranges::find(directories, dir) == end(directories));
        directories.push_back(std::filesystem::canonical(dir));
    }

    const std::vector<std::filesystem::path>& AssetLibrary::get_directories() const noexcept
    {
        return directories;
    }
}


