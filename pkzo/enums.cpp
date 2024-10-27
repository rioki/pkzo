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

#include "enums.h"

#include <array>
#include <iostream>
#include <string>

#include <SDL2/SDL.h>

namespace pkzo
{
    std::ostream& operator << (std::ostream& os, const Key& key) noexcept
    {
        switch (key)
        {
            case Key::UNKNOWN: return os << "UNKNOWN";
            case Key::A: return os << "A";
            case Key::B: return os << "B";
            case Key::C: return os << "C";
            case Key::D: return os << "D";
            case Key::E: return os << "E";
            case Key::F: return os << "F";
            case Key::G: return os << "G";
            case Key::H: return os << "H";
            case Key::I: return os << "I";
            case Key::J: return os << "J";
            case Key::K: return os << "K";
            case Key::L: return os << "L";
            case Key::M: return os << "M";
            case Key::N: return os << "N";
            case Key::O: return os << "O";
            case Key::P: return os << "P";
            case Key::Q: return os << "Q";
            case Key::R: return os << "R";
            case Key::S: return os << "S";
            case Key::T: return os << "T";
            case Key::U: return os << "U";
            case Key::V: return os << "V";
            case Key::W: return os << "W";
            case Key::X: return os << "X";
            case Key::Y: return os << "Y";
            case Key::Z: return os << "Z";
            case Key::ONE: return os << "ONE";
            case Key::TWO: return os << "TWO";
            case Key::THREE: return os << "THREE";
            case Key::FOUR: return os << "FOUR";
            case Key::FIVE: return os << "FIVE";
            case Key::SIX: return os << "SIX";
            case Key::SEVEN: return os << "SEVEN";
            case Key::EIGHT: return os << "EIGHT";
            case Key::NINE: return os << "NINE";
            case Key::ZERO: return os << "ZERO";
            case Key::RETURN: return os << "RETURN";
            case Key::ESCAPE: return os << "ESCAPE";
            case Key::BACKSPACE: return os << "BACKSPACE";
            case Key::TAB: return os << "TAB";
            case Key::SPACE: return os << "SPACE";
            case Key::MINUS: return os << "MINUS";
            case Key::EQUALS: return os << "EQUALS";
            case Key::LEFTBRACKET: return os << "LEFTBRACKET";
            case Key::RIGHTBRACKET: return os << "RIGHTBRACKET";
            case Key::BACKSLASH: return os << "BACKSLASH";
            case Key::NONUSHASH: return os << "NONUSHASH";
            case Key::SEMICOLON: return os << "SEMICOLON";
            case Key::APOSTROPHE: return os << "APOSTROPHE";
            case Key::GRAVE: return os << "GRAVE";
            case Key::COMMA: return os << "COMMA";
            case Key::PERIOD: return os << "PERIOD";
            case Key::SLASH: return os << "SLASH";
            case Key::CAPSLOCK: return os << "CAPSLOCK";
            case Key::F1: return os << "F1";
            case Key::F2: return os << "F2";
            case Key::F3: return os << "F3";
            case Key::F4: return os << "F4";
            case Key::F5: return os << "F5";
            case Key::F6: return os << "F6";
            case Key::F7: return os << "F7";
            case Key::F8: return os << "F8";
            case Key::F9: return os << "F9";
            case Key::F10: return os << "F10";
            case Key::F11: return os << "F11";
            case Key::F12: return os << "F12";
            case Key::PRINTSCREEN: return os << "PRINTSCREEN";
            case Key::SCROLLLOCK: return os << "SCROLLLOCK";
            case Key::PAUSE: return os << "PAUSE";
            case Key::INSERT: return os << "INSERT";
            case Key::HOME: return os << "HOME";
            case Key::PAGEUP: return os << "PAGEUP";
            case Key::DELETE: return os << "DELETE";
            case Key::END: return os << "END";
            case Key::PAGEDOWN: return os << "PAGEDOWN";
            case Key::RIGHT: return os << "RIGHT";
            case Key::LEFT: return os << "LEFT";
            case Key::DOWN: return os << "DOWN";
            case Key::UP: return os << "UP";
            case Key::NUMLOCKCLEAR: return os << "NUMLOCKCLEAR";
            case Key::KP_DIVIDE: return os << "KP_DIVIDE";
            case Key::KP_MULTIPLY: return os << "KP_MULTIPLY";
            case Key::KP_MINUS: return os << "KP_MINUS";
            case Key::KP_PLUS: return os << "KP_PLUS";
            case Key::KP_ENTER: return os << "KP_ENTER";
            case Key::KP_1: return os << "KP_1";
            case Key::KP_2: return os << "KP_2";
            case Key::KP_3: return os << "KP_3";
            case Key::KP_4: return os << "KP_4";
            case Key::KP_5: return os << "KP_5";
            case Key::KP_6: return os << "KP_6";
            case Key::KP_7: return os << "KP_7";
            case Key::KP_8: return os << "KP_8";
            case Key::KP_9: return os << "KP_9";
            case Key::KP_0: return os << "KP_0";
            case Key::KP_PERIOD: return os << "KP_PERIOD";
            case Key::NONUSBACKSLASH: return os << "NONUSBACKSLASH";
            case Key::APPLICATION: return os << "APPLICATION";
            case Key::POWER: return os << "POWER";
            case Key::KP_EQUALS: return os << "KP_EQUALS";
            case Key::F13: return os << "F13";
            case Key::F14: return os << "F14";
            case Key::F15: return os << "F15";
            case Key::F16: return os << "F16";
            case Key::F17: return os << "F17";
            case Key::F18: return os << "F18";
            case Key::F19: return os << "F19";
            case Key::F20: return os << "F20";
            case Key::F21: return os << "F21";
            case Key::F22: return os << "F22";
            case Key::F23: return os << "F23";
            case Key::F24: return os << "F24";
            case Key::EXECUTE: return os << "EXECUTE";
            case Key::HELP: return os << "HELP";
            case Key::MENU: return os << "MENU";
            case Key::SELECT: return os << "SELECT";
            case Key::STOP: return os << "STOP";
            case Key::AGAIN: return os << "AGAIN";
            case Key::UNDO: return os << "UNDO";
            case Key::CUT: return os << "CUT";
            case Key::COPY: return os << "COPY";
            case Key::PASTE: return os << "PASTE";
            case Key::FIND: return os << "FIND";
            case Key::MUTE: return os << "MUTE";
            case Key::VOLUMEUP: return os << "VOLUMEUP";
            case Key::VOLUMEDOWN: return os << "VOLUMEDOWN";
            case Key::KP_COMMA: return os << "KP_COMMA";
            case Key::KP_EQUALSAS400: return os << "KP_EQUALSAS400";
            case Key::INTERNATIONAL1: return os << "INTERNATIONAL1";
            case Key::INTERNATIONAL2: return os << "INTERNATIONAL2";
            case Key::INTERNATIONAL3: return os << "INTERNATIONAL3";
            case Key::INTERNATIONAL4: return os << "INTERNATIONAL4";
            case Key::INTERNATIONAL5: return os << "INTERNATIONAL5";
            case Key::INTERNATIONAL6: return os << "INTERNATIONAL6";
            case Key::INTERNATIONAL7: return os << "INTERNATIONAL7";
            case Key::INTERNATIONAL8: return os << "INTERNATIONAL8";
            case Key::INTERNATIONAL9: return os << "INTERNATIONAL9";
            case Key::LANG1: return os << "LANG1";
            case Key::LANG2: return os << "LANG2";
            case Key::LANG3: return os << "LANG3";
            case Key::LANG4: return os << "LANG4";
            case Key::LANG5: return os << "LANG5";
            case Key::LANG6: return os << "LANG6";
            case Key::LANG7: return os << "LANG7";
            case Key::LANG8: return os << "LANG8";
            case Key::LANG9: return os << "LANG9";
            case Key::ALTERASE: return os << "ALTERASE";
            case Key::SYSREQ: return os << "SYSREQ";
            case Key::CANCEL: return os << "CANCEL";
            case Key::CLEAR: return os << "CLEAR";
            case Key::PRIOR: return os << "PRIOR";
            case Key::RETURN2: return os << "RETURN2";
            case Key::SEPARATOR: return os << "SEPARATOR";
            case Key::OUT: return os << "OUT";
            case Key::OPER: return os << "OPER";
            case Key::CLEARAGAIN: return os << "CLEARAGAIN";
            case Key::CRSEL: return os << "CRSEL";
            case Key::EXSEL: return os << "EXSEL";
            case Key::KP_00: return os << "KP_00";
            case Key::KP_000: return os << "KP_000";
            case Key::THOUSANDSSEPARATOR: return os << "THOUSANDSSEPARATOR";
            case Key::DECIMALSEPARATOR: return os << "DECIMALSEPARATOR";
            case Key::CURRENCYUNIT: return os << "CURRENCYUNIT";
            case Key::CURRENCYSUBUNIT: return os << "CURRENCYSUBUNIT";
            case Key::KP_LEFTPAREN: return os << "KP_LEFTPAREN";
            case Key::KP_RIGHTPAREN: return os << "KP_RIGHTPAREN";
            case Key::KP_LEFTBRACE: return os << "KP_LEFTBRACE";
            case Key::KP_RIGHTBRACE: return os << "KP_RIGHTBRACE";
            case Key::KP_TAB: return os << "KP_TAB";
            case Key::KP_BACKSPACE: return os << "KP_BACKSPACE";
            case Key::KP_A: return os << "KP_A";
            case Key::KP_B: return os << "KP_B";
            case Key::KP_C: return os << "KP_C";
            case Key::KP_D: return os << "KP_D";
            case Key::KP_E: return os << "KP_E";
            case Key::KP_F: return os << "KP_F";
            case Key::KP_XOR: return os << "KP_XOR";
            case Key::KP_POWER: return os << "KP_POWER";
            case Key::KP_PERCENT: return os << "KP_PERCENT";
            case Key::KP_LESS: return os << "KP_LESS";
            case Key::KP_GREATER: return os << "KP_GREATER";
            case Key::KP_AMPERSAND: return os << "KP_AMPERSAND";
            case Key::KP_DBLAMPERSAND: return os << "KP_DBLAMPERSAND";
            case Key::KP_VERTICALBAR: return os << "KP_VERTICALBAR";
            case Key::KP_DBLVERTICALBAR: return os << "KP_DBLVERTICALBAR";
            case Key::KP_COLON: return os << "KP_COLON";
            case Key::KP_HASH: return os << "KP_HASH";
            case Key::KP_SPACE: return os << "KP_SPACE";
            case Key::KP_AT: return os << "KP_AT";
            case Key::KP_EXCLAM: return os << "KP_EXCLAM";
            case Key::KP_MEMSTORE: return os << "KP_MEMSTORE";
            case Key::KP_MEMRECALL: return os << "KP_MEMRECALL";
            case Key::KP_MEMCLEAR: return os << "KP_MEMCLEAR";
            case Key::KP_MEMADD: return os << "KP_MEMADD";
            case Key::KP_MEMSUBTRACT: return os << "KP_MEMSUBTRACT";
            case Key::KP_MEMMULTIPLY: return os << "KP_MEMMULTIPLY";
            case Key::KP_MEMDIVIDE: return os << "KP_MEMDIVIDE";
            case Key::KP_PLUSMINUS: return os << "KP_PLUSMINUS";
            case Key::KP_CLEAR: return os << "KP_CLEAR";
            case Key::KP_CLEARENTRY: return os << "KP_CLEARENTRY";
            case Key::KP_BINARY: return os << "KP_BINARY";
            case Key::KP_OCTAL: return os << "KP_OCTAL";
            case Key::KP_DECIMAL: return os << "KP_DECIMAL";
            case Key::KP_HEXADECIMAL: return os << "KP_HEXADECIMAL";
            case Key::LCTRL: return os << "LCTRL";
            case Key::LSHIFT: return os << "LSHIFT";
            case Key::LALT: return os << "LALT";
            case Key::LGUI: return os << "LGUI";
            case Key::RCTRL: return os << "RCTRL";
            case Key::RSHIFT: return os << "RSHIFT";
            case Key::RALT: return os << "RALT";
            case Key::RGUI: return os << "RGUI";
            case Key::MODE: return os << "MODE";
            case Key::AUDIONEXT: return os << "AUDIONEXT";
            case Key::AUDIOPREV: return os << "AUDIOPREV";
            case Key::AUDIOSTOP: return os << "AUDIOSTOP";
            case Key::AUDIOPLAY: return os << "AUDIOPLAY";
            case Key::AUDIOMUTE: return os << "AUDIOMUTE";
            case Key::MEDIASELECT: return os << "MEDIASELECT";
            case Key::WWW: return os << "WWW";
            case Key::MAIL: return os << "MAIL";
            case Key::CALCULATOR: return os << "CALCULATOR";
            case Key::COMPUTER: return os << "COMPUTER";
            case Key::AC_SEARCH: return os << "AC_SEARCH";
            case Key::AC_HOME: return os << "AC_HOME";
            case Key::AC_BACK: return os << "AC_BACK";
            case Key::AC_FORWARD: return os << "AC_FORWARD";
            case Key::AC_STOP: return os << "AC_STOP";
            case Key::AC_REFRESH: return os << "AC_REFRESH";
            case Key::AC_BOOKMARKS: return os << "AC_BOOKMARKS";
            case Key::BRIGHTNESSDOWN: return os << "BRIGHTNESSDOWN";
            case Key::BRIGHTNESSUP: return os << "BRIGHTNESSUP";
            case Key::DISPLAYSWITCH: return os << "DISPLAYSWITCH";
            case Key::KBDILLUMTOGGLE: return os << "KBDILLUMTOGGLE";
            case Key::KBDILLUMDOWN: return os << "KBDILLUMDOWN";
            case Key::KBDILLUMUP: return os << "KBDILLUMUP";
            case Key::EJECT: return os << "EJECT";
            case Key::SLEEP: return os << "SLEEP";
            case Key::APP1: return os << "APP1";
            case Key::APP2: return os << "APP2";
            case Key::AUDIOREWIND: return os << "AUDIOREWIND";
            case Key::AUDIOFASTFORWARD: return os << "AUDIOFASTFORWARD";
            case Key::SOFTLEFT: return os << "SOFTLEFT";
            case Key::SOFTRIGHT: return os << "SOFTRIGHT";
            case Key::CALL: return os << "CALL";
            case Key::ENDCALL: return os << "ENDCALL";
            default: return os << "Unknown Key";
        }
    }

    std::ostream& operator << (std::ostream& os, const KeyMod& mod) noexcept
    {
        static const auto strings = std::array<std::pair<KeyMod, std::string>, 4>{{
            {KeyMod::SHIFT, "SHIFT"},
            {KeyMod::CTRL,  "CTRL"},
            {KeyMod::ALT,   "ALT"},
            {KeyMod::GUI,   "GUI"}
        }};

        auto first = true;
        for (const auto& [keyMod, name] : strings)
        {
            if ((mod & keyMod) == keyMod)
            {
                if (!first)
                {
                    os << "|";
                }
                os << name;
                first = false;
            }
        }

        if (first)
        {
            os << "NONE";
        }

        return os;
    }
}
