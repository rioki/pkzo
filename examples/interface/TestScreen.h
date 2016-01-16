
#ifndef _TEST_SCREEN_H_
#define _TEST_SCREEN_H_

#include <pkzo/Screen.h>
#include <pkzo/Engine.h>
#include <pkzo/Text.h>
#include <pkzo/Rectangle.h>
#include <pkzo/Button.h>
#include <pkzo/CheckBox.h>
#include <pkzo/Slider.h>

namespace ui
{
    class TestScreen : public pkzo::Screen
    {
    public:
        TestScreen(pkzo::Engine& engine);

        ~TestScreen();

    private:
        pkzo::Text      title;
        pkzo::Rectangle panel;
        pkzo::Button    button;
        pkzo::Text      button_out;
        pkzo::CheckBox  checkbox;
        pkzo::Text      checkbox_out;
        pkzo::Slider    slider;
        pkzo::Text      slider_out;        
    };
}

#endif
