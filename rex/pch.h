// rioki's C++ extentions
// Copyright 2020-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#include <cstddef>

#include <array>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <string_view>
#include <string>
#include <thread>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#include <shlobj.h>
#include <dbghelp.h>
#undef ERROR
#endif

#include <iconv.h>
#include <tinyformat.h>
