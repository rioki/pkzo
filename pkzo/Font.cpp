// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "Font.h"

#include <map>

#include "FreeTypeFont.h"

namespace pkzo
{
    std::shared_ptr<Font> Font::load(const std::filesystem::path& file)
    {
        static std::map<std::filesystem::path, std::weak_ptr<Font>> cache;

        auto i = cache.find(file);
        if (i != end(cache))
        {
            auto cached_texture = i->second.lock();
            if (cached_texture)
            {
                return cached_texture;
            }
        }

        auto font = std::make_shared<FreeTypeFont>(file);
        cache.insert_or_assign(file, font);
        return font;
    }
}
