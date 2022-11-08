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

#include "pch.h"
#include "Style.h"

namespace ice::ui
{
    auto constexpr DEFAULT_PROP = "default";

    Style::Style(const std::filesystem::path& file)
    : file(file)
    {
        if (std::filesystem::is_regular_file(file))
        {
            auto input = std::ifstream(file);
            if (!input.is_open())
            {
                throw std::runtime_error(std::format("Failed to open '{}' for reading.", file.string()));
            }

            jtheme = nlohmann::json::parse(input);
        }
    }

    std::shared_ptr<Texture> Style::get_texture(const std::string_view widget, const std::string_view prop) const
    {
        const auto& jprop = get_prop(widget, prop);

        if (jprop.is_null())
        {
            return nullptr;
        }

        if (!(jprop.is_object() || jprop.is_string()))
        {
            throw std::domain_error(std::format("Theme '{}': texture {}.{} must be a JSON object or string.", file.filename().string(), widget, prop));
        }

        auto filename = jprop.is_object() ? jprop.at("file").get<std::string>() : jprop.get<std::string>();
        // TODO other parameters such as filter mode

        auto ic = texture_cache.find(filename);
        if (ic != end(texture_cache))
        {
            return std::get<std::shared_ptr<Texture>>(*ic);
        }

        auto texture = std::make_shared<Texture>(get_directory() / filename);
        texture_cache[filename] = texture;
        return texture;
    }

    std::shared_ptr<Font> Style::get_font(const std::string_view widget, const std::string_view prop) const
    {
        const auto& jprop = get_prop(widget, prop);

        if (jprop.is_null())
        {
            return nullptr;
        }

        if (!jprop.is_object())
        {
            throw std::domain_error(std::format("Theme '{}': font {}.{} must be a JSON object.", file.filename().string(), widget, prop));
        }

        auto filename = jprop.at("file").get<std::string>();
        auto size = jprop.at("size").get<unsigned int>();

        auto ic = font_cache.find({filename, size});
        if (ic != end(font_cache))
        {
            return std::get<std::shared_ptr<Font>>(*ic);
        }

        auto font = std::make_shared<Font>(get_directory() / filename, size);
        font_cache[{filename, size}] = font;
        return font;
    }

    glm::vec4 Style::get_color(const std::string_view widget, const std::string_view prop) const
    {
        return get_vec4(widget, prop);
    }

    glm::vec2 Style::get_vec2(const std::string_view widget, const std::string_view prop) const
    {
        const auto& jprop = get_prop(widget, prop);

        if (jprop.is_null())
        {
            return glm::vec2(0.0f);
        }

        return jprop.get<glm::vec2>();
    }

    glm::vec3 Style::get_vec3(const std::string_view widget, const std::string_view prop) const
    {
        const auto& jprop = get_prop(widget, prop);

        if (jprop.is_null())
        {
            return glm::vec3(0.0f);
        }

        return jprop.get<glm::vec3>();
    }

    glm::vec4 Style::get_vec4(const std::string_view widget, const std::string_view prop) const
    {
        const auto& jprop = get_prop(widget, prop);

        if (jprop.is_null())
        {
            return glm::vec4(0.0f);
        }

        return jprop.get<glm::vec4>();
    }

    void Style::set_texture(const std::string_view widget, const std::string_view prop, const std::shared_ptr<Texture>& value)
    {
        assert(value);
        auto filename = std::filesystem::relative(value->get_file(), get_directory());
        texture_cache[filename] = value;
        set_prop(widget, prop, filename.string());
    }

    void Style::set_font(const std::string_view widget, const std::string_view prop, const std::shared_ptr<Font>& value)
    {
        assert(value);
        auto filename = std::filesystem::relative(value->get_file(), get_directory());
        auto size     = value->get_size();
        font_cache[{filename.string(), size}] = value;
        set_prop(widget, prop, nlohmann::json{
            {"file", filename.string()},
            {"size", size},
        });
    }

    void Style::set_color(const std::string_view widget, const std::string_view prop, const glm::vec4& value)
    {
        set_vec4(widget, prop, value);
    }

    void Style::set_vec2(const std::string_view widget, const std::string_view prop, const glm::vec2& value)
    {
        set_prop(widget, prop, value);
    }

    void Style::set_vec3(const std::string_view widget, const std::string_view prop, const glm::vec3& value)
    {
        set_prop(widget, prop, value);
    }

    void Style::set_vec4(const std::string_view widget, const std::string_view prop, const glm::vec4& value)
    {
        set_prop(widget, prop, value);
    }

    std::filesystem::path Style::get_directory() const
    {
        if (std::filesystem::is_directory(file))
        {
            return file;
        }
        else
        {
            return file.parent_path();
        }
    }

    const nlohmann::json& Style::get_prop(const std::string_view widget, const std::string_view prop) const
    {
        auto si = jtheme.find(widget);
        if (si == end(jtheme))
        {
            si = jtheme.find(DEFAULT_PROP);
            if (si == end(jtheme))
            {
                throw std::domain_error(std::format("Theme '{}' has no '{}' property section.", file.filename().string(), DEFAULT_PROP));
            }
        }

        const auto& section = *si;
        auto pi = section.find(prop);
        if (pi == end(section))
        {
            si = jtheme.find(DEFAULT_PROP);
            if (si == end(jtheme))
            {
                throw std::domain_error(std::format("Theme '{}' has no '{}' property section.", file.filename().string(), DEFAULT_PROP));
            }
            const auto& default_section = *si;
            pi = default_section.find(prop);
            if (pi == end(default_section))
            {
                throw std::domain_error(std::format("Theme '{}' has no value property '{}' for widget '{}'.", file.filename().string(), prop, widget));
            }
        }

        return *pi;
    }

    void Style::set_prop(const std::string_view widget, const std::string_view prop, const nlohmann::json& jvalue)
    {
        jtheme[widget][prop] = jvalue;
    }
}