// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <string>
#include <map>
#include <vector>

#include "defines.h"

namespace rex
{
    class REX_EXPORT argument_parser
    {
    public:
        argument_parser();
        ~argument_parser();

        std::string get_command() const;

        void define_flag(const std::string& name, const std::string& description);
        void define_flag(char short_name, const std::string& name, const std::string& description);
        bool has_flag(const std::string& name) const;

        void define_option(const std::string& name, const std::string& description, const std::string& default_value);
        std::string get_option(const std::string& name) const;

        std::vector<std::string> get_files() const;

        void parse(int argc, const char** argv);

        std::string get_help() const;

    private:
        std::string command;
        std::map<std::string, bool> flags;
        std::map<char, std::string> short_flags;
        std::map<std::string, std::string> options;
        std::map<std::string, std::string> descriptions;
        std::vector<std::string> files;

        argument_parser(const argument_parser&) = delete;
        argument_parser& operator = (const argument_parser&) = delete;
    };
}

