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

#include <string_view>
#include <filesystem>

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

#include <ice/Asset.h>
#include <ice/Texture.h>
#include <ice/Font.h>

namespace ice::ui
{
    using stdex::in;
    using stdex::cref_t;

    class ICE_EXPORT Style : public ice::Asset
    {
    public:
        Style(in<std::filesystem::path> file);

        [[nodiscard]] std::shared_ptr<Texture> get_texture(in<std::string_view> widget, in<std::string_view> prop) const;
        [[nodiscard]] std::shared_ptr<Font>    get_font(in<std::string_view> widget, in<std::string_view> prop) const;
        [[nodiscard]] glm::vec4                get_color(in<std::string_view> widget, in<std::string_view> prop) const;
        [[nodiscard]] int                      get_int(in<std::string_view> widget, in<std::string_view> prop) const;
        [[nodiscard]] float                    get_float(in<std::string_view> widget, in<std::string_view> prop) const;
        [[nodiscard]] glm::vec2                get_vec2(in<std::string_view> widget, in<std::string_view> prop) const;
        [[nodiscard]] glm::vec3                get_vec3(in<std::string_view> widget, in<std::string_view> prop) const;
        [[nodiscard]] glm::vec4                get_vec4(in<std::string_view> widget, in<std::string_view> prop) const;

        void set_texture(in<std::string_view> widget, in<std::string_view> prop, in<std::shared_ptr<Texture>> value);
        void set_font(in<std::string_view> widget, in<std::string_view> prop, in<std::shared_ptr<Font>> value);
        void set_color(in<std::string_view> widget, in<std::string_view> prop, in<glm::vec4> value);
        void set_int(in<std::string_view> widget, in<std::string_view> prop, in<int> value);
        void set_float(in<std::string_view> widget, in<std::string_view> prop, in<float> value);
        void set_vec2(in<std::string_view> widget, in<std::string_view> prop, in<glm::vec2> value);
        void set_vec3(in<std::string_view> widget, in<std::string_view> prop, in<glm::vec3> value);
        void set_vec4(in<std::string_view> widget, in<std::string_view> prop, in<glm::vec4> value);

    private:
        using TextureCache = std::map<std::filesystem::path, std::shared_ptr<Texture>>;

        using FontId    = std::tuple<std::string, unsigned int>;
        using FontCache = std::map<FontId, std::shared_ptr<Font>>;

        nlohmann::json        jtheme;
        std::filesystem::path file;
        mutable TextureCache  texture_cache;
        mutable FontCache     font_cache;

        [[nodiscard]] std::filesystem::path get_directory() const;
        [[nodiscard]] cref_t<nlohmann::json> get_prop(in<std::string_view> widget, in<std::string_view> prop) const;

        template <typename T>
        [[nodiscard]] T get_simple_prop(in<std::string_view> widget, in<std::string_view> prop) const;

        void set_prop(in<std::string_view> widget, in<std::string_view> prop, in<nlohmann::json> jvalue);
    };
}
