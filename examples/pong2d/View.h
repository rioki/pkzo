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

#ifndef _PONG2D_VIEW_H_
#define _PONG2D_VIEW_H_

#include <pkzo/pkzo.h>

namespace pong2d
{
    class Game;
    class Simulation;

    class View : public pkzo::Screen
    {
    public:
        View(Game& game, Simulation& simulation);

        void update(std::chrono::milliseconds dt) noexcept override;

        //void handle_key_down(pkzo::KeyMod mod, pkzo::Key key) override;
        //void handle_key_up(pkzo::KeyMod mod, pkzo::Key key) override;

    private:
        Game& game;
        Simulation& simulation;

        std::shared_ptr<pkzo::Text> left_score_text;
        std::shared_ptr<pkzo::Text> right_score_text;

        std::shared_ptr<pkzo::Rectangle> ball_pawn;
        std::shared_ptr<pkzo::Rectangle> left_paddle_pawn;
        std::shared_ptr<pkzo::Rectangle> right_paddle_pawn;

        pkzo::Key left_up_key;
        pkzo::Key left_down_key;
        pkzo::Key right_up_key;
        pkzo::Key right_down_key;
    };
}

#endif
