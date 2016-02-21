#include "EditorScreen.h"

#include <pkzo/pkzo.h>

namespace pm
{
    rgm::vec4 color(unsigned long hex)
    {
        unsigned long r = (0xFF000000 & hex) >> 24;
        unsigned long g = (0x00FF0000 & hex) >> 16;
        unsigned long b = (0x0000FF00 & hex) >> 8;
        unsigned long a = (0x000000FF & hex);  

        rgm::vec4 values;

        values[0] = static_cast<float>(r) / 255.0f;
        values[1] = static_cast<float>(g) / 255.0f;
        values[2] = static_cast<float>(b) / 255.0f;
        values[3] = static_cast<float>(a) / 255.0f;

        return values;
    }

    std::shared_ptr<pkzo::Font> load_font(const std::string& file, unsigned int size)
    {
        std::shared_ptr<pkzo::Font> font(new pkzo::Font);
        font->load(file, size);
        return font;
    }

    std::shared_ptr<pkzo::Texture> load_texture(const std::string& file)
    {
        std::shared_ptr<pkzo::Texture> texture(new pkzo::Texture);
        texture->load(file);
        return texture;
    }

    EditorScreen::EditorScreen(rgm::ivec2 size)
    : Screen(size)
    {
        ribbon.set_background_color(color(0x2d2d30ff));
        ribbon.set_font(load_font("../assets/fonts/DejaVuSans.ttf", 12));
        ribbon.set_text_color(color(0xc7c7c7FF));

        ribbon.add_icon(load_texture("../assets/icons/File-24.png"), "New", [this] () {
        
        });
        ribbon.add_icon(load_texture("../assets/icons/Open Folder-24.png"), "Open", [this] () {
        
        });
        ribbon.add_icon(load_texture("../assets/icons/Save-24.png"), "Save", [this] () {
        
        });
        ribbon.add_icon(load_texture("../assets/icons/Orthogonal View-24.png"), "Box", [this] () {
        
        });
        ribbon.add_icon(load_texture("../assets/icons/Beach Ball-24.png"), "Sphere", [this] () {
        
        });
        ribbon.add_icon(load_texture("../assets/icons/Teapot-24.png"), "Teapot", [this] () {
        
        });

        add_widget(ribbon);

        resize(size);
    }

    EditorScreen::~EditorScreen()
    {
    }

    void EditorScreen::resize(rgm::ivec2 size)
    {
        set_size(size);

        ribbon.set_width(size[0]);
    }
}