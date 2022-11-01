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

#pragma once
#include "config.h"

#include <ice/ScreenNodeGroup.h>

namespace ice::ui
{
    //! User insterface base class.
    class ICE_EXPORT Widget : public ScreenNodeGroup
    {
    public:
        //! Construct user interface element.
        //!
        //! @param position the inital position
        //! @param size the initial size
        //! @{
        Widget() noexcept;
        Widget(const glm::vec2& size) noexcept;
        Widget(const glm::vec2& position, const glm::vec2& size) noexcept;
        //! @}

        //! Position
        //!
        //! The position is derived from the screen node's transform. If you access
        //! the widget through the position property it will always work. If
        //! you add rotation or saling to the transform this property fails
        //! to work in a deterministic fasion.
        //! @{
        void set_position(const glm::vec2& value) noexcept;
        glm::vec2 get_position() const noexcept;
        //! @}

        //! Size
        //!
        //! @{
        void set_size(const glm::vec2& value) noexcept;
        const glm::vec2& get_size() const noexcept;
        //! @}

        //! Minimum Size
        //!
        //! The minimum size is the size at which the widget can not get smaller.
        //! This will be used by layout code to pack the widgets.
        virtual glm::vec2 get_min_size() const noexcept;

    protected:
        //! Allow derived classes to control the size.
        //!
        //! Ths function allows derived classes to react to a new size request,
        //! and override the request with the new value.
        //!
        //! @param value the new size as requested
        //! @return the value accepted by the derived class
        virtual glm::vec2 handle_size_request(const glm::vec2& value) noexcept;

    private:
        glm::vec2 size = glm::vec2(0.0f);
    };
}
