// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <algorithm>
#include <memory>
#include <map>
#include <filesystem>

#include "utils.h"

namespace ice
{
    class Asset;

    class ICE_EXPORT AssetLibrary
    {
    public:
        AssetLibrary() noexcept;
        ~AssetLibrary();

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> load(const Args& ... args);

    private:
        std::unordered_map<size_t, std::shared_ptr<Asset>> asset_cache;

        AssetLibrary(const AssetLibrary&) = delete;
        AssetLibrary& operator = (const AssetLibrary&) = delete;
    };

    template <typename AssetT, typename ... Args>
    std::shared_ptr<AssetT> AssetLibrary::load(const Args& ... args)
    {
        auto key = hash(args...);

        auto i = asset_cache.find(key);
        if (i != end(asset_cache))
        {
            auto a = std::dynamic_pointer_cast<AssetT>(i->second);
            assert(a != nullptr);
            return a;
        }

        auto asset = std::make_shared<AssetT>(args...);
        asset_cache[key] = asset;
        return asset;
    }
}
