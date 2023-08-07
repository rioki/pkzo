// pkzo
// Copyright 2023 Sean Farrell <sean.farrell@rioki.org>
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

#include <mutex>
#include <sstream>

#include <Windows.h>

namespace pkzo::test
{
    class DebugMonitor
    {
    public:
        DebugMonitor();
        ~DebugMonitor();

        std::string get_output() const noexcept;

    private:
        struct dbwin_buffer
        {
            DWORD dwProcessId;
            char  data[4096-sizeof(DWORD)];
        };

        mutable std::mutex mutex;
        std::stringstream  output;
        HANDLE             buffer_ready_event;
        HANDLE             data_ready_event;
        HANDLE             mapped_file;
        dbwin_buffer*      buffer;
        std::jthread       thread;

        DebugMonitor(const DebugMonitor&) = delete;
        DebugMonitor& operator = (const DebugMonitor&) = delete;
    };
}