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

#include <cstdlib>
#include <pkzo/debug.h>
#include <pkzo/dialogs.h>

#include "App.h"

int main(int argc, char* argv[])
{
    pkzo::on_trace([] (const std::source_location& loc, const std::string_view msg) {
        tfm::printf("%s(%d): %s\n", pkzo::basename(loc.file_name()), loc.line(), msg);
    });
    #ifndef NDEBUG
    pkzo::on_trace([] (const std::source_location& loc, const std::string_view msg) {
        pkzo::debug_output(tfm::format("%s(%d): %s\n", pkzo::basename(loc.file_name()), loc.line(), msg));
    });
    #endif

    try
    {
        auto app = lab::App(argc, argv);
        app.run();
        return EXIT_SUCCESS;
    }
    catch (const std::exception& ex)
    {
        pkzo::show_message_box("Unexpected Error", ex.what());
        return EXIT_FAILURE;
    }
    catch (...)
    {
        pkzo::show_message_box("Unexpected Error", "Unknown error.");
        return EXIT_FAILURE;
    }
}
