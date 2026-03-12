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

#pragma once

#include <atomic>
#include <filesystem>

#include <glm/glm.hpp>
#include <freeimage.h>

#include "MemoryTexture.h"

namespace pkzo
{
    class FreeImageSentry
    {
    public:
        FreeImageSentry();
        ~FreeImageSentry();

    private:
        static std::atomic<unsigned int> use_count;
    };

    class PKZO_EXPORT FreeImageTexture : public MemoryTexture, public std::enable_shared_from_this<FreeImageTexture>
    {
    public:
        FreeImageTexture(const FileLoadSpecs& specs);
        FreeImageTexture(const MemorLoadSpecs& specs);
        FreeImageTexture(const CreateSpecs& specs);

        ~FreeImageTexture();

        const std::string& get_id() const override;
        glm::uvec2 get_size() const override;
        ColorMode get_color_mode() const override;
        DataType get_data_type() const override;
        const void* get_memory() const override;
        TextureFilter get_filter() const override;
        Clamp get_clamp() const override;

        std::shared_ptr<MemoryTexture> download() override;

        glm::vec4 get_pixel(const glm::uvec2& pos) const override;
        void set_pixel(const glm::uvec2& pos, const glm::vec4& value) override;

        void save(const std::filesystem::path& file) const override;

    private:
        FreeImageSentry sentry;
        FIBITMAP*       bitmap = nullptr;
        std::string     id;
        TextureFilter   filter;
        Clamp           clamp;
    };
}
