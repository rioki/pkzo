// pkzo
// Copyright 2010-2026 Sean Farrell
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
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

#include "Mouse.h"

#include "stdng.h"
#include "events.h"

namespace pkzo
{
    Mouse::Mouse()
    {
         input_slot = on_input([this] (const InputEvent& event) {
             std::visit(stdng::overloaded{
                 [this] (const MouseMoveEvent& e) {
                     move_signal.emit(e);
                 },
                 [this] (const MouseButtonDownEvent& e) {
                     button_down_signal.emit(e);
                 },
                 [this] (const MouseButtonUpEvent& e) {
                     button_up_signal.emit(e);
                 },
                 [this] (const MouseWheelEvent& e) {
                     wheel_signal.emit(e);
                 },
                 [] (const auto&) {}
             }, event);
         });
    }

    Mouse::~Mouse() = default;

    rsig::connection Mouse::on_move(const std::function<void (MouseMoveEvent)>& handler)
    {
        return move_signal.connect(handler);
    }

    rsig::connection Mouse::on_button_down(const std::function<void (MouseButtonDownEvent)>& handler)
    {
        return button_down_signal.connect(handler);
    }

    rsig::connection Mouse::on_button_up(const std::function<void (MouseButtonUpEvent)>& handler)
    {
        return button_up_signal.connect(handler);
    }

    rsig::connection Mouse::on_wheel(const std::function<void (MouseWheelEvent)>& handler)
    {
        return wheel_signal.connect(handler);
    }
}
