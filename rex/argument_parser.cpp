// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#include "pch.h"
#include "argument_parser.h"

namespace rex
{
    argument_parser::argument_parser() = default;
    argument_parser::~argument_parser() = default;

    std::string argument_parser::get_command() const
    {
        return command;
    }

    void argument_parser::define_flag(const std::string& name, const std::string& description)
    {
        flags[name] = false;
        descriptions[name] = description;
    }

    void argument_parser::define_flag(char short_name, const std::string& name, const std::string& description)
    {
        flags[name] = false;
        short_flags[short_name] = name;
        descriptions[name] = description;
    }

    bool argument_parser::has_flag(const std::string& name) const
    {
        return flags.at(name);
    }

    void argument_parser::define_option(const std::string& name, const std::string& description, const std::string& default_value)
    {
        options[name] = default_value;
        descriptions[name] = description;
    }

    std::string argument_parser::get_option(const std::string& name) const
    {
        return options.at(name);
    }

    std::vector<std::string> argument_parser::get_files() const
    {
        return files;
    }

    template <typename Key, typename Value>
    void nice_set(std::map<Key, Value>& map, const Key& key, const Value& value)
    {
        auto i = map.find(key);
        if (i == map.end())
        {
            throw std::runtime_error(tfm::format("Unknown argument %s.", key));
        }
        i->second = value;
    }

    template <typename Key, typename Value>
    Value nice_get(std::map<Key, Value>& map, const Key& key)
    {
        auto i = map.find(key);
        if (i == map.end())
        {
            throw std::runtime_error(tfm::format("Unknown argument %s.", key));
        }
        return i->second;
    }

    void argument_parser::parse(int argc, const char** argv)
    {
        command = argv[0];

        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];

            if (arg[0] == '-')
            {
                if (arg[1] == '-')
                    {
                    auto pos = arg.find('=');
                    if (pos != std::string::npos)
                    {
                        auto name = arg.substr(2, pos - 2);
                        auto value = arg.substr(pos + 1);
                        nice_set(options, name, value);
                    }
                    else
                    {
                        auto name = arg.substr(2);
                        nice_set(flags, name, true);
                    }
                }
                else
                {
                    auto name = arg.substr(1);
                    for (const auto c : name)
                    {
                        auto flag = nice_get(short_flags, c);
                        assert(flags.count(flag) == 1);
                        flags.at(flag) = true;
                    }
                }
            }
            else
            {
                files.push_back(arg);
            }
        }
    }

    std::string argument_parser::get_help() const
    {
        auto buffer = std::stringstream{};

        buffer << "Usage:\n"
               << "  " << command << " [options] [files]\n"
               << "\n"
               << "Options:\n";

        // name, short name, description
        auto options = std::vector<std::tuple<std::string, std::string, std::string>>{};

        for (const auto& flag : flags)
        {
            options.emplace_back(flag.first, "", "");
        }

        for (const auto& option : this->options)
        {
            options.emplace_back(option.first, "", "");
        }

        for (const auto& short_flag : short_flags)
        {
            auto i = std::ranges::find_if(options, [&short_flag](const auto& option) {
                return std::get<0>(option) == short_flag.second;
            });
            assert(i != options.end());
            std::get<1>(*i) = short_flag.first;
        }

        for (const auto& descr : descriptions)
        {
            auto i = std::ranges::find_if(options, [&descr](const auto& option) {
                return std::get<0>(option) == descr.first;
            });
            assert(i != options.end());
            std::get<2>(*i) = descr.second;
        }

        std::ranges::sort(options, [](const auto& a, const auto& b) {
            return std::get<0>(a) < std::get<0>(b);
        });

        auto max_name_length = std::accumulate(options.begin(), options.end(), size_t{0}, [](const auto& a, const auto& b) {
            return std::max(a, std::get<0>(b).size() + std::get<1>(b).size() + 3);
        });

        for (const auto& [name, s, descr] : options)
        {
            assert(!name.empty());
            auto flag_length = name.size();
            buffer << "  --" << name;
            if (!s.empty())
            {
                flag_length += s.size() + 3;
                buffer << ", -" << s;
            }

            buffer << std::string(max_name_length - flag_length, ' ') << " " << descr << "\n";
        }



        return buffer.str();
    }
}
