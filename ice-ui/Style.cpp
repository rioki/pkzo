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

    Style::Style(AssetLibrary& _library, const std::filesystem::path& file)
    : library(_library), file(file)
    {
        if (!std::filesystem::exists(file))
        {
            throw std::runtime_error(std::format("UI Style '{}' could not be found.", strex::narrow(file.native())));
        }

        if (std::filesystem::is_regular_file(file))
        {
            auto input = std::ifstream(file);
            if (!input.is_open())
            {
                throw std::runtime_error(std::format("Failed to open '{}' for reading.", strex::narrow(file.native())));
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

        return library.load<Texture>(get_directory() / filename);
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

        return library.load<Font>(get_directory() / filename, size);
    }

    glm::vec4 Style::get_color(const std::string_view widget, const std::string_view prop) const
    {
        return get_vec4(widget, prop);
    }

    int Style::get_int(const std::string_view widget, const std::string_view prop) const
    {
        return get_simple_prop<int>(widget, prop);
    }

    float Style::get_float(const std::string_view widget, const std::string_view prop) const
    {
        return get_simple_prop<float>(widget, prop);
    }

    glm::vec2 Style::get_vec2(const std::string_view widget, const std::string_view prop) const
    {
        return get_simple_prop<glm::vec2>(widget, prop);
    }

    glm::vec3 Style::get_vec3(const std::string_view widget, const std::string_view prop) const
    {
        return get_simple_prop<glm::vec3>(widget, prop);
    }

    glm::vec4 Style::get_vec4(const std::string_view widget, const std::string_view prop) const
    {
        return get_simple_prop<glm::vec4>(widget, prop);
    }

    void Style::set_texture(const std::string_view widget, const std::string_view prop, const std::shared_ptr<Texture>& value)
    {
        assert(value);
        auto filename = std::filesystem::relative(value->get_file(), get_directory());
        set_prop(widget, prop, filename.string());
    }

    void Style::set_font(const std::string_view widget, const std::string_view prop, const std::shared_ptr<Font>& value)
    {
        assert(value);
        auto filename = std::filesystem::relative(value->get_file(), get_directory());
        auto size     = value->get_size();
        set_prop(widget, prop, nlohmann::json{
            {"file", filename.string()},
            {"size", size},
        });
    }

    void Style::set_color(const std::string_view widget, const std::string_view prop, const glm::vec4& value)
    {
        set_vec4(widget, prop, value);
    }

    void Style::set_int(const std::string_view widget, const std::string_view prop, const int value)
    {
        set_prop(widget, prop, value);
    }

    void Style::set_float(const std::string_view widget, const std::string_view prop, const float value)
    {
        set_prop(widget, prop, value);
    }

    void Style::set_vec2(const std::string_view widget, const std::string_view prop, const glm::vec2 value)
    {
        set_prop(widget, prop, value);
    }

    void Style::set_vec3(const std::string_view widget, const std::string_view prop,const glm::vec3& value)
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

    std::optional<std::string> get_variant_base(const std::string& widget)
    {
        static auto re_name_variant = std::regex("([a-zA-Z0-9_]+)/([a-zA-Z0-9_]+)");
        std::smatch result;
        if (std::regex_match(cbegin(widget), cend(widget), result, re_name_variant))
        {
            return result[1].str();
        }

        return std::nullopt;
    }

    in<nlohmann::json> Style::get_prop(const std::string_view widget, const std::string_view prop) const
    {
        auto si = jtheme.find(widget);
        if (si != end(jtheme))
        {
            auto pi = si->find(prop);
            if (pi != end(*si))
            {
                return *pi;
            }
        }

        // CHECKME This string_view to string promotion may be called allot, check if this can be improved.
        if (auto base_name = get_variant_base(std::string(widget))) // only if widget with variant
        {
            si = jtheme.find(*base_name);
            if (si != end(jtheme))
            {
                auto pi = si->find(prop);
                if (pi != end(*si))
                {
                    return *pi;
                }
            }
        }

        si = jtheme.find(DEFAULT_PROP);
        if (si != end(jtheme))
        {
            auto pi = si->find(prop);
            if (pi != end(*si))
            {
                return *pi;
            }
        }

        throw std::domain_error(std::format("Theme '{}' has no value property '{}' for widget '{}'.", file.filename().string(), prop, widget));
    }

    template <typename T>
    struct zero_traits;

    template <>
    struct zero_traits<int>
    {
        static constexpr int get() noexcept
        {
            return 0;
        }
    };

    template <>
    struct zero_traits<float>
    {
        static constexpr float get() noexcept
        {
            return 0.0f;
        }
    };

    template <size_t N, typename T, glm::qualifier Q>
    struct zero_traits<glm::vec<N, T, Q>>
    {
        static constexpr auto get() noexcept
        {
            return glm::vec<N, T, Q>(0.0f);
        }
    };

    template <typename T>
    T Style::get_simple_prop(const std::string_view widget, const std::string_view prop) const
    {
        const auto& jprop = get_prop(widget, prop);

        if (jprop.is_null())
        {
            return zero_traits<T>::get();
        }

        return jprop.get<T>();
    }

    void Style::set_prop(const std::string_view widget, const std::string_view prop, in<nlohmann::json> jvalue)
    {
        jtheme[widget][prop] = jvalue;
    }
}