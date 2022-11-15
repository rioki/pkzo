// Ice Engine
// Copyright 2022 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include "config.h"

#include <algorithm>
#include <memory>
#include <map>
#include <filesystem>
#include <string_view>

#include "utils.h"

namespace ice
{
    using stdex::in;
    using stdex::inref;
    using stdex::cref_t;

    class Asset;

    class ICE_EXPORT AssetLibrary
    {
    public:
        AssetLibrary() noexcept;
        ~AssetLibrary();

        void add_directory(in<std::filesystem::path> dir);
        cref_t<std::vector<std::filesystem::path>> get_directories() const noexcept;

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> load(const Args& ... args);

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> load(const char* path, const Args& ... args);

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> load(in<std::string> path, const Args& ... args);

        template <typename AssetT, typename ... Args>
        std::shared_ptr<AssetT> load(in<std::filesystem::path> path, const Args& ... args);

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

    template <typename AssetT, typename ... Args>
    std::shared_ptr<AssetT> AssetLibrary::load(in<std::string> path, const Args& ... args)
    {
        return load<AssetT>(std::filesystem::path(path), args ...);
    }

    inline std::filesystem::path _fix_path(in<std::filesystem::path> path, in<std::vector<std::filesystem::path>> dirs)
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
    std::shared_ptr<AssetT> AssetLibrary::load(in<std::filesystem::path> path, const Args& ... args)
    {
        auto fixed_path = _fix_path(path, directories);
        return do_load<AssetT>(fixed_path, args ...);
    }

    template <typename AssetT, typename ... Args>
    requires std::constructible_from<AssetT, const Args&...>
    inline std::shared_ptr<AssetT> make_asset_ptr(inref<AssetLibrary> /*library*/, const Args& ... args)
    {
        return std::make_shared<AssetT>(args...);
    }

    template <typename AssetT, typename ... Args>
    requires std::constructible_from<AssetT, AssetLibrary&, const Args&...>
    inline std::shared_ptr<AssetT> make_asset_ptr(inref<AssetLibrary> library, const Args& ... args)
    {
        return std::make_shared<AssetT>(library, args...);
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

        auto asset = make_asset_ptr<AssetT>(*this, args...);
        cache[key] = asset;
        return asset;
    }
}
