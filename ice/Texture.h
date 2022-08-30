// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <filesystem>
#include <glm/glm.hpp>

#include "Asset.h"

struct FIBITMAP;

namespace ice
{
    enum class ColorMode
    {
        UNKNOWN,
        R,
        RG,
        RGB,
        BGR,
        RGBA,
        BGRA
    };

    enum class DataType
    {
        UNKNOWN,
        INT8,
        UINT8,
        INT16,
        UINT16,
        UINT32,
        INT32,
        FLOAT,
        DOUBLE
    };

    enum class FilterMode
    {
        NEAREST,
        LINEAR
    };

    enum class WrapMode
    {
        CLAMP,
        REPEAT
    };

    class ICE_EXPORT Texture : public Asset
    {
    public:
        Texture(const std::filesystem::path& file);
        Texture(const glm::uvec2& size, ColorMode mode, DataType group, const void* memory, const std::string& label = "memory");
        ~Texture();

        const std::filesystem::path& get_file() const noexcept;

        glm::uvec2 get_size() const noexcept;
        ColorMode get_color_mode() const noexcept;
        DataType get_data_type() const noexcept;

        glm::vec4 get_texel(const glm::uvec2& index) const noexcept;
        void set_texel(const glm::uvec2& index, const glm::vec4& value) noexcept;

        void* get_data() const noexcept;

        void set_filter_mode(FilterMode value) noexcept;
        FilterMode get_filter_mode() const noexcept;

        void set_wrap_mode(WrapMode value) noexcept;
        WrapMode get_wrap_mode() const noexcept;

        const std::string& get_label() const noexcept;

        void save(const std::filesystem::path& file) const;

    private:
        std::filesystem::path file;
        FIBITMAP*             bitmap      = nullptr;
        FilterMode            filter_mode = FilterMode::LINEAR;
        WrapMode              wrap_mode   = WrapMode::REPEAT;
        std::string           label       = "unnamed";

        Texture(const Texture&) = delete;
        Texture& operator = (const Texture&) = delete;
    };

    ICE_EXPORT float compare(const std::shared_ptr<Texture>& a, const std::shared_ptr<Texture>& b);
    ICE_EXPORT std::shared_ptr<Texture> diff(const std::shared_ptr<Texture>& a, const std::shared_ptr<Texture>& b);
}
