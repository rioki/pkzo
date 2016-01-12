
#include "TeapotEngine.h"

#include <pkzo/Window.h>

#include "TeapotScreen.h"
#include "TeapotScene.h"
#include "CameraController.h"

namespace teapot
{
    TeapotEngine::TeapotEngine()
    : Engine("pkzo-teapot")
    {
        switch_screen(new TeapotScreen(pkzo::Vector2(get_window().get_width(), get_window().get_height()), get_library()));
        switch_scene(new TeapotScene(get_library()));

        controller = new CameraController(*this);
    }

    TeapotEngine::~TeapotEngine()
    {
        delete controller;
    }
}