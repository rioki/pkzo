#include "TeapotScreen.h"

namespace teapot
{
    TeapotScreen::TeapotScreen(const pkzo::Vector2& size, pkzo::Library& library)
    : Screen(size[0], size[1])
    {
        auto caption_font = library.load_font("../assets/fonts/DejaVuSans.ttf", 32);
        auto text_font    = library.load_font("../assets/fonts/DejaVuSans.ttf", 18);

        set_background_color(pkzo::Color(0.0f, 0.0f, 0.0f, 0.0f));

        caption.set_font(caption_font);
        caption.set_text("Utah Teapot");

        explanation.set_font(text_font);
        explanation.set_text("Martin Newell needed a moderately simple mathematical model\n"
                             "of a familiar object for his work. His wife Sandra suggested \n"
                             "modelling their tea service since they were sitting down for \n"
                             "tea at the time.\n"
                             "He got some graph paper and a pencil, and sketched the entire\n"
                             "teapot by eye. Then he went back to the lab and edited bézier\n"
                             "control points on a Tektronix storage tube, again by hand.\n");
        
        explanation.set_position(size[0] - 10 - explanation.get_width(), size[1] - 10 - explanation.get_height());
        caption.set_position(explanation.get_x(), explanation.get_y() - 10 - caption.get_height());

        add_widget(explanation);
        add_widget(caption);
    }

    TeapotScreen::~TeapotScreen() {}
}