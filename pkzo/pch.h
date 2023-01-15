// pkzo
// Copyright 2022-2023 Sean Farrell
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

#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <atomic>
#include <string>
#include <string_view>
#include <vector>
#include <deque>
#include <map>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <format>
#include <memory>
#include <stdexcept>
#include <numbers>
#include <regex>

#include <Windows.h>

#include <iconv.h>
#include <SDL2/SDL.h>
#include <FreeImage.h>
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <rioki/glow/fwd.h>
#include <rioki/glow/glow.h>

#include <rioki/c9y/sync.h>
#include <rioki/c9y/async.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "glm_2d.h"
#include "glm_io.h"
#include "glm_json.h"
#include "glm_utils.h"
#include "strex.h"