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

        void add_directory(const std::filesystem::path& dir);
        const std::vector<std::filesystem::path>& get_directories() const noexcept;

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> load(const Args& ... args);

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> load(const char* path, const Args& ... args);

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> load(const std::filesystem::path& path, const Args& ... args);

    private:
        std::vector<std::filesystem::path>                 directories;
        std::unordered_map<size_t, std::shared_ptr<Asset>> cache;

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> do_load(const Args& ... args);

        AssetLibrary(const AssetLibrary&) = delete;
        AssetLibrary& operator = (const AssetLibrary&) = delete;
    };

    template <typename AssetT, typename ... Args>
    std::shared_ptr<AssetT> AssetLibrary::load(const Args& ... args)
    {
        return do_load<AssetT>(args...);
    }

    template <typename AssetT, typename ... Args>
    std::shared_ptr<AssetT> AssetLibrary::load(const char* path, const Args& ... args)
    {
        return load<AssetT>(std::filesystem::path(path), args ...);
    }

    std::filesystem::path _fix_path(const std::filesystem::path& path, const std::vector<std::filesystem::path>& dirs)
    {
        if (path.is_absolute())
        {
            return std::filesystem::weakly_canonical(path);
        }

        for (const auto& dir : dirs)
        {
            auto test_file = dir / path;
            if (std::filesystem::exists(test_file))
            {
                return std::filesystem::canonical(test_file);
            }
        }

        // this probably does not exist
        return path;
    }

    template <typename AssetT, typename ... Args>
    std::shared_ptr<AssetT> AssetLibrary::load(const std::filesystem::path& path, const Args& ... args)
    {
        auto fixed_path = _fix_path(path, directories);
        return do_load<AssetT>(fixed_path, args ...);
    }

    template <typename AssetT, typename ... Args>
    std::shared_ptr<AssetT> AssetLibrary::do_load(const Args& ... args)
    {
        auto key = hash(args...);

        auto i = cache.find(key);
        if (i != end(cache))
        {
            auto a = std::dynamic_pointer_cast<AssetT>(i->second);
            assert(a != nullptr);
            return a;
        }

        auto asset = std::make_shared<AssetT>(args...);
        cache[key] = asset;
        return asset;
    }
}
