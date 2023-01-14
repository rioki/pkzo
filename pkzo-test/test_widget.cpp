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

class TestWidget : public pkzo::Widget
{
public:
    TestWidget() noexcept = default;

    TestWidget(const glm::vec2& size) noexcept
    : Widget(size) {}

    TestWidget(const glm::vec2& position, const glm::vec2& size) noexcept
    : Widget(position, size) {}
};

class SizedWidget : public pkzo::Widget
{
public:
    SizedWidget() noexcept
    : Widget(glm::vec2(50.0f)) {}

    glm::vec2 get_min_size() const noexcept override
    {
        return glm::vec2(42.0f);
    }

protected:
    glm::vec2 handle_size_request(const glm::vec2& value) noexcept override
    {
        return glm::max(get_min_size(), value);
    }
};

TEST(Widget, default_contruct)
{
    auto widget = TestWidget();
    EXPECT_GLM_NEAR(glm::mat3(1.0f), widget.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(0.0f), widget.get_position(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(0.0f), widget.get_size(), 1e-4f);
}

TEST(Widget, init_size)
{
    auto widget = TestWidget(glm::vec2(15.0f, 24.0f));
    EXPECT_GLM_NEAR(glm::mat3(1.0f),         widget.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(0.0f),         widget.get_position(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(15.0f, 24.0f), widget.get_size(), 1e-4f);
}

TEST(Widget, init_position_size)
{
    auto widget = TestWidget(glm::vec2(-12.0f, 13.0f), glm::vec2(15.0f, 24.0f));
    EXPECT_GLM_NEAR(glm::translate(glm::vec2(-12.0f, 13.0f)), widget.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(-12.0f, 13.0f),                 widget.get_position(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(15.0f, 24.0f),                  widget.get_size(), 1e-4f);
}

TEST(Widget, position_sets_transform)
{
    auto widget = TestWidget();
    EXPECT_GLM_NEAR(glm::translate(glm::vec2(0.0f, 0.0f)), widget.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(0.0f),                       widget.get_position(), 1e-4f);

    widget.set_position(glm::vec2(45.0f, 67.0f));
    EXPECT_GLM_NEAR(glm::translate(glm::vec2(45.0f, 67.0f)), widget.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(45.0f, 67.0f),                 widget.get_position(), 1e-4f);
}

TEST(Widget, position_follows_transform)
{
    auto widget = TestWidget();
    EXPECT_GLM_NEAR(glm::translate(glm::vec2(0.0f, 0.0f)), widget.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(0.0f),                       widget.get_position(), 1e-4f);

    // Scale and rotation are undefined for widgets.
    widget.set_transform(glm::translate(glm::vec2(45.0f, 67.0f)));
    EXPECT_GLM_NEAR(glm::translate(glm::vec2(45.0f, 67.0f)), widget.get_transform(), 1e-4f);
    EXPECT_GLM_NEAR(glm::vec2(45.0f, 67.0f),                 widget.get_position(), 1e-4f);
}

TEST(Widget, size_request)
{
    auto widget = SizedWidget();
    EXPECT_GLM_NEAR(glm::vec2(50.0f), widget.get_size(), 1e-4f);

    // larger
    widget.set_size(glm::vec2(45.0f, 67.0f));
    EXPECT_GLM_NEAR(glm::vec2(45.0f, 67.0f), widget.get_size(), 1e-4f);

    // smaller x
    widget.set_size(glm::vec2(40.0f, 67.0f));
    EXPECT_GLM_NEAR(glm::vec2(42.0f, 67.0f), widget.get_size(), 1e-4f);

    // smaller y
    widget.set_size(glm::vec2(45.0f, 40.0f));
    EXPECT_GLM_NEAR(glm::vec2(45.0f, 42.0f), widget.get_size(), 1e-4f);

    // smaller x and y
    widget.set_size(glm::vec2(40.0f, 35.0f));
    EXPECT_GLM_NEAR(glm::vec2(42.0f, 42.0f), widget.get_size(), 1e-4f);
}
