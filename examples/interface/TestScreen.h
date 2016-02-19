
#ifndef _TEST_SCREEN_H_
#define _TEST_SCREEN_H_

#include <pkzo2d/pkzo2d.h>
//#include <pkzoui/pkzoui.h>

namespace ui
{
    class TestScreen : public pkzo::Screen
    {
    public:
        TestScreen(rgm::ivec2 size);

        ~TestScreen();

    private:
        pkzo::Text      title;
        pkzo::Rectangle panel;
        //pkzo::Button    button;
        pkzo::Text      button_out;
        //pkzo::CheckBox  checkbox;
        pkzo::Text      checkbox_out;
        //pkzo::Slider    slider;
        pkzo::Text      slider_out;        
    };
}

#endif
