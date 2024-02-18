// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <filesystem>
#include <string_view>
#include <string>

#include "defines.h"

namespace rex
{
    REX_EXPORT std::string file_name(const std::string_view& path) noexcept;
    REX_EXPORT std::string get_env_variable(const std::string_view name) noexcept;
    REX_EXPORT std::filesystem::path get_temp_folder();
    REX_EXPORT std::filesystem::path get_user_folder();
    REX_EXPORT std::string get_module_filename() noexcept;
}
