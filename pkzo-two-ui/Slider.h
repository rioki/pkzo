//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef _PKZO_TWO_UI_SLIDER_H_
#define _PKZO_TWO_UI_SLIDER_H_

#include "config.h"

#include <memory>
#include <pkzo/pkzo.h>
#include <pkzo-two/pkzo-two.h>

namespace pkzo::two::ui
{
    enum class SliderOrientation
    {
        HORIZONTAL,
        VERTICAL
    };

    //! Slider Widget
    class PKZOUI_EXPORT Slider : public ScreenNodeGroup
    {
    public:
        //! Default Contructor
        //!
        //! @warning you need to set background_texture and handle_texture before
        //! you can use the slider.
        Slider() noexcept;

        //! Construct the Slider
        //!
        //! @param background_texture the background texture
        //! @param handle_texture the handle texture
        //! @param value the slider value
        //!
        //! @{
        Slider(const std::shared_ptr<Texture>& background_texture, const std::shared_ptr<Texture>& handle_texture) noexcept;
        Slider(const std::shared_ptr<Texture>& background_texture, const std::shared_ptr<Texture>& handle_texture, float value) noexcept;
        //! @}

        ~Slider();

        //! Get the widget size.
        const glm::vec2& get_size() const noexcept;

        //! Set the background texture.
        void set_background_texture(const std::shared_ptr<Texture>& value) noexcept;
        //! Get the background texture.
        const std::shared_ptr<Texture>& get_background_texture() const noexcept;

        //! Set the handle texture.
        void set_handle_texture(const std::shared_ptr<Texture>& value) noexcept;
        //! Get the handle texture.
        const std::shared_ptr<Texture>& get_handle_texture() const noexcept;

        //! Set the slidre orientation.
        void set_orientation(SliderOrientation value) noexcept;
        //! Get the slidre orientation.
        SliderOrientation get_orientation() const noexcept;

        //! Set the slider value.
        void set_value(float value) noexcept;
        //! Get the slider value.
        float get_value() const noexcept;

        //! Change Event
        void on_change(const std::function<void (float)>& cb) noexcept;

    private:
        SliderOrientation          orientation = SliderOrientation::HORIZONTAL;
        float                      value       = 0.5f;
        std::shared_ptr<Rectangle> background;
        std::shared_ptr<Rectangle> handle;
        std::shared_ptr<HitArea>   hit_area;

        std::function<void (float)> change_cb;

        bool slide_armed = false;

        void set_value_from_pos(glm::vec2 pos);
        void update_hadle_position();
        void handle_down(MouseButton button, glm::vec2 pos);
        void handle_move(glm::vec2 pos);
        void handle_up(MouseButton button, glm::vec2 pos);
    };
}

#endif
