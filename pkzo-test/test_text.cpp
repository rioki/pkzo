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

#include "pch.h"

__declspec(dllexport) void testing::internal::PrintU8StringTo(const ::std::u8string& s, ::std::ostream* os)
{
	(*os) << std::string_view{ (const char*)s.data(), s.size() };
}

TEST(Text, init)
{
    auto transform = glm::translate(glm::mat3(1.0f), glm::vec2(14.0f, 12.0f));
    auto text      = std::string{"Hello World"};
    auto font      = std::make_shared<pkzo::Font>(pkzo::test::get_asset_folder() / "fonts/DejaVuSans.ttf", 32);  \
    auto color     = pkzo::rgba(0xffa500ff);


    auto widget = pkzo::Text(transform, text, font, color);

    EXPECT_GLM_NEAR(transform, widget.get_transform(), 1e-4f);
    EXPECT_EQ(text, widget.get_text());
    EXPECT_EQ(font, widget.get_font());
    EXPECT_GLM_EQ(color, widget.get_color());
}

TEST(Text, init_no_transofrm)
{
    auto text      = std::string{"Hello World"};
    auto font      = std::make_shared<pkzo::Font>(pkzo::test::get_asset_folder() / "fonts/DejaVuSans.ttf", 32);  \
    auto color     = pkzo::rgba(0xffa500ff);

    auto widget = pkzo::Text(text, font, color);

    EXPECT_GLM_NEAR(glm::mat3(1.0f), widget.get_transform(), 1e-4f);
    EXPECT_EQ(text, widget.get_text());
    EXPECT_EQ(font, widget.get_font());
    EXPECT_GLM_EQ(color, widget.get_color());
}
