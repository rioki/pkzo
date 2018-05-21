/*
  pkzo

  Copyright (c) 2014-2018 Sean Farrell

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "Key.h"

#include <iostream>

#if _MSC_VER
namespace std
{
	istream& operator >> (istream& is, string& str)
	{
		string tmp;

		int c = is.get();
		while (c != EOF && c != ' ' && c != '\t' && c != '\r' && c != '\n')
		{
			tmp.push_back(static_cast<char>(c));
			c = is.get();
		}

		is.unget();
		str = tmp;
		return is;
	}
}
#endif

namespace pkzo
{
    std::ostream& operator << (std::ostream& os, Key key)
    {
        switch (key)
        {
            case KEY_UNKNOWN:
                os << "UNKNOWN";
                break;
            case KEY_A:
                os << "A";
                break;
            case KEY_B:
                os << "B";
                break;
            case KEY_C:
                os << "C";
                break;
            case KEY_D:
                os << "D";
                break;
            case KEY_E:
                os << "E";
                break;
            case KEY_F:
                os << "F";
                break;
            case KEY_G:
                os << "G";
                break;
            case KEY_H:
                os << "H";
                break;
            case KEY_I:
                os << "I";
                break;
            case KEY_J:
                os << "J";
                break;
            case KEY_K:
                os << "K";
                break;
            case KEY_L:
                os << "L";
                break;
            case KEY_M:
                os << "M";
                break;
            case KEY_N:
                os << "N";
                break;
            case KEY_O:
                os << "O";
                break;
            case KEY_P:
                os << "P";
                break;
            case KEY_Q:
                os << "Q";
                break;
            case KEY_R:
                os << "R";
                break;
            case KEY_S:
                os << "S";
                break;
            case KEY_T:
                os << "T";
                break;
            case KEY_U:
                os << "U";
                break;
            case KEY_V:
                os << "V";
                break;
            case KEY_W:
                os << "W";
                break;
            case KEY_X:
                os << "X";
                break;
            case KEY_Y:
                os << "Y";
                break;
            case KEY_Z:
                os << "Z";
                break;
            case KEY_1:
                os << "1";
                break;
            case KEY_2:
                os << "2";
                break;
            case KEY_3:
                os << "3";
                break;
            case KEY_4:
                os << "4";
                break;
            case KEY_5:
                os << "5";
                break;
            case KEY_6:
                os << "6";
                break;
            case KEY_7:
                os << "7";
                break;
            case KEY_8:
                os << "8";
                break;
            case KEY_9:
                os << "9";
                break;
            case KEY_0:
                os << "0";
                break;
            case KEY_RETURN:
                os << "RETURN";
                break;
            case KEY_ESCAPE:
                os << "ESCAPE";
                break;
            case KEY_BACKSPACE:
                os << "BACKSPACE";
                break;
            case KEY_TAB:
                os << "TAB";
                break;
            case KEY_SPACE:
                os << "SPACE";
                break;
            case KEY_MINUS:
                os << "MINUS";
                break;
            case KEY_EQUALS:
                os << "EQUALS";
                break;
            case KEY_LEFTBRACKET:
                os << "LEFTBRACKET";
                break;
            case KEY_RIGHTBRACKET:
                os << "RIGHTBRACKET";
                break;
            case KEY_BACKSLASH:
                os << "BACKSLASH";
                break;
            case KEY_NONUSHASH:
                os << "NONUSHASH";
                break;
            case KEY_SEMICOLON:
                os << "SEMICOLON";
                break;
            case KEY_APOSTROPHE:
                os << "APOSTROPHE";
                break;
            case KEY_GRAVE:
                os << "GRAVE";
                break;
            case KEY_PERIOD:
                os << "PERIOD";
                break;
            case KEY_SLASH:
                os << "SLASH";
                break;
            case KEY_CAPSLOCK:
                os << "CAPSLOCK";
                break;
            case KEY_F1:
                os << "F1";
                break;
            case KEY_F2:
                os << "F2";
                break;
            case KEY_F3:
                os << "F3";
                break;
            case KEY_F4:
                os << "F4";
                break;
            case KEY_F5:
                os << "F5";
                break;
            case KEY_F6:
                os << "F6";
                break;
            case KEY_F7:
                os << "F7";
                break;
            case KEY_F8:
                os << "F8";
                break;
            case KEY_F9:
                os << "F9";
                break;
            case KEY_F10:
                os << "F10";
                break;
            case KEY_F11:
                os << "F11";
                break;
            case KEY_F12:
                os << "F12";
                break;
            case KEY_PRINTSCREEN:
                os << "PRINTSCREEN";
                break;
            case KEY_SCROLLLOCK:
                os << "SCROLLLOCK";
                break;
            case KEY_PAUSE:
                os << "PAUSE";
                break;
            case KEY_INSERT:
                os << "INSERT";
                break;
            case KEY_HOME:
                os << "HOME";
                break;
            case KEY_PAGEUP:
                os << "PAGEUP";
                break;
            case KEY_DELETE:
                os << "DELETE";
                break;
            case KEY_END:
                os << "END";
                break;
            case KEY_PAGEDOWN:
                os << "PAGEDOWN";
                break;
            case KEY_RIGHT:
                os << "RIGHT";
                break;
            case KEY_LEFT:
                os << "LEFT";
                break;
            case KEY_DOWN:
                os << "DOWN";
                break;
            case KEY_UP:
                os << "UP";
                break;
            case KEY_NUMLOCKCLEAR:
                os << "NUMLOCKCLEAR";
                break;
            case KEY_KP_DIVIDE:
                os << "KP_DIVIDE";
                break;
            case KEY_KP_MULTIPLY:
                os << "KP_MULTIPLY";
                break;
            case KEY_KP_MINUS:
                os << "KP_MINUS";
                break;
            case KEY_KP_PLUS:
                os << "KP_PLUS";
                break;
            case KEY_KP_ENTER:
                os << "KP_ENTER";
                break;
            case KEY_KP_1:
                os << "KP_1";
                break;
            case KEY_KP_2:
                os << "KP_2";
                break;
            case KEY_KP_3:
                os << "KP_3";
                break;
            case KEY_KP_4:
                os << "KP_4";
                break;
            case KEY_KP_5:
                os << "KP_5";
                break;
            case KEY_KP_6:
                os << "KP_6";
                break;
            case KEY_KP_7:
                os << "KP_7";
                break;
            case KEY_KP_8:
                os << "KP_8";
                break;
            case KEY_KP_9:
                os << "KP_9";
                break;
            case KEY_KP_0:
                os << "KP_0";
                break;
            case KEY_KP_PERIOD:
                os << "KP_PERIOD";
                break;
            case KEY_NONUSBACKSLASH:
                os << "NONUSBACKSLASH";
                break;
            case KEY_APPLICATION:
                os << "APPLICATION";
                break;
            case KEY_POWER:
                os << "POWER";
                break;
            case KEY_KP_EQUALS:
                os << "KP_EQUALS";
                break;
            case KEY_F13:
                os << "F13";
                break;
            case KEY_F14:
                os << "F14";
                break;
            case KEY_F15:
                os << "F15";
                break;
            case KEY_F16:
                os << "F16";
                break;
            case KEY_F17:
                os << "F17";
                break;
            case KEY_F18:
                os << "F18";
                break;
            case KEY_F19:
                os << "F19";
                break;
            case KEY_F20:
                os << "F20";
                break;
            case KEY_F21:
                os << "F21";
                break;
            case KEY_F22:
                os << "F22";
                break;
            case KEY_F23:
                os << "F23";
                break;
            case KEY_F24:
                os << "F24";
                break;
            case KEY_EXECUTE:
                os << "EXECUTE";
                break;
            case KEY_HELP:
                os << "HELP";
                break;
            case KEY_MENU:
                os << "MENU";
                break;
            case KEY_SELECT:
                os << "SELECT";
                break;
            case KEY_STOP:
                os << "STOP";
                break;
            case KEY_AGAIN:
                os << "AGAIN";
                break;
            case KEY_UNDO:
                os << "UNDO";
                break;
            case KEY_CUT:
                os << "CUT";
                break;
            case KEY_COPY:
                os << "COPY";
                break;
            case KEY_PASTE:
                os << "PASTE";
                break;
            case KEY_FIND:
                os << "FIND";
                break;
            case KEY_MUTE:
                os << "MUTE";
                break;
            case KEY_VOLUMEUP:
                os << "VOLUMEUP";
                break;
            case KEY_VOLUMEDOWN:
                os << "VOLUMEDOWN";
                break;
            case KEY_KP_COMMA:
                os << "KP_COMMA";
                break;
            case KEY_KP_EQUALSAS400:
                os << "KP_EQUALSAS400";
                break;
            case KEY_INTERNATIONAL1:
                os << "INTERNATIONAL1";
                break;
            case KEY_INTERNATIONAL2:
                os << "INTERNATIONAL2";
                break;
            case KEY_INTERNATIONAL3:
                os << "INTERNATIONAL3";
                break;
            case KEY_INTERNATIONAL4:
                os << "INTERNATIONAL4";
                break;
            case KEY_INTERNATIONAL5:
                os << "INTERNATIONAL5";
                break;
            case KEY_INTERNATIONAL6:
                os << "INTERNATIONAL6";
                break;
            case KEY_INTERNATIONAL7:
                os << "INTERNATIONAL7";
                break;
            case KEY_INTERNATIONAL8:
                os << "INTERNATIONAL8";
                break;
            case KEY_INTERNATIONAL9:
                os << "INTERNATIONAL9";
                break;
            case KEY_LANG1:
                os << "LANG1";
                break;
            case KEY_LANG2:
                os << "LANG2";
                break;
            case KEY_LANG3:
                os << "LANG3";
                break;
            case KEY_LANG4:
                os << "LANG4";
                break;
            case KEY_LANG5:
                os << "LANG5";
                break;
            case KEY_LANG6:
                os << "LANG6";
                break;
            case KEY_LANG7:
                os << "LANG7";
                break;
            case KEY_LANG8:
                os << "LANG8";
                break;
            case KEY_LANG9:
                os << "LANG9";
                break;
            case KEY_ALTERASE:
                os << "ALTERASE";
                break;
            case KEY_SYSREQ:
                os << "SYSREQ";
                break;
            case KEY_CANCEL:
                os << "CANCEL";
                break;
            case KEY_CLEAR:
                os << "CLEAR";
                break;
            case KEY_PRIOR:
                os << "PRIOR";
                break;
            case KEY_RETURN2:
                os << "RETURN2";
                break;
            case KEY_SEPARATOR:
                os << "SEPARATOR";
                break;
            case KEY_OUT:
                os << "OUT";
                break;
            case KEY_OPER:
                os << "OPER";
                break;
            case KEY_CLEARAGAIN:
                os << "CLEARAGAIN";
                break;
            case KEY_CRSEL:
                os << "CRSEL";
                break;
            case KEY_EXSEL:
                os << "EXSEL";
                break;
            case KEY_KP_00:
                os << "KP_00";
                break;
            case KEY_KP_000:
                os << "KP_000";
                break;
            case KEY_THOUSANDSSEPARATOR:
                os << "THOUSANDSSEPARATOR";
                break;
            case KEY_DECIMALSEPARATOR:
                os << "DECIMALSEPARATOR";
                break;
            case KEY_CURRENCYUNIT:
                os << "CURRENCYUNIT";
                break;
            case KEY_CURRENCYSUBUNIT:
                os << "CURRENCYSUBUNIT";
                break;
            case KEY_KP_LEFTPAREN:
                os << "KP_LEFTPAREN";
                break;
            case KEY_KP_RIGHTPAREN:
                os << "KP_RIGHTPAREN";
                break;
            case KEY_KP_LEFTBRACE:
                os << "KP_LEFTBRACE";
                break;
            case KEY_KP_RIGHTBRACE:
                os << "KP_RIGHTBRACE";
                break;
            case KEY_KP_TAB:
                os << "KP_TAB";
                break;
            case KEY_KP_BACKSPACE:
                os << "KP_BACKSPACE";
                break;
            case KEY_KP_A:
                os << "KP_A";
                break;
            case KEY_KP_B:
                os << "KP_B";
                break;
            case KEY_KP_C:
                os << "KP_C";
                break;
            case KEY_KP_D:
                os << "KP_D";
                break;
            case KEY_KP_E:
                os << "KP_E";
                break;
            case KEY_KP_F:
                os << "KP_F";
                break;
            case KEY_KP_XOR:
                os << "KP_XOR";
                break;
            case KEY_KP_POWER:
                os << "KP_POWER";
                break;
            case KEY_KP_PERCENT:
                os << "KP_PERCENT";
                break;
            case KEY_KP_LESS:
                os << "KP_LESS";
                break;
            case KEY_KP_GREATER:
                os << "KP_GREATER";
                break;
            case KEY_KP_AMPERSAND:
                os << "KP_AMPERSAND";
                break;
            case KEY_KP_DBLAMPERSAND:
                os << "KP_DBLAMPERSAND";
                break;
            case KEY_KP_VERTICALBAR:
                os << "KP_VERTICALBAR";
                break;
            case KEY_KP_DBLVERTICALBAR:
                os << "KP_DBLVERTICALBAR";
                break;
            case KEY_KP_COLON:
                os << "KP_COLON";
                break;
            case KEY_KP_HASH:
                os << "KP_HASH";
                break;
            case KEY_KP_SPACE:
                os << "KP_SPACE";
                break;
            case KEY_KP_AT:
                os << "KP_AT";
                break;
            case KEY_KP_EXCLAM:
                os << "KP_EXCLAM";
                break;
            case KEY_KP_MEMSTORE:
                os << "KP_MEMSTORE";
                break;
            case KEY_KP_MEMRECALL:
                os << "KP_MEMRECALL";
                break;
            case KEY_KP_MEMCLEAR:
                os << "KP_MEMCLEAR";
                break;
            case KEY_KP_MEMADD:
                os << "KP_MEMADD";
                break;
            case KEY_KP_MEMSUBTRACT:
                os << "KP_MEMSUBTRACT";
                break;
            case KEY_KP_MEMMULTIPLY:
                os << "KP_MEMMULTIPLY";
                break;
            case KEY_KP_MEMDIVIDE:
                os << "KP_MEMDIVIDE";
                break;
            case KEY_KP_PLUSMINUS:
                os << "KP_PLUSMINUS";
                break;
            case KEY_KP_CLEAR:
                os << "KP_CLEAR";
                break;
            case KEY_KP_CLEARENTRY:
                os << "KP_CLEARENTRY";
                break;
            case KEY_KP_BINARY:
                os << "KP_BINARY";
                break;
            case KEY_KP_OCTAL:
                os << "KP_OCTAL";
                break;
            case KEY_KP_DECIMAL:
                os << "KP_DECIMAL";
                break;
            case KEY_KP_HEXADECIMAL:
                os << "KP_HEXADECIMAL";
                break;
            case KEY_LCTRL:
                os << "LCTRL";
                break;
            case KEY_LSHIFT:
                os << "LSHIFT";
                break;
            case KEY_LALT:
                os << "LALT";
                break;
            case KEY_LGUI:
                os << "LGUI";
                break;
            case KEY_RCTRL:
                os << "RCTRL";
                break;
            case KEY_RSHIFT:
                os << "RSHIFT";
                break;
            case KEY_RALT:
                os << "RALT";
                break;
            case KEY_RGUI:
                os << "RGUI";
                break;
            case KEY_MODE:
                os << "MODE";
                break;
            case KEY_AUDIONEXT:
                os << "AUDIONEXT";
                break;
            case KEY_AUDIOPREV:
                os << "AUDIOPREV";
                break;
            case KEY_AUDIOSTOP:
                os << "AUDIOSTOP";
                break;
            case KEY_AUDIOPLAY:
                os << "AUDIOPLAY";
                break;
            case KEY_AUDIOMUTE:
                os << "AUDIOMUTE";
                break;
            case KEY_MEDIASELECT:
                os << "MEDIASELECT";
                break;
            case KEY_WWW:
                os << "WWW";
                break;
            case KEY_MAIL:
                os << "MAIL";
                break;
            case KEY_CALCULATOR:
                os << "CALCULATOR";
                break;
            case KEY_COMPUTER:
                os << "COMPUTER";
                break;
            case KEY_AC_SEARCH:
                os << "AC_SEARCH";
                break;
            case KEY_AC_HOME:
                os << "AC_HOME";
                break;
            case KEY_AC_BACK:
                os << "AC_BACK";
                break;
            case KEY_AC_FORWARD:
                os << "AC_FORWARD";
                break;
            case KEY_AC_STOP:
                os << "AC_STOP";
                break;
            case KEY_AC_REFRESH:
                os << "AC_REFRESH";
                break;
            case KEY_AC_BOOKMARKS:
                os << "AC_BOOKMARKS";
                break;
            case KEY_BRIGHTNESSDOWN:
                os << "BRIGHTNESSDOWN";
                break;
            case KEY_BRIGHTNESSUP:
                os << "BRIGHTNESSUP";
                break;
            case KEY_DISPLAYSWITCH:
                os << "DISPLAYSWITCH";
                break;
            case KEY_KBDILLUMTOGGLE:
                os << "KBDILLUMTOGGLE";
                break;
            case KEY_KBDILLUMDOWN:
                os << "KBDILLUMDOWN";
                break;
            case KEY_KBDILLUMUP:
                os << "KBDILLUMUP";
                break;
            case KEY_EJECT:
                os << "EJECT";
                break;
            case KEY_SLEEP:
                os << "SLEEP";
                break;
            case KEY_APP1:
                os << "APP1";
                break;
            case KEY_APP2:
                os << "APP2";
                break;  
            default:
                os << (unsigned int) key;
                break;            
        }
        return os;
    }

    std::istream& operator >> (std::istream& is, Key& key)
    {
        std::string s;
        is >> s;
        
		key = KEY_UNKNOWN;

        if (s == "UNKNOWN")
        {
            key = KEY_UNKNOWN;
        }
        if (s == "A")
        {
            key = KEY_A;
        }
        if (s == "B")
        {
            key = KEY_B;
        }
        if (s == "C")
        {
            key = KEY_C;
        }
        if (s == "D")
        {
            key = KEY_D;
        }
        if (s == "E")
        {
            key = KEY_E;
        }
        if (s == "F")
        {
            key = KEY_F;
        }
        if (s == "G")
        {
            key = KEY_G;
        }
        if (s == "H")
        {
            key = KEY_H;
        }
        if (s == "I")
        {
            key = KEY_I;
        }
        if (s == "J")
        {
            key = KEY_J;
        }
        if (s == "K")
        {
            key = KEY_K;
        }
        if (s == "L")
        {
            key = KEY_L;
        }
        if (s == "M")
        {
            key = KEY_M;
        }
        if (s == "N")
        {
            key = KEY_N;
        }
        if (s == "O")
        {
            key = KEY_O;
        }
        if (s == "P")
        {
            key = KEY_P;
        }
        if (s == "Q")
        {
            key = KEY_Q;
        }
        if (s == "R")
        {
            key = KEY_R;
        }
        if (s == "S")
        {
            key = KEY_S;
        }
        if (s == "T")
        {
            key = KEY_T;
        }
        if (s == "U")
        {
            key = KEY_U;
        }
        if (s == "V")
        {
            key = KEY_V;
        }
        if (s == "W")
        {
            key = KEY_W;
        }
        if (s == "X")
        {
            key = KEY_X;
        }
        if (s == "Y")
        {
            key = KEY_Y;
        }
        if (s == "Z")
        {
            key = KEY_Z;
        }
        if (s == "1")
        {
            key = KEY_1;
        }
        if (s == "2")
        {
            key = KEY_2;
        }
        if (s == "3")
        {
            key = KEY_3;
        }
        if (s == "4")
        {
            key = KEY_4;
        }
        if (s == "5")
        {
            key = KEY_5;
        }
        if (s == "6")
        {
            key = KEY_6;
        }
        if (s == "7")
        {
            key = KEY_7;
        }
        if (s == "8")
        {
            key = KEY_8;
        }
        if (s == "9")
        {
            key = KEY_9;
        }
        if (s == "0")
        {
            key = KEY_0;
        }
        if (s == "RETURN")
        {
            key = KEY_RETURN;
        }
        if (s == "ESCAPE")
        {
            key = KEY_ESCAPE;
        }
        if (s == "BACKSPACE")
        {
            key = KEY_BACKSPACE;
        }
        if (s == "TAB")
        {
            key = KEY_TAB;
        }
        if (s == "SPACE")
        {
            key = KEY_SPACE;
        }
        if (s == "MINUS")
        {
            key = KEY_MINUS;
        }
        if (s == "EQUALS")
        {
            key = KEY_EQUALS;
        }
        if (s == "LEFTBRACKET")
        {
            key = KEY_LEFTBRACKET;
        }
        if (s == "RIGHTBRACKET")
        {
            key = KEY_RIGHTBRACKET;
        }
        if (s == "BACKSLASH")
        {
            key = KEY_BACKSLASH;
        }
        if (s == "NONUSHASH")
        {
            key = KEY_NONUSHASH;
        }
        if (s == "SEMICOLON")
        {
            key = KEY_SEMICOLON;
        }
        if (s == "APOSTROPHE")
        {
            key = KEY_APOSTROPHE;
        }
        if (s == "GRAVE")
        {
            key = KEY_GRAVE;
        }
        if (s == "PERIOD")
        {
            key = KEY_PERIOD;
        }
        if (s == "SLASH")
        {
            key = KEY_SLASH;
        }
        if (s == "CAPSLOCK")
        {
            key = KEY_CAPSLOCK;
        }
        if (s == "F1")
        {
            key = KEY_F1;
        }
        if (s == "F2")
        {
            key = KEY_F2;
        }
        if (s == "F3")
        {
            key = KEY_F3;
        }
        if (s == "F4")
        {
            key = KEY_F4;
        }
        if (s == "F5")
        {
            key = KEY_F5;
        }
        if (s == "F6")
        {
            key = KEY_F6;
        }
        if (s == "F7")
        {
            key = KEY_F7;
        }
        if (s == "F8")
        {
            key = KEY_F8;
        }
        if (s == "F9")
        {
            key = KEY_F9;
        }
        if (s == "F10")
        {
            key = KEY_F10;
        }
        if (s == "F11")
        {
            key = KEY_F11;
        }
        if (s == "F12")
        {
            key = KEY_F12;
        }
        if (s == "PRINTSCREEN")
        {
            key = KEY_PRINTSCREEN;
        }
        if (s == "SCROLLLOCK")
        {
            key = KEY_SCROLLLOCK;
        }
        if (s == "PAUSE")
        {
            key = KEY_PAUSE;
        }
        if (s == "INSERT")
        {
            key = KEY_INSERT;
        }
        if (s == "HOME")
        {
            key = KEY_HOME;
        }
        if (s == "PAGEUP")
        {
            key = KEY_PAGEUP;
        }
        if (s == "DELETE")
        {
            key = KEY_DELETE;
        }
        if (s == "END")
        {
            key = KEY_END;
        }
        if (s == "PAGEDOWN")
        {
            key = KEY_PAGEDOWN;
        }
        if (s == "RIGHT")
        {
            key = KEY_RIGHT;
        }
        if (s == "LEFT")
        {
            key = KEY_LEFT;
        }
        if (s == "DOWN")
        {
            key = KEY_DOWN;
        }
        if (s == "UP")
        {
            key = KEY_UP;
        }
        if (s == "NUMLOCKCLEAR")
        {
            key = KEY_NUMLOCKCLEAR;
        }
        if (s == "KP_DIVIDE")
        {
            key = KEY_KP_DIVIDE;
        }
        if (s == "KP_MULTIPLY")
        {
            key = KEY_KP_MULTIPLY;
        }
        if (s == "KP_MINUS")
        {
            key = KEY_KP_MINUS;
        }
        if (s == "KP_PLUS")
        {
            key = KEY_KP_PLUS;
        }
        if (s == "KP_ENTER")
        {
            key = KEY_KP_ENTER;
        }
        if (s == "KP_1")
        {
            key = KEY_KP_1;
        }
        if (s == "KP_2")
        {
            key = KEY_KP_2;
        }
        if (s == "KP_3")
        {
            key = KEY_KP_3;
        }
        if (s == "KP_4")
        {
            key = KEY_KP_4;
        }
        if (s == "KP_5")
        {
            key = KEY_KP_5;
        }
        if (s == "KP_6")
        {
            key = KEY_KP_6;
        }
        if (s == "KP_7")
        {
            key = KEY_KP_7;
        }
        if (s == "KP_8")
        {
            key = KEY_KP_8;
        }
        if (s == "KP_9")
        {
            key = KEY_KP_9;
        }
        if (s == "KP_0")
        {
            key = KEY_KP_0;
        }
        if (s == "KP_PERIOD")
        {
            key = KEY_KP_PERIOD;
        }
        if (s == "NONUSBACKSLASH")
        {
            key = KEY_NONUSBACKSLASH;
        }
        if (s == "APPLICATION")
        {
            key = KEY_APPLICATION;
        }
        if (s == "POWER")
        {
            key = KEY_POWER;
        }
        if (s == "KP_EQUALS")
        {
            key = KEY_KP_EQUALS;
        }
        if (s == "F13")
        {
            key = KEY_F13;
        }
        if (s == "F14")
        {
            key = KEY_F14;
        }
        if (s == "F15")
        {
            key = KEY_F15;
        }
        if (s == "F16")
        {
            key = KEY_F16;
        }
        if (s == "F17")
        {
            key = KEY_F17;
        }
        if (s == "F18")
        {
            key = KEY_F18;
        }
        if (s == "F19")
        {
            key = KEY_F19;
        }
        if (s == "F20")
        {
            key = KEY_F20;
        }
        if (s == "F21")
        {
            key = KEY_F21;
        }
        if (s == "F22")
        {
            key = KEY_F22;
        }
        if (s == "F23")
        {
            key = KEY_F23;
        }
        if (s == "F24")
        {
            key = KEY_F24;
        }
        if (s == "EXECUTE")
        {
            key = KEY_EXECUTE;
        }
        if (s == "HELP")
        {
            key = KEY_HELP;
        }
        if (s == "MENU")
        {
            key = KEY_MENU;
        }
        if (s == "SELECT")
        {
            key = KEY_SELECT;
        }
        if (s == "STOP")
        {
            key = KEY_STOP;
        }
        if (s == "AGAIN")
        {
            key = KEY_AGAIN;
        }
        if (s == "UNDO")
        {
            key = KEY_UNDO;
        }
        if (s == "CUT")
        {
            key = KEY_CUT;
        }
        if (s == "COPY")
        {
            key = KEY_COPY;
        }
        if (s == "PASTE")
        {
            key = KEY_PASTE;
        }
        if (s == "FIND")
        {
            key = KEY_FIND;
        }
        if (s == "MUTE")
        {
            key = KEY_MUTE;
        }
        if (s == "VOLUMEUP")
        {
            key = KEY_VOLUMEUP;
        }
        if (s == "VOLUMEDOWN")
        {
            key = KEY_VOLUMEDOWN;
        }
        if (s == "KP_COMMA")
        {
            key = KEY_KP_COMMA;
        }
        if (s == "KP_EQUALSAS400")
        {
            key = KEY_KP_EQUALSAS400;
        }
        if (s == "INTERNATIONAL1")
        {
            key = KEY_INTERNATIONAL1;
        }
        if (s == "INTERNATIONAL2")
        {
            key = KEY_INTERNATIONAL2;
        }
        if (s == "INTERNATIONAL3")
        {
            key = KEY_INTERNATIONAL3;
        }
        if (s == "INTERNATIONAL4")
        {
            key = KEY_INTERNATIONAL4;
        }
        if (s == "INTERNATIONAL5")
        {
            key = KEY_INTERNATIONAL5;
        }
        if (s == "INTERNATIONAL6")
        {
            key = KEY_INTERNATIONAL6;
        }
        if (s == "INTERNATIONAL7")
        {
            key = KEY_INTERNATIONAL7;
        }
        if (s == "INTERNATIONAL8")
        {
            key = KEY_INTERNATIONAL8;
        }
        if (s == "INTERNATIONAL9")
        {
            key = KEY_INTERNATIONAL9;
        }
        if (s == "LANG1")
        {
            key = KEY_LANG1;
        }
        if (s == "LANG2")
        {
            key = KEY_LANG2;
        }
        if (s == "LANG3")
        {
            key = KEY_LANG3;
        }
        if (s == "LANG4")
        {
            key = KEY_LANG4;
        }
        if (s == "LANG5")
        {
            key = KEY_LANG5;
        }
        if (s == "LANG6")
        {
            key = KEY_LANG6;
        }
        if (s == "LANG7")
        {
            key = KEY_LANG7;
        }
        if (s == "LANG8")
        {
            key = KEY_LANG8;
        }
        if (s == "LANG9")
        {
            key = KEY_LANG9;
        }
        if (s == "ALTERASE")
        {
            key = KEY_ALTERASE;
        }
        if (s == "SYSREQ")
        {
            key = KEY_SYSREQ;
        }
        if (s == "CANCEL")
        {
            key = KEY_CANCEL;
        }
        if (s == "CLEAR")
        {
            key = KEY_CLEAR;
        }
        if (s == "PRIOR")
        {
            key = KEY_PRIOR;
        }
        if (s == "RETURN2")
        {
            key = KEY_RETURN2;
        }
        if (s == "SEPARATOR")
        {
            key = KEY_SEPARATOR;
        }
        if (s == "OUT")
        {
            key = KEY_OUT;
        }
        if (s == "OPER")
        {
            key = KEY_OPER;
        }
        if (s == "CLEARAGAIN")
        {
            key = KEY_CLEARAGAIN;
        }
        if (s == "CRSEL")
        {
            key = KEY_CRSEL;
        }
        if (s == "EXSEL")
        {
            key = KEY_EXSEL;
        }
        if (s == "KP_00")
        {
            key = KEY_KP_00;
        }
        if (s == "KP_000")
        {
            key = KEY_KP_000;
        }
        if (s == "THOUSANDSSEPARATOR")
        {
            key = KEY_THOUSANDSSEPARATOR;
        }
        if (s == "DECIMALSEPARATOR")
        {
            key = KEY_DECIMALSEPARATOR;
        }
        if (s == "CURRENCYUNIT")
        {
            key = KEY_CURRENCYUNIT;
        }
        if (s == "CURRENCYSUBUNIT")
        {
            key = KEY_CURRENCYSUBUNIT;
        }
        if (s == "KP_LEFTPAREN")
        {
            key = KEY_KP_LEFTPAREN;
        }
        if (s == "KP_RIGHTPAREN")
        {
            key = KEY_KP_RIGHTPAREN;
        }
        if (s == "KP_LEFTBRACE")
        {
            key = KEY_KP_LEFTBRACE;
        }
        if (s == "KP_RIGHTBRACE")
        {
            key = KEY_KP_RIGHTBRACE;
        }
        if (s == "KP_TAB")
        {
            key = KEY_KP_TAB;
        }
        if (s == "KP_BACKSPACE")
        {
            key = KEY_KP_BACKSPACE;
        }
        if (s == "KP_A")
        {
            key = KEY_KP_A;
        }
        if (s == "KP_B")
        {
            key = KEY_KP_B;
        }
        if (s == "KP_C")
        {
            key = KEY_KP_C;
        }
        if (s == "KP_D")
        {
            key = KEY_KP_D;
        }
        if (s == "KP_E")
        {
            key = KEY_KP_E;
        }
        if (s == "KP_F")
        {
            key = KEY_KP_F;
        }
        if (s == "KP_XOR")
        {
            key = KEY_KP_XOR;
        }
        if (s == "KP_POWER")
        {
            key = KEY_KP_POWER;
        }
        if (s == "KP_PERCENT")
        {
            key = KEY_KP_PERCENT;
        }
        if (s == "KP_LESS")
        {
            key = KEY_KP_LESS;
        }
        if (s == "KP_GREATER")
        {
            key = KEY_KP_GREATER;
        }
        if (s == "KP_AMPERSAND")
        {
            key = KEY_KP_AMPERSAND;
        }
        if (s == "KP_DBLAMPERSAND")
        {
            key = KEY_KP_DBLAMPERSAND;
        }
        if (s == "KP_VERTICALBAR")
        {
            key = KEY_KP_VERTICALBAR;
        }
        if (s == "KP_DBLVERTICALBAR")
        {
            key = KEY_KP_DBLVERTICALBAR;
        }
        if (s == "KP_COLON")
        {
            key = KEY_KP_COLON;
        }
        if (s == "KP_HASH")
        {
            key = KEY_KP_HASH;
        }
        if (s == "KP_SPACE")
        {
            key = KEY_KP_SPACE;
        }
        if (s == "KP_AT")
        {
            key = KEY_KP_AT;
        }
        if (s == "KP_EXCLAM")
        {
            key = KEY_KP_EXCLAM;
        }
        if (s == "KP_MEMSTORE")
        {
            key = KEY_KP_MEMSTORE;
        }
        if (s == "KP_MEMRECALL")
        {
            key = KEY_KP_MEMRECALL;
        }
        if (s == "KP_MEMCLEAR")
        {
            key = KEY_KP_MEMCLEAR;
        }
        if (s == "KP_MEMADD")
        {
            key = KEY_KP_MEMADD;
        }
        if (s == "KP_MEMSUBTRACT")
        {
            key = KEY_KP_MEMSUBTRACT;
        }
        if (s == "KP_MEMMULTIPLY")
        {
            key = KEY_KP_MEMMULTIPLY;
        }
        if (s == "KP_MEMDIVIDE")
        {
            key = KEY_KP_MEMDIVIDE;
        }
        if (s == "KP_PLUSMINUS")
        {
            key = KEY_KP_PLUSMINUS;
        }
        if (s == "KP_CLEAR")
        {
            key = KEY_KP_CLEAR;
        }
        if (s == "KP_CLEARENTRY")
        {
            key = KEY_KP_CLEARENTRY;
        }
        if (s == "KP_BINARY")
        {
            key = KEY_KP_BINARY;
        }
        if (s == "KP_OCTAL")
        {
            key = KEY_KP_OCTAL;
        }
        if (s == "KP_DECIMAL")
        {
            key = KEY_KP_DECIMAL;
        }
        if (s == "KP_HEXADECIMAL")
        {
            key = KEY_KP_HEXADECIMAL;
        }
        if (s == "LCTRL")
        {
            key = KEY_LCTRL;
        }
        if (s == "LSHIFT")
        {
            key = KEY_LSHIFT;
        }
        if (s == "LALT")
        {
            key = KEY_LALT;
        }
        if (s == "LGUI")
        {
            key = KEY_LGUI;
        }
        if (s == "RCTRL")
        {
            key = KEY_RCTRL;
        }
        if (s == "RSHIFT")
        {
            key = KEY_RSHIFT;
        }
        if (s == "RALT")
        {
            key = KEY_RALT;
        }
        if (s == "RGUI")
        {
            key = KEY_RGUI;
        }
        if (s == "MODE")
        {
            key = KEY_MODE;
        }
        if (s == "AUDIONEXT")
        {
            key = KEY_AUDIONEXT;
        }
        if (s == "AUDIOPREV")
        {
            key = KEY_AUDIOPREV;
        }
        if (s == "AUDIOSTOP")
        {
            key = KEY_AUDIOSTOP;
        }
        if (s == "AUDIOPLAY")
        {
            key = KEY_AUDIOPLAY;
        }
        if (s == "AUDIOMUTE")
        {
            key = KEY_AUDIOMUTE;
        }
        if (s == "MEDIASELECT")
        {
            key = KEY_MEDIASELECT;
        }
        if (s == "WWW")
        {
            key = KEY_WWW;
        }
        if (s == "MAIL")
        {
            key = KEY_MAIL;
        }
        if (s == "CALCULATOR")
        {
            key = KEY_CALCULATOR;
        }
        if (s == "COMPUTER")
        {
            key = KEY_COMPUTER;
        }
        if (s == "AC_SEARCH")
        {
            key = KEY_AC_SEARCH;
        }
        if (s == "AC_HOME")
        {
            key = KEY_AC_HOME;
        }
        if (s == "AC_BACK")
        {
            key = KEY_AC_BACK;
        }
        if (s == "AC_FORWARD")
        {
            key = KEY_AC_FORWARD;
        }
        if (s == "AC_STOP")
        {
            key = KEY_AC_STOP;
        }
        if (s == "AC_REFRESH")
        {
            key = KEY_AC_REFRESH;
        }
        if (s == "AC_BOOKMARKS")
        {
            key = KEY_AC_BOOKMARKS;
        }
        if (s == "BRIGHTNESSDOWN")
        {
            key = KEY_BRIGHTNESSDOWN;
        }
        if (s == "BRIGHTNESSUP")
        {
            key = KEY_BRIGHTNESSUP;
        }
        if (s == "DISPLAYSWITCH")
        {
            key = KEY_DISPLAYSWITCH;
        }
        if (s == "KBDILLUMTOGGLE")
        {
            key = KEY_KBDILLUMTOGGLE;
        }
        if (s == "KBDILLUMDOWN")
        {
            key = KEY_KBDILLUMDOWN;
        }
        if (s == "KBDILLUMUP")
        {
            key = KEY_KBDILLUMUP;
        }
        if (s == "EJECT")
        {
            key = KEY_EJECT;
        }
        if (s == "SLEEP")
        {
            key = KEY_SLEEP;
        }
        if (s == "APP1")
        {
            key = KEY_APP1;
        }
        if (s == "APP2")
        {
            key = KEY_APP2;
        }
        
        return is;
    }
}