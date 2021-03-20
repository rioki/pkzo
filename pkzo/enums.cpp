//
// pkzo
//
// Copyright 2014-2021 Sean Farrell <sean.farrell@rioki.org>
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
#include "enums.h"
#include "utils.h"

namespace pkzo
{
    std::vector<std::string> explode(const std::string& str, const std::string& delimiter)
    {
        std::vector<std::string> gibs;
        size_t start = 0;
        size_t end = 0;

        while ((start != std::string::npos) && (start < str.size()))
        {
            end = str.find(delimiter, start);

            std::string gib;
            if (end == std::string::npos)
            {
                gib = str.substr(start);
                start = std::string::npos;
            }
            else
            {
                gib = str.substr(start, end - start);
                start = end + delimiter.size();
            }
            gibs.push_back(gib);
        }

        return gibs;
    }

    std::ostream& operator << (std::ostream& os, WindowMode mode) noexcept
    {
        switch (mode)
        {
        case WindowMode::STATIC:
            os << "STATIC";
            break;
        case WindowMode::RESIZABLE:
            os << "RESIZABLE";
            break;
        case WindowMode::FULLSCREEN:
            os << "FULLSCREEN";
            break;
        default:
            assert(false);
            break;
        }
        return os;
    }

    std::istream& operator >> (std::istream& is, WindowMode& mode)
    {
        std::string word;
        is >> word;
        switch (hash(word))
        {
        case hash("STATIC"):
            mode = WindowMode::STATIC;
            break;
        case hash("RESIZABLE"):
            mode = WindowMode::RESIZABLE;
            break;
        case hash("FULLSCREEN"):
            mode = WindowMode::FULLSCREEN;
            break;
        default:
            throw format_error("Unknown WindowMode");
        }
        return is;
    }

    std::ostream& operator << (std::ostream& os, MouseButton button) noexcept
    {
        switch (button)
        {
        case MouseButton::NONE:
            os << "NONE";
            break;
        case MouseButton::LEFT:
            os << "LEFT";
            break;
        case MouseButton::MIDDLE:
            os << "MIDDLE";
            break;
        case MouseButton::RIGHT:
            os << "RIGHT";
            break;
        case MouseButton::BUTTON4:
            os << "BUTTON4";
            break;
        case MouseButton::BUTTON5:
            os << "BUTTON5";
            break;
        default:
            assert(false);
            break;
        }
        return os;
    }

    std::istream& operator >> (std::istream& is, MouseButton& button)
    {
        std::string word;
        is >> word;
        switch (hash(word))
        {
        case hash("NONE"):
            button = MouseButton::NONE;
            break;
        case hash("LEFT"):
            button = MouseButton::LEFT;
            break;
        case hash("MIDDLE"):
            button = MouseButton::MIDDLE;
            break;
        case hash("RIGHT"):
            button = MouseButton::RIGHT;
            break;
        case hash("BUTTON4"):
            button = MouseButton::BUTTON4;
            break;
        case hash("BUTTON5"):
            button = MouseButton::BUTTON5;
            break;
        default:
            throw format_error("Unknown MouseButton");
        }
        return is;
    }

    std::ostream& operator << (std::ostream& os, Key key) noexcept
    {
        switch (key)
        {
        case Key::UNDEFINED:
            os << "UNDEFINED";
            break;
        case Key::A:
            os << "A";
            break;
        case Key::B:
            os << "B";
            break;
        case Key::C:
            os << "C";
            break;
        case Key::D:
            os << "D";
            break;
        case Key::E:
            os << "E";
            break;
        case Key::F:
            os << "F";
            break;
        case Key::G:
            os << "G";
            break;
        case Key::H:
            os << "H";
            break;
        case Key::I:
            os << "I";
            break;
        case Key::J:
            os << "J";
            break;
        case Key::K:
            os << "K";
            break;
        case Key::L:
            os << "L";
            break;
        case Key::M:
            os << "M";
            break;
        case Key::N:
            os << "N";
            break;
        case Key::O:
            os << "O";
            break;
        case Key::P:
            os << "P";
            break;
        case Key::Q:
            os << "Q";
            break;
        case Key::R:
            os << "R";
            break;
        case Key::S:
            os << "S";
            break;
        case Key::T:
            os << "T";
            break;
        case Key::U:
            os << "U";
            break;
        case Key::V:
            os << "V";
            break;
        case Key::W:
            os << "W";
            break;
        case Key::X:
            os << "X";
            break;
        case Key::Y:
            os << "Y";
            break;
        case Key::Z:
            os << "Z";
            break;
        case Key::ONE:
            os << "ONE";
            break;
        case Key::TWO:
            os << "TWO";
            break;
        case Key::THREE:
            os << "THREE";
            break;
        case Key::FOUR:
            os << "FOUR";
            break;
        case Key::FIVE:
            os << "FIVE";
            break;
        case Key::SIX:
            os << "SIX";
            break;
        case Key::SEVEN:
            os << "SEVEN";
            break;
        case Key::EIGHT:
            os << "EIGHT";
            break;
        case Key::NINE:
            os << "NINE";
            break;
        case Key::ZERO:
            os << "ZERO";
            break;
        case Key::RETURN:
            os << "RETURN";
            break;
        case Key::ESCAPE:
            os << "ESCAPE";
            break;
        case Key::BACKSPACE:
            os << "BACKSPACE";
            break;
        case Key::TAB:
            os << "TAB";
            break;
        case Key::SPACE:
            os << "SPACE";
            break;
        case Key::MINUS:
            os << "MINUS";
            break;
        case Key::EQUALS:
            os << "EQUALS";
            break;
        case Key::LEFTBRACKET:
            os << "LEFTBRACKET";
            break;
        case Key::RIGHTBRACKET:
            os << "RIGHTBRACKET";
            break;
        case Key::BACKSLASH:
            os << "BACKSLASH";
            break;
        case Key::NONUSHASH:
            os << "NONUSHASH";
            break;
        case Key::SEMICOLON:
            os << "SEMICOLON";
            break;
        case Key::APOSTROPHE:
            os << "APOSTROPHE";
            break;
        case Key::GRAVE:
            os << "GRAVE";
            break;
        case Key::PERIOD:
            os << "PERIOD";
            break;
        case Key::SLASH:
            os << "SLASH";
            break;
        case Key::CAPSLOCK:
            os << "CAPSLOCK";
            break;
        case Key::F1:
            os << "F1";
            break;
        case Key::F2:
            os << "F2";
            break;
        case Key::F3:
            os << "F3";
            break;
        case Key::F4:
            os << "F4";
            break;
        case Key::F5:
            os << "F5";
            break;
        case Key::F6:
            os << "F6";
            break;
        case Key::F7:
            os << "F7";
            break;
        case Key::F8:
            os << "F8";
            break;
        case Key::F9:
            os << "F9";
            break;
        case Key::F10:
            os << "F10";
            break;
        case Key::F11:
            os << "F11";
            break;
        case Key::F12:
            os << "F12";
            break;
        case Key::PRINTSCREEN:
            os << "PRINTSCREEN";
            break;
        case Key::SCROLLLOCK:
            os << "SCROLLLOCK";
            break;
        case Key::PAUSE:
            os << "PAUSE";
            break;
        case Key::INSERT:
            os << "INSERT";
            break;
        case Key::HOME:
            os << "HOME";
            break;
        case Key::PAGEUP:
            os << "PAGEUP";
            break;
        case Key::DELETE:
            os << "DELETE";
            break;
        case Key::END:
            os << "END";
            break;
        case Key::PAGEDOWN:
            os << "PAGEDOWN";
            break;
        case Key::RIGHT:
            os << "RIGHT";
            break;
        case Key::LEFT:
            os << "LEFT";
            break;
        case Key::DOWN:
            os << "DOWN";
            break;
        case Key::UP:
            os << "UP";
            break;
        case Key::NUMLOCKCLEAR:
            os << "NUMLOCKCLEAR";
            break;
        case Key::KPDIVIDE:
            os << "KPDIVIDE";
            break;
        case Key::KPMULTIPLY:
            os << "KPMULTIPLY";
            break;
        case Key::KPMINUS:
            os << "KPMINUS";
            break;
        case Key::KPPLUS:
            os << "KPPLUS";
            break;
        case Key::KPENTER:
            os << "KPENTER";
            break;
        case Key::KP1:
            os << "KP1";
            break;
        case Key::KP2:
            os << "KP2";
            break;
        case Key::KP3:
            os << "KP3";
            break;
        case Key::KP4:
            os << "KP4";
            break;
        case Key::KP5:
            os << "KP5";
            break;
        case Key::KP6:
            os << "KP6";
            break;
        case Key::KP7:
            os << "KP7";
            break;
        case Key::KP8:
            os << "KP8";
            break;
        case Key::KP9:
            os << "KP9";
            break;
        case Key::KP0:
            os << "KP0";
            break;
        case Key::KPPERIOD:
            os << "KPPERIOD";
            break;
        case Key::NONUSBACKSLASH:
            os << "NONUSBACKSLASH";
            break;
        case Key::APPLICATION:
            os << "APPLICATION";
            break;
        case Key::POWER:
            os << "POWER";
            break;
        case Key::KPEQUALS:
            os << "KPEQUALS";
            break;
        case Key::F13:
            os << "F13";
            break;
        case Key::F14:
            os << "F14";
            break;
        case Key::F15:
            os << "F15";
            break;
        case Key::F16:
            os << "F16";
            break;
        case Key::F17:
            os << "F17";
            break;
        case Key::F18:
            os << "F18";
            break;
        case Key::F19:
            os << "F19";
            break;
        case Key::F20:
            os << "F20";
            break;
        case Key::F21:
            os << "F21";
            break;
        case Key::F22:
            os << "F22";
            break;
        case Key::F23:
            os << "F23";
            break;
        case Key::F24:
            os << "F24";
            break;
        case Key::EXECUTE:
            os << "EXECUTE";
            break;
        case Key::HELP:
            os << "HELP";
            break;
        case Key::MENU:
            os << "MENU";
            break;
        case Key::SELECT:
            os << "SELECT";
            break;
        case Key::STOP:
            os << "STOP";
            break;
        case Key::AGAIN:
            os << "AGAIN";
            break;
        case Key::UNDO:
            os << "UNDO";
            break;
        case Key::CUT:
            os << "CUT";
            break;
        case Key::COPY:
            os << "COPY";
            break;
        case Key::PASTE:
            os << "PASTE";
            break;
        case Key::FIND:
            os << "FIND";
            break;
        case Key::MUTE:
            os << "MUTE";
            break;
        case Key::VOLUMEUP:
            os << "VOLUMEUP";
            break;
        case Key::VOLUMEDOWN:
            os << "VOLUMEDOWN";
            break;
        case Key::KPCOMMA:
            os << "KPCOMMA";
            break;
        case Key::KPEQUALSAS400:
            os << "KPEQUALSAS400";
            break;
        case Key::INTERNATIONAL1:
            os << "INTERNATIONAL1";
            break;
        case Key::INTERNATIONAL2:
            os << "INTERNATIONAL2";
            break;
        case Key::INTERNATIONAL3:
            os << "INTERNATIONAL3";
            break;
        case Key::INTERNATIONAL4:
            os << "INTERNATIONAL4";
            break;
        case Key::INTERNATIONAL5:
            os << "INTERNATIONAL5";
            break;
        case Key::INTERNATIONAL6:
            os << "INTERNATIONAL6";
            break;
        case Key::INTERNATIONAL7:
            os << "INTERNATIONAL7";
            break;
        case Key::INTERNATIONAL8:
            os << "INTERNATIONAL8";
            break;
        case Key::INTERNATIONAL9:
            os << "INTERNATIONAL9";
            break;
        case Key::LANG1:
            os << "LANG1";
            break;
        case Key::LANG2:
            os << "LANG2";
            break;
        case Key::LANG3:
            os << "LANG3";
            break;
        case Key::LANG4:
            os << "LANG4";
            break;
        case Key::LANG5:
            os << "LANG5";
            break;
        case Key::LANG6:
            os << "LANG6";
            break;
        case Key::LANG7:
            os << "LANG7";
            break;
        case Key::LANG8:
            os << "LANG8";
            break;
        case Key::LANG9:
            os << "LANG9";
            break;
        case Key::ALTERASE:
            os << "ALTERASE";
            break;
        case Key::SYSREQ:
            os << "SYSREQ";
            break;
        case Key::CANCEL:
            os << "CANCEL";
            break;
        case Key::CLEAR:
            os << "CLEAR";
            break;
        case Key::PRIOR:
            os << "PRIOR";
            break;
        case Key::RETURN2:
            os << "RETURN2";
            break;
        case Key::SEPARATOR:
            os << "SEPARATOR";
            break;
        case Key::OUT:
            os << "OUT";
            break;
        case Key::OPER:
            os << "OPER";
            break;
        case Key::CLEARAGAIN:
            os << "CLEARAGAIN";
            break;
        case Key::CRSEL:
            os << "CRSEL";
            break;
        case Key::EXSEL:
            os << "EXSEL";
            break;
        case Key::KP00:
            os << "KP00";
            break;
        case Key::KP000:
            os << "KP000";
            break;
        case Key::THOUSANDSSEPARATOR:
            os << "THOUSANDSSEPARATOR";
            break;
        case Key::DECIMALSEPARATOR:
            os << "DECIMALSEPARATOR";
            break;
        case Key::CURRENCYUNIT:
            os << "CURRENCYUNIT";
            break;
        case Key::CURRENCYSUBUNIT:
            os << "CURRENCYSUBUNIT";
            break;
        case Key::KPLEFTPAREN:
            os << "KPLEFTPAREN";
            break;
        case Key::KPRIGHTPAREN:
            os << "KPRIGHTPAREN";
            break;
        case Key::KPLEFTBRACE:
            os << "KPLEFTBRACE";
            break;
        case Key::KPRIGHTBRACE:
            os << "KPRIGHTBRACE";
            break;
        case Key::KPTAB:
            os << "KPTAB";
            break;
        case Key::KPBACKSPACE:
            os << "KPBACKSPACE";
            break;
        case Key::KPA:
            os << "KPA";
            break;
        case Key::KPB:
            os << "KPB";
            break;
        case Key::KPC:
            os << "KPC";
            break;
        case Key::KPD:
            os << "KPD";
            break;
        case Key::KPE:
            os << "KPE";
            break;
        case Key::KPF:
            os << "KPF";
            break;
        case Key::KPXOR:
            os << "KPXOR";
            break;
        case Key::KPPOWER:
            os << "KPPOWER";
            break;
        case Key::KPPERCENT:
            os << "KPPERCENT";
            break;
        case Key::KPLESS:
            os << "KPLESS";
            break;
        case Key::KPGREATER:
            os << "KPGREATER";
            break;
        case Key::KPAMPERSAND:
            os << "KPAMPERSAND";
            break;
        case Key::KPDBLAMPERSAND:
            os << "KPDBLAMPERSAND";
            break;
        case Key::KPVERTICALBAR:
            os << "KPVERTICALBAR";
            break;
        case Key::KPDBLVERTICALBAR:
            os << "KPDBLVERTICALBAR";
            break;
        case Key::KPCOLON:
            os << "KPCOLON";
            break;
        case Key::KPHASH:
            os << "KPHASH";
            break;
        case Key::KPSPACE:
            os << "KPSPACE";
            break;
        case Key::KPAT:
            os << "KPAT";
            break;
        case Key::KPEXCLAM:
            os << "KPEXCLAM";
            break;
        case Key::KPMEMSTORE:
            os << "KPMEMSTORE";
            break;
        case Key::KPMEMRECALL:
            os << "KPMEMRECALL";
            break;
        case Key::KPMEMCLEAR:
            os << "KPMEMCLEAR";
            break;
        case Key::KPMEMADD:
            os << "KPMEMADD";
            break;
        case Key::KPMEMSUBTRACT:
            os << "KPMEMSUBTRACT";
            break;
        case Key::KPMEMMULTIPLY:
            os << "KPMEMMULTIPLY";
            break;
        case Key::KPMEMDIVIDE:
            os << "KPMEMDIVIDE";
            break;
        case Key::KPPLUSMINUS:
            os << "KPPLUSMINUS";
            break;
        case Key::KPCLEAR:
            os << "KPCLEAR";
            break;
        case Key::KPCLEARENTRY:
            os << "KPCLEARENTRY";
            break;
        case Key::KPBINARY:
            os << "KPBINARY";
            break;
        case Key::KPOCTAL:
            os << "KPOCTAL";
            break;
        case Key::KPDECIMAL:
            os << "KPDECIMAL";
            break;
        case Key::KPHEXADECIMAL:
            os << "KPHEXADECIMAL";
            break;
        case Key::LCTRL:
            os << "LCTRL";
            break;
        case Key::LSHIFT:
            os << "LSHIFT";
            break;
        case Key::LALT:
            os << "LALT";
            break;
        case Key::LGUI:
            os << "LGUI";
            break;
        case Key::RCTRL:
            os << "RCTRL";
            break;
        case Key::RSHIFT:
            os << "RSHIFT";
            break;
        case Key::RALT:
            os << "RALT";
            break;
        case Key::RGUI:
            os << "RGUI";
            break;
        case Key::MODE:
            os << "MODE";
            break;
        case Key::AUDIONEXT:
            os << "AUDIONEXT";
            break;
        case Key::AUDIOPREV:
            os << "AUDIOPREV";
            break;
        case Key::AUDIOSTOP:
            os << "AUDIOSTOP";
            break;
        case Key::AUDIOPLAY:
            os << "AUDIOPLAY";
            break;
        case Key::AUDIOMUTE:
            os << "AUDIOMUTE";
            break;
        case Key::MEDIASELECT:
            os << "MEDIASELECT";
            break;
        case Key::WWW:
            os << "WWW";
            break;
        case Key::MAIL:
            os << "MAIL";
            break;
        case Key::CALCULATOR:
            os << "CALCULATOR";
            break;
        case Key::COMPUTER:
            os << "COMPUTER";
            break;
        case Key::ACSEARCH:
            os << "ACSEARCH";
            break;
        case Key::ACHOME:
            os << "ACHOME";
            break;
        case Key::ACBACK:
            os << "ACBACK";
            break;
        case Key::ACFORWARD:
            os << "ACFORWARD";
            break;
        case Key::ACSTOP:
            os << "ACSTOP";
            break;
        case Key::ACREFRESH:
            os << "ACREFRESH";
            break;
        case Key::ACBOOKMARKS:
            os << "ACBOOKMARKS";
            break;
        case Key::BRIGHTNESSDOWN:
            os << "BRIGHTNESSDOWN";
            break;
        case Key::BRIGHTNESSUP:
            os << "BRIGHTNESSUP";
            break;
        case Key::DISPLAYSWITCH:
            os << "DISPLAYSWITCH";
            break;
        case Key::KBDILLUMTOGGLE:
            os << "KBDILLUMTOGGLE";
            break;
        case Key::KBDILLUMDOWN:
            os << "KBDILLUMDOWN";
            break;
        case Key::KBDILLUMUP:
            os << "KBDILLUMUP";
            break;
        case Key::EJECT:
            os << "EJECT";
            break;
        case Key::SLEEP:
            os << "SLEEP";
            break;
        case Key::APP1:
            os << "APP1";
            break;
        case Key::APP2:
            os << "APP2";
            break;
        default:
            assert(false);
            break;
        }
        return os;
    }

    std::istream& operator >> (std::istream& is, Key& key)
    {
        std::string word;
        is >> word;
        switch (hash(word))
        {
        case hash("UNDEFINED"):
            key = Key::UNDEFINED;
            break;
        case hash("A"):
            key = Key::A;
            break;
        case hash("B"):
            key = Key::B;
            break;
        case hash("C"):
            key = Key::C;
            break;
        case hash("D"):
            key = Key::D;
            break;
        case hash("E"):
            key = Key::E;
            break;
        case hash("F"):
            key = Key::F;
            break;
        case hash("G"):
            key = Key::G;
            break;
        case hash("H"):
            key = Key::H;
            break;
        case hash("I"):
            key = Key::I;
            break;
        case hash("J"):
            key = Key::J;
            break;
        case hash("K"):
            key = Key::K;
            break;
        case hash("L"):
            key = Key::L;
            break;
        case hash("M"):
            key = Key::M;
            break;
        case hash("N"):
            key = Key::N;
            break;
        case hash("O"):
            key = Key::O;
            break;
        case hash("P"):
            key = Key::P;
            break;
        case hash("Q"):
            key = Key::Q;
            break;
        case hash("R"):
            key = Key::R;
            break;
        case hash("S"):
            key = Key::S;
            break;
        case hash("T"):
            key = Key::T;
            break;
        case hash("U"):
            key = Key::U;
            break;
        case hash("V"):
            key = Key::V;
            break;
        case hash("W"):
            key = Key::W;
            break;
        case hash("X"):
            key = Key::X;
            break;
        case hash("Y"):
            key = Key::Y;
            break;
        case hash("Z"):
            key = Key::Z;
            break;
        case hash("ONE"):
            key = Key::ONE;
            break;
        case hash("TWO"):
            key = Key::TWO;
            break;
        case hash("THREE"):
            key = Key::THREE;
            break;
        case hash("FOUR"):
            key = Key::FOUR;
            break;
        case hash("FIVE"):
            key = Key::FIVE;
            break;
        case hash("SIX"):
            key = Key::SIX;
            break;
        case hash("SEVEN"):
            key = Key::SEVEN;
            break;
        case hash("EIGHT"):
            key = Key::EIGHT;
            break;
        case hash("NINE"):
            key = Key::NINE;
            break;
        case hash("ZERO"):
            key = Key::ZERO;
            break;
        case hash("RETURN"):
            key = Key::RETURN;
            break;
        case hash("ESCAPE"):
            key = Key::ESCAPE;
            break;
        case hash("BACKSPACE"):
            key = Key::BACKSPACE;
            break;
        case hash("TAB"):
            key = Key::TAB;
            break;
        case hash("SPACE"):
            key = Key::SPACE;
            break;
        case hash("MINUS"):
            key = Key::MINUS;
            break;
        case hash("EQUALS"):
            key = Key::EQUALS;
            break;
        case hash("LEFTBRACKET"):
            key = Key::LEFTBRACKET;
            break;
        case hash("RIGHTBRACKET"):
            key = Key::RIGHTBRACKET;
            break;
        case hash("BACKSLASH"):
            key = Key::BACKSLASH;
            break;
        case hash("NONUSHASH"):
            key = Key::NONUSHASH;
            break;
        case hash("SEMICOLON"):
            key = Key::SEMICOLON;
            break;
        case hash("APOSTROPHE"):
            key = Key::APOSTROPHE;
            break;
        case hash("GRAVE"):
            key = Key::GRAVE;
            break;
        case hash("PERIOD"):
            key = Key::PERIOD;
            break;
        case hash("SLASH"):
            key = Key::SLASH;
            break;
        case hash("CAPSLOCK"):
            key = Key::CAPSLOCK;
            break;
        case hash("F1"):
            key = Key::F1;
            break;
        case hash("F2"):
            key = Key::F2;
            break;
        case hash("F3"):
            key = Key::F3;
            break;
        case hash("F4"):
            key = Key::F4;
            break;
        case hash("F5"):
            key = Key::F5;
            break;
        case hash("F6"):
            key = Key::F6;
            break;
        case hash("F7"):
            key = Key::F7;
            break;
        case hash("F8"):
            key = Key::F8;
            break;
        case hash("F9"):
            key = Key::F9;
            break;
        case hash("F10"):
            key = Key::F10;
            break;
        case hash("F11"):
            key = Key::F11;
            break;
        case hash("F12"):
            key = Key::F12;
            break;
        case hash("PRINTSCREEN"):
            key = Key::PRINTSCREEN;
            break;
        case hash("SCROLLLOCK"):
            key = Key::SCROLLLOCK;
            break;
        case hash("PAUSE"):
            key = Key::PAUSE;
            break;
        case hash("INSERT"):
            key = Key::INSERT;
            break;
        case hash("HOME"):
            key = Key::HOME;
            break;
        case hash("PAGEUP"):
            key = Key::PAGEUP;
            break;
        case hash("DELETE"):
            key = Key::DELETE;
            break;
        case hash("END"):
            key = Key::END;
            break;
        case hash("PAGEDOWN"):
            key = Key::PAGEDOWN;
            break;
        case hash("RIGHT"):
            key = Key::RIGHT;
            break;
        case hash("LEFT"):
            key = Key::LEFT;
            break;
        case hash("DOWN"):
            key = Key::DOWN;
            break;
        case hash("UP"):
            key = Key::UP;
            break;
        case hash("NUMLOCKCLEAR"):
            key = Key::NUMLOCKCLEAR;
            break;
        case hash("KPDIVIDE"):
            key = Key::KPDIVIDE;
            break;
        case hash("KPMULTIPLY"):
            key = Key::KPMULTIPLY;
            break;
        case hash("KPMINUS"):
            key = Key::KPMINUS;
            break;
        case hash("KPPLUS"):
            key = Key::KPPLUS;
            break;
        case hash("KPENTER"):
            key = Key::KPENTER;
            break;
        case hash("KP1"):
            key = Key::KP1;
            break;
        case hash("KP2"):
            key = Key::KP2;
            break;
        case hash("KP3"):
            key = Key::KP3;
            break;
        case hash("KP4"):
            key = Key::KP4;
            break;
        case hash("KP5"):
            key = Key::KP5;
            break;
        case hash("KP6"):
            key = Key::KP6;
            break;
        case hash("KP7"):
            key = Key::KP7;
            break;
        case hash("KP8"):
            key = Key::KP8;
            break;
        case hash("KP9"):
            key = Key::KP9;
            break;
        case hash("KP0"):
            key = Key::KP0;
            break;
        case hash("KPPERIOD"):
            key = Key::KPPERIOD;
            break;
        case hash("NONUSBACKSLASH"):
            key = Key::NONUSBACKSLASH;
            break;
        case hash("APPLICATION"):
            key = Key::APPLICATION;
            break;
        case hash("POWER"):
            key = Key::POWER;
            break;
        case hash("KPEQUALS"):
            key = Key::KPEQUALS;
            break;
        case hash("F13"):
            key = Key::F13;
            break;
        case hash("F14"):
            key = Key::F14;
            break;
        case hash("F15"):
            key = Key::F15;
            break;
        case hash("F16"):
            key = Key::F16;
            break;
        case hash("F17"):
            key = Key::F17;
            break;
        case hash("F18"):
            key = Key::F18;
            break;
        case hash("F19"):
            key = Key::F19;
            break;
        case hash("F20"):
            key = Key::F20;
            break;
        case hash("F21"):
            key = Key::F21;
            break;
        case hash("F22"):
            key = Key::F22;
            break;
        case hash("F23"):
            key = Key::F23;
            break;
        case hash("F24"):
            key = Key::F24;
            break;
        case hash("EXECUTE"):
            key = Key::EXECUTE;
            break;
        case hash("HELP"):
            key = Key::HELP;
            break;
        case hash("MENU"):
            key = Key::MENU;
            break;
        case hash("SELECT"):
            key = Key::SELECT;
            break;
        case hash("STOP"):
            key = Key::STOP;
            break;
        case hash("AGAIN"):
            key = Key::AGAIN;
            break;
        case hash("UNDO"):
            key = Key::UNDO;
            break;
        case hash("CUT"):
            key = Key::CUT;
            break;
        case hash("COPY"):
            key = Key::COPY;
            break;
        case hash("PASTE"):
            key = Key::PASTE;
            break;
        case hash("FIND"):
            key = Key::FIND;
            break;
        case hash("MUTE"):
            key = Key::MUTE;
            break;
        case hash("VOLUMEUP"):
            key = Key::VOLUMEUP;
            break;
        case hash("VOLUMEDOWN"):
            key = Key::VOLUMEDOWN;
            break;
        case hash("KPCOMMA"):
            key = Key::KPCOMMA;
            break;
        case hash("KPEQUALSAS400"):
            key = Key::KPEQUALSAS400;
            break;
        case hash("INTERNATIONAL1"):
            key = Key::INTERNATIONAL1;
            break;
        case hash("INTERNATIONAL2"):
            key = Key::INTERNATIONAL2;
            break;
        case hash("INTERNATIONAL3"):
            key = Key::INTERNATIONAL3;
            break;
        case hash("INTERNATIONAL4"):
            key = Key::INTERNATIONAL4;
            break;
        case hash("INTERNATIONAL5"):
            key = Key::INTERNATIONAL5;
            break;
        case hash("INTERNATIONAL6"):
            key = Key::INTERNATIONAL6;
            break;
        case hash("INTERNATIONAL7"):
            key = Key::INTERNATIONAL7;
            break;
        case hash("INTERNATIONAL8"):
            key = Key::INTERNATIONAL8;
            break;
        case hash("INTERNATIONAL9"):
            key = Key::INTERNATIONAL9;
            break;
        case hash("LANG1"):
            key = Key::LANG1;
            break;
        case hash("LANG2"):
            key = Key::LANG2;
            break;
        case hash("LANG3"):
            key = Key::LANG3;
            break;
        case hash("LANG4"):
            key = Key::LANG4;
            break;
        case hash("LANG5"):
            key = Key::LANG5;
            break;
        case hash("LANG6"):
            key = Key::LANG6;
            break;
        case hash("LANG7"):
            key = Key::LANG7;
            break;
        case hash("LANG8"):
            key = Key::LANG8;
            break;
        case hash("LANG9"):
            key = Key::LANG9;
            break;
        case hash("ALTERASE"):
            key = Key::ALTERASE;
            break;
        case hash("SYSREQ"):
            key = Key::SYSREQ;
            break;
        case hash("CANCEL"):
            key = Key::CANCEL;
            break;
        case hash("CLEAR"):
            key = Key::CLEAR;
            break;
        case hash("PRIOR"):
            key = Key::PRIOR;
            break;
        case hash("RETURN2"):
            key = Key::RETURN2;
            break;
        case hash("SEPARATOR"):
            key = Key::SEPARATOR;
            break;
        case hash("OUT"):
            key = Key::OUT;
            break;
        case hash("OPER"):
            key = Key::OPER;
            break;
        case hash("CLEARAGAIN"):
            key = Key::CLEARAGAIN;
            break;
        case hash("CRSEL"):
            key = Key::CRSEL;
            break;
        case hash("EXSEL"):
            key = Key::EXSEL;
            break;
        case hash("KP00"):
            key = Key::KP00;
            break;
        case hash("KP000"):
            key = Key::KP000;
            break;
        case hash("THOUSANDSSEPARATOR"):
            key = Key::THOUSANDSSEPARATOR;
            break;
        case hash("DECIMALSEPARATOR"):
            key = Key::DECIMALSEPARATOR;
            break;
        case hash("CURRENCYUNIT"):
            key = Key::CURRENCYUNIT;
            break;
        case hash("CURRENCYSUBUNIT"):
            key = Key::CURRENCYSUBUNIT;
            break;
        case hash("KPLEFTPAREN"):
            key = Key::KPLEFTPAREN;
            break;
        case hash("KPRIGHTPAREN"):
            key = Key::KPRIGHTPAREN;
            break;
        case hash("KPLEFTBRACE"):
            key = Key::KPLEFTBRACE;
            break;
        case hash("KPRIGHTBRACE"):
            key = Key::KPRIGHTBRACE;
            break;
        case hash("KPTAB"):
            key = Key::KPTAB;
            break;
        case hash("KPBACKSPACE"):
            key = Key::KPBACKSPACE;
            break;
        case hash("KPA"):
            key = Key::KPA;
            break;
        case hash("KPB"):
            key = Key::KPB;
            break;
        case hash("KPC"):
            key = Key::KPC;
            break;
        case hash("KPD"):
            key = Key::KPD;
            break;
        case hash("KPE"):
            key = Key::KPE;
            break;
        case hash("KPF"):
            key = Key::KPF;
            break;
        case hash("KPXOR"):
            key = Key::KPXOR;
            break;
        case hash("KPPOWER"):
            key = Key::KPPOWER;
            break;
        case hash("KPPERCENT"):
            key = Key::KPPERCENT;
            break;
        case hash("KPLESS"):
            key = Key::KPLESS;
            break;
        case hash("KPGREATER"):
            key = Key::KPGREATER;
            break;
        case hash("KPAMPERSAND"):
            key = Key::KPAMPERSAND;
            break;
        case hash("KPDBLAMPERSAND"):
            key = Key::KPDBLAMPERSAND;
            break;
        case hash("KPVERTICALBAR"):
            key = Key::KPVERTICALBAR;
            break;
        case hash("KPDBLVERTICALBAR"):
            key = Key::KPDBLVERTICALBAR;
            break;
        case hash("KPCOLON"):
            key = Key::KPCOLON;
            break;
        case hash("KPHASH"):
            key = Key::KPHASH;
            break;
        case hash("KPSPACE"):
            key = Key::KPSPACE;
            break;
        case hash("KPAT"):
            key = Key::KPAT;
            break;
        case hash("KPEXCLAM"):
            key = Key::KPEXCLAM;
            break;
        case hash("KPMEMSTORE"):
            key = Key::KPMEMSTORE;
            break;
        case hash("KPMEMRECALL"):
            key = Key::KPMEMRECALL;
            break;
        case hash("KPMEMCLEAR"):
            key = Key::KPMEMCLEAR;
            break;
        case hash("KPMEMADD"):
            key = Key::KPMEMADD;
            break;
        case hash("KPMEMSUBTRACT"):
            key = Key::KPMEMSUBTRACT;
            break;
        case hash("KPMEMMULTIPLY"):
            key = Key::KPMEMMULTIPLY;
            break;
        case hash("KPMEMDIVIDE"):
            key = Key::KPMEMDIVIDE;
            break;
        case hash("KPPLUSMINUS"):
            key = Key::KPPLUSMINUS;
            break;
        case hash("KPCLEAR"):
            key = Key::KPCLEAR;
            break;
        case hash("KPCLEARENTRY"):
            key = Key::KPCLEARENTRY;
            break;
        case hash("KPBINARY"):
            key = Key::KPBINARY;
            break;
        case hash("KPOCTAL"):
            key = Key::KPOCTAL;
            break;
        case hash("KPDECIMAL"):
            key = Key::KPDECIMAL;
            break;
        case hash("KPHEXADECIMAL"):
            key = Key::KPHEXADECIMAL;
            break;
        case hash("LCTRL"):
            key = Key::LCTRL;
            break;
        case hash("LSHIFT"):
            key = Key::LSHIFT;
            break;
        case hash("LALT"):
            key = Key::LALT;
            break;
        case hash("LGUI"):
            key = Key::LGUI;
            break;
        case hash("RCTRL"):
            key = Key::RCTRL;
            break;
        case hash("RSHIFT"):
            key = Key::RSHIFT;
            break;
        case hash("RALT"):
            key = Key::RALT;
            break;
        case hash("RGUI"):
            key = Key::RGUI;
            break;
        case hash("MODE"):
            key = Key::MODE;
            break;
        case hash("AUDIONEXT"):
            key = Key::AUDIONEXT;
            break;
        case hash("AUDIOPREV"):
            key = Key::AUDIOPREV;
            break;
        case hash("AUDIOSTOP"):
            key = Key::AUDIOSTOP;
            break;
        case hash("AUDIOPLAY"):
            key = Key::AUDIOPLAY;
            break;
        case hash("AUDIOMUTE"):
            key = Key::AUDIOMUTE;
            break;
        case hash("MEDIASELECT"):
            key = Key::MEDIASELECT;
            break;
        case hash("WWW"):
            key = Key::WWW;
            break;
        case hash("MAIL"):
            key = Key::MAIL;
            break;
        case hash("CALCULATOR"):
            key = Key::CALCULATOR;
            break;
        case hash("COMPUTER"):
            key = Key::COMPUTER;
            break;
        case hash("ACSEARCH"):
            key = Key::ACSEARCH;
            break;
        case hash("ACHOME"):
            key = Key::ACHOME;
            break;
        case hash("ACBACK"):
            key = Key::ACBACK;
            break;
        case hash("ACFORWARD"):
            key = Key::ACFORWARD;
            break;
        case hash("ACSTOP"):
            key = Key::ACSTOP;
            break;
        case hash("ACREFRESH"):
            key = Key::ACREFRESH;
            break;
        case hash("ACBOOKMARKS"):
            key = Key::ACBOOKMARKS;
            break;
        case hash("BRIGHTNESSDOWN"):
            key = Key::BRIGHTNESSDOWN;
            break;
        case hash("BRIGHTNESSUP"):
            key = Key::BRIGHTNESSUP;
            break;
        case hash("DISPLAYSWITCH"):
            key = Key::DISPLAYSWITCH;
            break;
        case hash("KBDILLUMTOGGLE"):
            key = Key::KBDILLUMTOGGLE;
            break;
        case hash("KBDILLUMDOWN"):
            key = Key::KBDILLUMDOWN;
            break;
        case hash("KBDILLUMUP"):
            key = Key::KBDILLUMUP;
            break;
        case hash("EJECT"):
            key = Key::EJECT;
            break;
        case hash("SLEEP"):
            key = Key::SLEEP;
            break;
        case hash("APP1"):
            key = Key::APP1;
            break;
        case hash("APP2"):
            key = Key::APP2;
            break;
        default:
            throw format_error("Unknown Key");
        }
        return is;
    }

    std::ostream& operator << (std::ostream& os, KeyMod mod) noexcept
    {
        if (mod == KeyMod::NONE)
        {
            os << "NONE";
        }

        bool prev_mod = false;
        if ((mod & KeyMod::SHIFT) == KeyMod::SHIFT)
        {
            os << "SHIFT";
            prev_mod = true;
        }

        if ((mod & KeyMod::CTRL) == KeyMod::CTRL)
        {
            if (prev_mod)
            {
                os << "+";
            }
            os << "CTRL";
            prev_mod = true;
        }

        if ((mod & KeyMod::ALT) == KeyMod::ALT)
        {
            if (prev_mod)
            {
                os << "+";
            }
            os << "ALT";
            prev_mod = true;
        }

        if ((mod & KeyMod::META) == KeyMod::META)
        {
            if (prev_mod)
            {
                os << "+";
            }
            os << "META";
            prev_mod = true;
        }

        return os;
    }

    std::istream& operator >> (std::istream& is, KeyMod& mod)
    {
        std::string word;
        is >> word;

        mod = KeyMod::NONE;

        auto bits = explode(word, "+");
        for (const auto& bit : bits)
        {
            switch (hash(bit))
            {
            case hash("SHIFT"):
                mod |= KeyMod::SHIFT;
                break;
            case hash("CTRL"):
                mod |= KeyMod::CTRL;
                break;
            case hash("ALT"):
                mod |= KeyMod::ALT;
                break;
            case hash("META"):
                mod |= KeyMod::META;
                break;
            default:
                throw format_error("Unknown KeyMod");
            }
        }

        return is;
    }

    PKZO_EXPORT std::string to_string(KeyMod mod, Key key)
    {
        std::stringstream buff;

        if (mod != KeyMod::NONE)
        {
            buff << mod << "+";
        }
        buff << key;

        return buff.str();
    }
}
