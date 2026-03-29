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

#include "Keyboard.h"

#include "stdng.h"

namespace pkzo
{
    Keyboard::Keyboard()
    {
         input_slot = on_input([this] (const InputEvent& event) {
             std::visit(stdng::overloaded{
                 [this] (const KeyDownEvent& e) {
                     key_down_signal.emit(e);
                 },
                 [this] (const KeyUpEvent& e) {
                     key_up_signal.emit(e);
                 },
                 [] (const auto&) {}
             }, event);
         });
    }

    Keyboard::~Keyboard() =default;

    rsig::connection Keyboard::on_key_down(const std::function<void (const KeyDownEvent&)>& handler)
    {
        return key_down_signal.connect(handler);
    }

    rsig::connection Keyboard::on_key_up(const std::function<void (const KeyUpEvent&)>& handler)
    {
        return key_up_signal.connect(handler);
    }
}
