//
// pkzo
//
// Copyright 2010-2021 Sean Farrell <sean.farrell@rioki.org>
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

#include "pch.h"
#include "View.h"

#include "Game.h"
#include "Simulation.h"

namespace pong2d
{
    class ObjectView : public pkzo::two::Rectangle
    {
    public:
        ObjectView(Object& obj, const glm::vec4& color = glm::vec4(1.0f))
        : Rectangle(color, obj.get_size()), object(obj)
        {
            set_position(object.get_position());
        }

        void animate(std::chrono::milliseconds dt) override
        {
            Rectangle::animate(dt);
            set_position(object.get_position());
        }

    private:
        Object& object;
    };

    View::View(Game& g, Simulation& s)
    : Screen(s.get_field_size()), game(g), simulation(s)
    {
        auto score_font = std::make_shared<pkzo::Font>("../assets/fonts/Hardpixel.ttf", 60);

        left_score_text = std::make_shared<pkzo::two::Text>(score_font, pkzo::to_string(simulation.get_left_score()));
        left_score_text->set_position({-133, 250});
        add_node(left_score_text);

        right_score_text = std::make_shared<pkzo::two::Text>(score_font, pkzo::to_string(simulation.get_right_score()));
        right_score_text->set_position({133, 250});
        add_node(right_score_text);

        ball_pawn = std::make_shared<ObjectView>(simulation.get_ball());
        add_node(ball_pawn);

        left_paddle_pawn = std::make_shared<ObjectView>(simulation.get_left_paddle());
        add_node(left_paddle_pawn);

        right_paddle_pawn = std::make_shared<ObjectView>(simulation.get_right_paddle());
        add_node(right_paddle_pawn);

        auto& settings = game.get_settings();
        left_up_key    = settings.get_value("Player1", "up",   pkzo::Key::Q);
        left_down_key  = settings.get_value("Player1", "down", pkzo::Key::A);
        right_up_key   = settings.get_value("Player2", "up",   pkzo::Key::P);
        right_down_key = settings.get_value("Player2", "down", pkzo::Key::L);
    }

    void View::animate(std::chrono::milliseconds dt)
    {
        Screen::animate(dt);

        // REVIEW:
        // This looks expensive, consider implementing event callback.
        left_score_text->set_text(pkzo::to_string(simulation.get_left_score()));
        right_score_text->set_text(pkzo::to_string(simulation.get_right_score()));
    }

    void View::handle_key_down(pkzo::KeyMod mod, pkzo::Key key)
    {
        Screen::handle_key_down(mod, key);
        if (key == pkzo::Key::ESCAPE)
        {
            // TODO: PAUSE_MENU
            game.change_state(GameState::MAIN_MENU);
        }

        if (key == left_up_key)
        {
            simulation.get_left_paddle().start_up();
        }
        if (key == left_down_key)
        {
            simulation.get_left_paddle().start_down();
        }
        if (key == right_up_key)
        {
            simulation.get_right_paddle().start_up();
        }
        if (key == right_down_key)
        {
            simulation.get_right_paddle().start_down();
        }
    }

    void View::handle_key_up(pkzo::KeyMod mod, pkzo::Key key)
    {
        Screen::handle_key_up(mod, key);

        if (key == left_up_key)
        {
            simulation.get_left_paddle().stop_up();
        }
        if (key == left_down_key)
        {
            simulation.get_left_paddle().stop_down();
        }
        if (key == right_up_key)
        {
            simulation.get_right_paddle().stop_up();
        }
        if (key == right_down_key)
        {
            simulation.get_right_paddle().stop_down();
        }
    }
}
