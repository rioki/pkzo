// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <tuple>
#include <memory>
#include <filesystem>
#include <glm/glm.hpp>

#include "Asset.h"

typedef struct FT_LibraryRec_  *FT_Library;
typedef struct FT_FaceRec_  *FT_Face;

namespace ice
{
    class Texture;

    class ICE_EXPORT Font : public Asset
    {
    public:
        Font(const std::filesystem::path& file, unsigned int size);
        ~Font();

        const std::filesystem::path& get_file() const noexcept;
        unsigned int get_size() const noexcept;

        glm::uvec2 estimate(const std::string& text) const noexcept;
        std::shared_ptr<Texture> render(const std::string& text) const noexcept;

    private:
        static FT_Library init_ft_library();

        FT_Library            ft_library = init_ft_library();
        FT_Face               face;
        std::filesystem::path file;
        unsigned int          size;

        std::tuple<glm::uvec2, glm::uvec2> estimate_impl(const std::u32string& text) const noexcept;

        Font(const Font&) = delete;
        Font& operator = (const Font&) = delete;
    };
}
