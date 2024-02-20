// pkzo
// Copyright 2011-2024 Sean Farrell <sean.farrell@rioki.org>
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

#pragma once

#include <iostream>

#include <glm/glm.hpp>

#include "defines.h"

namespace pkzo
{
    enum class MouseButton
    {
        NONE    = 0,
        LEFT    = 1,
        MIDDLE  = 2,
        RIGHT   = 3,
        BUTTON4 = 4,
        BUTTON5 = 5
    };

    enum class Key
    {
        UNKNOWN            = 0,
        A                  = 4,
        B                  = 5,
        C                  = 6,
        D                  = 7,
        E                  = 8,
        F                  = 9,
        G                  = 10,
        H                  = 11,
        I                  = 12,
        J                  = 13,
        K                  = 14,
        L                  = 15,
        M                  = 16,
        N                  = 17,
        O                  = 18,
        P                  = 19,
        Q                  = 20,
        R                  = 21,
        S                  = 22,
        T                  = 23,
        U                  = 24,
        V                  = 25,
        W                  = 26,
        X                  = 27,
        Y                  = 28,
        Z                  = 29,
        ONE                = 30,
        TWO                = 31,
        THREE              = 32,
        FOUR               = 33,
        FIVE               = 34,
        SIX                = 35,
        SEVEN              = 36,
        EIGHT              = 37,
        NINE               = 38,
        ZERO               = 39,
        RETURN             = 40,
        ESCAPE             = 41,
        BACKSPACE          = 42,
        TAB                = 43,
        SPACE              = 44,
        MINUS              = 45,
        EQUALS             = 46,
        LEFTBRACKET        = 47,
        RIGHTBRACKET       = 48,
        BACKSLASH          = 49,
        NONUSHASH          = 50,
        SEMICOLON          = 51,
        APOSTROPHE         = 52,
        GRAVE              = 53,
        PERIOD             = 54,
        SLASH              = 55,
        CAPSLOCK           = 56,
        F1                 = 57,
        F2                 = 58,
        F3                 = 59,
        F4                 = 60,
        F5                 = 61,
        F6                 = 62,
        F7                 = 63,
        F8                 = 64,
        F9                 = 65,
        F10                = 66,
        F11                = 67,
        F12                = 68,
        PRINTSCREEN        = 69,
        SCROLLLOCK         = 70,
        PAUSE              = 71,
        INSERT             = 72,
        HOME               = 73,
        PAGEUP             = 74,
        DEL                = 75,
        END                = 76,
        PAGEDOWN           = 77,
        RIGHT              = 78,
        LEFT               = 79,
        DOWN               = 80,
        UP                 = 81,
        NUMLOCKCLEAR       = 82,
        KP_DIVIDE          = 83,
        KP_MULTIPLY        = 84,
        KP_MINUS           = 85,
        KP_PLUS            = 86,
        KP_ENTER           = 87,
        KP_1               = 88,
        KP_2               = 89,
        KP_3               = 90,
        KP_4               = 91,
        KP_5               = 92,
        KP_6               = 93,
        KP_7               = 94,
        KP_8               = 95,
        KP_9               = 96,
        KP_0               = 97,
        KPPERIOD           = 98,
        NONUSBACKSLASH     = 99,
        APPLICATION        = 101,
        POWER              = 102,
        KP_EQUALS          = 103,
        F13                = 104,
        F14                = 105,
        F15                = 106,
        F16                = 107,
        F17                = 108,
        F18                = 109,
        F19                = 110,
        F20                = 111,
        F21                = 112,
        F22                = 113,
        F23                = 114,
        F24                = 115,
        EXECUTE            = 116,
        HELP               = 117,
        MENU               = 118,
        SELECT             = 119,
        STOP               = 120,
        AGAIN              = 121,
        UNDO               = 122,
        CUT                = 123,
        COPY               = 124,
        PASTE              = 125,
        FIND               = 126,
        MUTE               = 127,
        VOLUMEUP           = 128,
        VOLUMEDOWN         = 129,
        KP_COMMA           = 133,
        KP_EQUALSAS400     = 134,
        INTERNATIONAL1     = 135,
        INTERNATIONAL2     = 136,
        INTERNATIONAL3     = 137,
        INTERNATIONAL4     = 138,
        INTERNATIONAL5     = 139,
        INTERNATIONAL6     = 140,
        INTERNATIONAL7     = 141,
        INTERNATIONAL8     = 142,
        INTERNATIONAL9     = 143,
        LANG1              = 144,
        LANG2              = 145,
        LANG3              = 146,
        LANG4              = 147,
        LANG5              = 148,
        LANG6              = 149,
        LANG7              = 150,
        LANG8              = 151,
        LANG9              = 152,
        ALTERASE           = 153,
        SYSREQ             = 154,
        CANCEL             = 155,
        CLEAR              = 156,
        PRIOR              = 157,
        RETURN2            = 158,
        SEPARATOR          = 159,
        OUT_               = 160,
        OPER               = 161,
        CLEARAGAIN         = 162,
        CRSEL              = 163,
        EXSEL              = 164,
        KP_00              = 176,
        KP_000             = 177,
        THOUSANDSSEPARATOR = 178,
        DECIMALSEPARATOR   = 179,
        CURRENCYUNIT       = 180,
        CURRENCYSUBUNIT    = 181,
        KP_LEFTPAREN       = 182,
        KP_RIGHTPAREN      = 183,
        KP_LEFTBRACE       = 184,
        KP_RIGHTBRACE      = 185,
        KP_TAB             = 186,
        KP_BACKSPACE       = 187,
        KP_A               = 188,
        KP_B               = 189,
        KP_C               = 190,
        KP_D               = 191,
        KP_E               = 192,
        KP_F               = 193,
        KP_XOR             = 194,
        KP_POWER           = 195,
        KP_PERCENT         = 196,
        KP_LESS            = 197,
        KP_GREATER         = 198,
        KP_AMPERSAND       = 199,
        KP_DBLAMPERSAND    = 200,
        KP_VERTICALBAR     = 201,
        KP_DBLVERTICALBAR  = 202,
        KP_COLON           = 203,
        KP_HASH            = 204,
        KP_SPACE           = 205,
        KP_AT              = 206,
        KP_EXCLAM          = 207,
        KP_MEMSTORE        = 208,
        KP_MEMRECALL       = 209,
        KP_MEMCLEAR        = 210,
        KP_MEMADD          = 211,
        KP_MEMSUBTRACT     = 212,
        KP_MEMMULTIPLY     = 213,
        KP_MEMDIVIDE       = 214,
        KP_PLUSMINUS       = 215,
        KP_CLEAR           = 216,
        KP_CLEARENTRY      = 217,
        KP_BINARY          = 218,
        KP_OCTAL           = 219,
        KP_DECIMAL         = 220,
        KP_HEXADECIMAL     = 221,
        LCTRL              = 224,
        LSHIFT             = 225,
        LALT               = 226,
        LGUI               = 227,
        RCTRL              = 228,
        RSHIFT             = 229,
        RALT               = 230,
        RGUI               = 231,
        MODE               = 257,
        AUDIONEXT          = 258,
        AUDIOPREV          = 259,
        AUDIOSTOP          = 260,
        AUDIOPLAY          = 261,
        AUDIOMUTE          = 262,
        MEDIASELECT        = 263,
        WWW                = 264,
        MAIL               = 265,
        CALCULATOR         = 266,
        COMPUTER           = 267,
        AC_SEARCH          = 268,
        AC_HOME            = 269,
        AC_BACK            = 270,
        AC_FORWARD         = 271,
        AC_STOP            = 272,
        AC_REFRESH         = 273,
        AC_BOOKMARKS       = 274,
        BRIGHTNESSDOWN     = 275,
        BRIGHTNESSUP       = 276,
        DISPLAYSWITCH      = 277,
        KBDILLUMTOGGLE     = 278,
        KBDILLUMDOWN       = 279,
        KBDILLUMUP         = 280,
        EJECT              = 281,
        SLEEP              = 282,
        APP1               = 283,
        APP2               = 284
    };

    enum class KeyMod
    {
        NONE   = 0,
        LSHIFT = 1,
        RSHIFT = 2,
        LCTRL  = 64,
        RCTRL  = 128,
        LALT   = 256,
        RALT   = 512,
        LGUI   = 1024,
        RGUI   = 2048,
        NUM    = 4096,
        CAPS   = 8192,
        MODE   = 16384,
        SCROLL = 32768,

        CTRL   = LCTRL | RCTRL,
        SHIFT  = LSHIFT | RSHIFT,
        ALT    = LALT | RALT,
        GUI    = LGUI | RGUI
    };

    inline KeyMod operator | (KeyMod lhs, KeyMod rhs) noexcept
    {
        return static_cast<KeyMod>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    inline KeyMod operator & (KeyMod lhs, KeyMod rhs) noexcept
    {
        return static_cast<KeyMod>(static_cast<int>(lhs) & static_cast<int>(rhs));
    }

    inline KeyMod operator ^ (KeyMod lhs, KeyMod rhs) noexcept
    {
        return static_cast<KeyMod>(static_cast<int>(lhs) ^ static_cast<int>(rhs));
    }

    PKZO_EXPORT std::ostream& operator << (std::ostream& os, MouseButton button);
    PKZO_EXPORT std::ostream& operator << (std::ostream& os, Key key);
    PKZO_EXPORT std::ostream& operator << (std::ostream& os, KeyMod mod);

    class PKZO_EXPORT InputHandler
    {
    public:
        virtual ~InputHandler() = default;

        virtual void handle_mouse_button_down(pkzo::MouseButton button, glm::ivec2 pos) {};
        virtual void handle_mouse_button_up(pkzo::MouseButton button, glm::ivec2 pos) {};
        virtual void handle_mouse_move(glm::ivec2 pos, glm::ivec2 rel) {};
        virtual void handle_mouse_wheel(glm::ivec2 rel) {};

        virtual void handle_keboard_down(pkzo::KeyMod mod, pkzo::Key key) {};
        virtual void handle_keboard_up(pkzo::KeyMod mod, pkzo::Key key) {};
        virtual void handle_keboard_text(const std::string_view text) {};
    };
}
