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

#pragma once
#include "config.h"

namespace pkzo
{
    //! Subsystem
    //!
    //! @note Bitwise operators are defined for this enum, you may
    //! combine systems with the | operator.
    enum class SdlSubsystem
    {
        AUDIO     = bit(0),
        VIDEO     = bit(1),
        JOYSTICK  = bit(2),
        HAPTIC    = bit(3),
        GAMEPAD   = bit(4),
        EVENTS    = bit(5),
        SENSOR    = bit(6),
        CAMERA    = bit(7)
    };

    //! Utility to initialize and cleanup SDL systems.
    //!
    //! SDL's subsytems are reference counted so use in an RAII way.
    class PKZO_API SdlSentry
    {
    public:
        //! Initialize the given SDL subsystems.
        explicit SdlSentry(SdlSubsystem subsystem);

        //! Cleanup the given SDL subsystems.
        ~SdlSentry();

    private:
        SdlSubsystem subsystem;

        SdlSentry(const SdlSentry&) = delete;
        SdlSentry& operator = (const SdlSentry&) = delete;
    };
}
