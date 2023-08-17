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

#pragma once
#include "config.h"

#include <iosfwd>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_events.h>
#include <rsig/rsig.h>

#include "utils.h"

#ifdef DELETE
#undef DELETE
#endif

#ifdef OUT
#undef OUT
#endif

namespace pkzo
{
    class EventRouter;

    //! Key
    enum class Key
    {
        UNKNOWN            = SDL_SCANCODE_UNKNOWN,
        A                  = SDL_SCANCODE_A,
        B                  = SDL_SCANCODE_B,
        C                  = SDL_SCANCODE_C,
        D                  = SDL_SCANCODE_D,
        E                  = SDL_SCANCODE_E,
        F                  = SDL_SCANCODE_F,
        G                  = SDL_SCANCODE_G,
        H                  = SDL_SCANCODE_H,
        I                  = SDL_SCANCODE_I,
        J                  = SDL_SCANCODE_J,
        K                  = SDL_SCANCODE_K,
        L                  = SDL_SCANCODE_L,
        M                  = SDL_SCANCODE_M,
        N                  = SDL_SCANCODE_N,
        O                  = SDL_SCANCODE_O,
        P                  = SDL_SCANCODE_P,
        Q                  = SDL_SCANCODE_Q,
        R                  = SDL_SCANCODE_R,
        S                  = SDL_SCANCODE_S,
        T                  = SDL_SCANCODE_T,
        U                  = SDL_SCANCODE_U,
        V                  = SDL_SCANCODE_V,
        W                  = SDL_SCANCODE_W,
        X                  = SDL_SCANCODE_X,
        Y                  = SDL_SCANCODE_Y,
        Z                  = SDL_SCANCODE_Z,
        ONE                = SDL_SCANCODE_1,
        TWO                = SDL_SCANCODE_2,
        THREE              = SDL_SCANCODE_3,
        FOUR               = SDL_SCANCODE_4,
        FIVE               = SDL_SCANCODE_5,
        SIX                = SDL_SCANCODE_6,
        SEVEN              = SDL_SCANCODE_7,
        EIGHT              = SDL_SCANCODE_8,
        NINE               = SDL_SCANCODE_9,
        ZERO               = SDL_SCANCODE_0,
        RETURN             = SDL_SCANCODE_RETURN,
        ESCAPE             = SDL_SCANCODE_ESCAPE,
        BACKSPACE          = SDL_SCANCODE_BACKSPACE,
        TAB                = SDL_SCANCODE_TAB,
        SPACE              = SDL_SCANCODE_SPACE,
        MINUS              = SDL_SCANCODE_MINUS,
        EQUALS             = SDL_SCANCODE_EQUALS,
        LEFTBRACKET        = SDL_SCANCODE_LEFTBRACKET,
        RIGHTBRACKET       = SDL_SCANCODE_RIGHTBRACKET,
        BACKSLASH          = SDL_SCANCODE_BACKSLASH,
        NONUSHASH          = SDL_SCANCODE_NONUSHASH,
        SEMICOLON          = SDL_SCANCODE_SEMICOLON,
        APOSTROPHE         = SDL_SCANCODE_APOSTROPHE,
        GRAVE              = SDL_SCANCODE_GRAVE,
        PERIOD             = SDL_SCANCODE_PERIOD,
        SLASH              = SDL_SCANCODE_SLASH,
        CAPSLOCK           = SDL_SCANCODE_CAPSLOCK,
        F1                 = SDL_SCANCODE_F1,
        F2                 = SDL_SCANCODE_F2,
        F3                 = SDL_SCANCODE_F3,
        F4                 = SDL_SCANCODE_F4,
        F5                 = SDL_SCANCODE_F5,
        F6                 = SDL_SCANCODE_F6,
        F7                 = SDL_SCANCODE_F7,
        F8                 = SDL_SCANCODE_F8,
        F9                 = SDL_SCANCODE_F9,
        F10                = SDL_SCANCODE_F10,
        F11                = SDL_SCANCODE_F11,
        F12                = SDL_SCANCODE_F12,
        PRINTSCREEN        = SDL_SCANCODE_PRINTSCREEN,
        SCROLLLOCK         = SDL_SCANCODE_SCROLLLOCK,
        PAUSE              = SDL_SCANCODE_PAUSE,
        INSERT             = SDL_SCANCODE_INSERT,
        HOME               = SDL_SCANCODE_HOME,
        PAGEUP             = SDL_SCANCODE_PAGEUP,
        DELETE             = SDL_SCANCODE_DELETE,
        END                = SDL_SCANCODE_END,
        PAGEDOWN           = SDL_SCANCODE_PAGEDOWN,
        RIGHT              = SDL_SCANCODE_RIGHT,
        LEFT               = SDL_SCANCODE_LEFT,
        DOWN               = SDL_SCANCODE_DOWN,
        UP                 = SDL_SCANCODE_UP,
        NUMLOCKCLEAR       = SDL_SCANCODE_NUMLOCKCLEAR,
        KP_DIVIDE          = SDL_SCANCODE_KP_DIVIDE,
        KP_MULTIPLY        = SDL_SCANCODE_KP_MULTIPLY,
        KP_MINUS           = SDL_SCANCODE_KP_MINUS,
        KP_PLUS            = SDL_SCANCODE_KP_PLUS,
        KP_ENTER           = SDL_SCANCODE_KP_ENTER,
        KP_1               = SDL_SCANCODE_KP_1,
        KP_2               = SDL_SCANCODE_KP_2,
        KP_3               = SDL_SCANCODE_KP_3,
        KP_4               = SDL_SCANCODE_KP_4,
        KP_5               = SDL_SCANCODE_KP_5,
        KP_6               = SDL_SCANCODE_KP_6,
        KP_7               = SDL_SCANCODE_KP_7,
        KP_8               = SDL_SCANCODE_KP_8,
        KP_9               = SDL_SCANCODE_KP_9,
        KP_0               = SDL_SCANCODE_KP_0,
        KPPERIOD           = SDL_SCANCODE_KP_PERIOD,
        NONUSBACKSLASH     = SDL_SCANCODE_NONUSBACKSLASH,
        APPLICATION        = SDL_SCANCODE_APPLICATION,
        POWER              = SDL_SCANCODE_POWER,
        KP_EQUALS          = SDL_SCANCODE_KP_EQUALS,
        F13                = SDL_SCANCODE_F13,
        F14                = SDL_SCANCODE_F14,
        F15                = SDL_SCANCODE_F15,
        F16                = SDL_SCANCODE_F16,
        F17                = SDL_SCANCODE_F17,
        F18                = SDL_SCANCODE_F18,
        F19                = SDL_SCANCODE_F19,
        F20                = SDL_SCANCODE_F20,
        F21                = SDL_SCANCODE_F21,
        F22                = SDL_SCANCODE_F22,
        F23                = SDL_SCANCODE_F23,
        F24                = SDL_SCANCODE_F24,
        EXECUTE            = SDL_SCANCODE_EXECUTE,
        HELP               = SDL_SCANCODE_HELP,
        MENU               = SDL_SCANCODE_MENU,
        SELECT             = SDL_SCANCODE_SELECT,
        STOP               = SDL_SCANCODE_STOP,
        AGAIN              = SDL_SCANCODE_AGAIN,
        UNDO               = SDL_SCANCODE_UNDO,
        CUT                = SDL_SCANCODE_CUT,
        COPY               = SDL_SCANCODE_COPY,
        PASTE              = SDL_SCANCODE_PASTE,
        FIND               = SDL_SCANCODE_FIND,
        MUTE               = SDL_SCANCODE_MUTE,
        VOLUMEUP           = SDL_SCANCODE_VOLUMEUP,
        VOLUMEDOWN         = SDL_SCANCODE_VOLUMEDOWN,
        KP_COMMA           = SDL_SCANCODE_KP_COMMA,
        KP_EQUALSAS400     = SDL_SCANCODE_KP_EQUALSAS400,
        INTERNATIONAL1     = SDL_SCANCODE_INTERNATIONAL1,
        INTERNATIONAL2     = SDL_SCANCODE_INTERNATIONAL2,
        INTERNATIONAL3     = SDL_SCANCODE_INTERNATIONAL3,
        INTERNATIONAL4     = SDL_SCANCODE_INTERNATIONAL4,
        INTERNATIONAL5     = SDL_SCANCODE_INTERNATIONAL5,
        INTERNATIONAL6     = SDL_SCANCODE_INTERNATIONAL6,
        INTERNATIONAL7     = SDL_SCANCODE_INTERNATIONAL7,
        INTERNATIONAL8     = SDL_SCANCODE_INTERNATIONAL8,
        INTERNATIONAL9     = SDL_SCANCODE_INTERNATIONAL9,
        LANG1              = SDL_SCANCODE_LANG1,
        LANG2              = SDL_SCANCODE_LANG2,
        LANG3              = SDL_SCANCODE_LANG3,
        LANG4              = SDL_SCANCODE_LANG4,
        LANG5              = SDL_SCANCODE_LANG5,
        LANG6              = SDL_SCANCODE_LANG6,
        LANG7              = SDL_SCANCODE_LANG7,
        LANG8              = SDL_SCANCODE_LANG8,
        LANG9              = SDL_SCANCODE_LANG9,
        ALTERASE           = SDL_SCANCODE_ALTERASE,
        SYSREQ             = SDL_SCANCODE_SYSREQ,
        CANCEL             = SDL_SCANCODE_CANCEL,
        CLEAR              = SDL_SCANCODE_CLEAR,
        PRIOR              = SDL_SCANCODE_PRIOR,
        RETURN2            = SDL_SCANCODE_RETURN2,
        SEPARATOR          = SDL_SCANCODE_SEPARATOR,
        OUT                = SDL_SCANCODE_OUT,
        OPER               = SDL_SCANCODE_OPER,
        CLEARAGAIN         = SDL_SCANCODE_CLEARAGAIN,
        CRSEL              = SDL_SCANCODE_CRSEL,
        EXSEL              = SDL_SCANCODE_EXSEL,
        KP_00              = SDL_SCANCODE_KP_00,
        KP_000             = SDL_SCANCODE_KP_000,
        THOUSANDSSEPARATOR = SDL_SCANCODE_THOUSANDSSEPARATOR,
        DECIMALSEPARATOR   = SDL_SCANCODE_DECIMALSEPARATOR,
        CURRENCYUNIT       = SDL_SCANCODE_CURRENCYUNIT,
        CURRENCYSUBUNIT    = SDL_SCANCODE_CURRENCYSUBUNIT,
        KP_LEFTPAREN       = SDL_SCANCODE_KP_LEFTPAREN,
        KP_RIGHTPAREN      = SDL_SCANCODE_KP_RIGHTPAREN,
        KP_LEFTBRACE       = SDL_SCANCODE_KP_LEFTBRACE,
        KP_RIGHTBRACE      = SDL_SCANCODE_KP_RIGHTBRACE,
        KP_TAB             = SDL_SCANCODE_KP_TAB,
        KP_BACKSPACE       = SDL_SCANCODE_KP_BACKSPACE,
        KP_A               = SDL_SCANCODE_KP_A,
        KP_B               = SDL_SCANCODE_KP_B,
        KP_C               = SDL_SCANCODE_KP_C,
        KP_D               = SDL_SCANCODE_KP_D,
        KP_E               = SDL_SCANCODE_KP_E,
        KP_F               = SDL_SCANCODE_KP_F,
        KP_XOR             = SDL_SCANCODE_KP_XOR,
        KP_POWER           = SDL_SCANCODE_KP_POWER,
        KP_PERCENT         = SDL_SCANCODE_KP_PERCENT,
        KP_LESS            = SDL_SCANCODE_KP_LESS,
        KP_GREATER         = SDL_SCANCODE_KP_GREATER,
        KP_AMPERSAND       = SDL_SCANCODE_KP_AMPERSAND,
        KP_DBLAMPERSAND    = SDL_SCANCODE_KP_DBLAMPERSAND,
        KP_VERTICALBAR     = SDL_SCANCODE_KP_VERTICALBAR,
        KP_DBLVERTICALBAR  = SDL_SCANCODE_KP_DBLVERTICALBAR,
        KP_COLON           = SDL_SCANCODE_KP_COLON,
        KP_HASH            = SDL_SCANCODE_KP_HASH,
        KP_SPACE           = SDL_SCANCODE_KP_SPACE,
        KP_AT              = SDL_SCANCODE_KP_AT,
        KP_EXCLAM          = SDL_SCANCODE_KP_EXCLAM,
        KP_MEMSTORE        = SDL_SCANCODE_KP_MEMSTORE,
        KP_MEMRECALL       = SDL_SCANCODE_KP_MEMRECALL,
        KP_MEMCLEAR        = SDL_SCANCODE_KP_MEMCLEAR,
        KP_MEMADD          = SDL_SCANCODE_KP_MEMADD,
        KP_MEMSUBTRACT     = SDL_SCANCODE_KP_MEMSUBTRACT,
        KP_MEMMULTIPLY     = SDL_SCANCODE_KP_MEMMULTIPLY,
        KP_MEMDIVIDE       = SDL_SCANCODE_KP_MEMDIVIDE,
        KP_PLUSMINUS       = SDL_SCANCODE_KP_PLUSMINUS,
        KP_CLEAR           = SDL_SCANCODE_KP_CLEAR,
        KP_CLEARENTRY      = SDL_SCANCODE_KP_CLEARENTRY,
        KP_BINARY          = SDL_SCANCODE_KP_BINARY,
        KP_OCTAL           = SDL_SCANCODE_KP_OCTAL,
        KP_DECIMAL         = SDL_SCANCODE_KP_DECIMAL,
        KP_HEXADECIMAL     = SDL_SCANCODE_KP_HEXADECIMAL,
        LCTRL              = SDL_SCANCODE_LCTRL,
        LSHIFT             = SDL_SCANCODE_LSHIFT,
        LALT               = SDL_SCANCODE_LALT,
        LGUI               = SDL_SCANCODE_LGUI,
        RCTRL              = SDL_SCANCODE_RCTRL,
        RSHIFT             = SDL_SCANCODE_RSHIFT,
        RALT               = SDL_SCANCODE_RALT,
        RGUI               = SDL_SCANCODE_RGUI,
        MODE               = SDL_SCANCODE_MODE,
        AUDIONEXT          = SDL_SCANCODE_AUDIONEXT,
        AUDIOPREV          = SDL_SCANCODE_AUDIOPREV,
        AUDIOSTOP          = SDL_SCANCODE_AUDIOSTOP,
        AUDIOPLAY          = SDL_SCANCODE_AUDIOPLAY,
        AUDIOMUTE          = SDL_SCANCODE_AUDIOMUTE,
        MEDIASELECT        = SDL_SCANCODE_MEDIASELECT,
        WWW                = SDL_SCANCODE_WWW,
        MAIL               = SDL_SCANCODE_MAIL,
        CALCULATOR         = SDL_SCANCODE_CALCULATOR,
        COMPUTER           = SDL_SCANCODE_COMPUTER,
        AC_SEARCH          = SDL_SCANCODE_AC_SEARCH,
        AC_HOME            = SDL_SCANCODE_AC_HOME,
        AC_BACK            = SDL_SCANCODE_AC_BACK,
        AC_FORWARD         = SDL_SCANCODE_AC_FORWARD,
        AC_STOP            = SDL_SCANCODE_AC_STOP,
        AC_REFRESH         = SDL_SCANCODE_AC_REFRESH,
        AC_BOOKMARKS       = SDL_SCANCODE_AC_BOOKMARKS,
        BRIGHTNESSDOWN     = SDL_SCANCODE_BRIGHTNESSDOWN,
        BRIGHTNESSUP       = SDL_SCANCODE_BRIGHTNESSUP,
        DISPLAYSWITCH      = SDL_SCANCODE_DISPLAYSWITCH,
        KBDILLUMTOGGLE     = SDL_SCANCODE_KBDILLUMTOGGLE,
        KBDILLUMDOWN       = SDL_SCANCODE_KBDILLUMDOWN,
        KBDILLUMUP         = SDL_SCANCODE_KBDILLUMUP,
        EJECT              = SDL_SCANCODE_EJECT,
        SLEEP              = SDL_SCANCODE_SLEEP,
        APP1               = SDL_SCANCODE_APP1,
        APP2               = SDL_SCANCODE_APP2
    };


    //! Key Modifier
    enum class KeyMod
    {
        NONE   = KMOD_NONE,
        LSHIFT = KMOD_LSHIFT,
        RSHIFT = KMOD_RSHIFT,
        LCTRL  = KMOD_LCTRL,
        RCTRL  = KMOD_RCTRL,
        LALT   = KMOD_LALT,
        RALT   = KMOD_RALT,
        LGUI   = KMOD_LGUI,
        RGUI   = KMOD_RGUI,
        NUM    = KMOD_NUM,
        CAPS   = KMOD_CAPS,
        MODE   = KMOD_MODE,
        SCROLL = KMOD_SCROLL,

        CTRL   = KMOD_CTRL,
        SHIFT  = KMOD_SHIFT,
        ALT    = KMOD_ALT,
        GUI    = KMOD_GUI
    };
    PKZO_ENUM_OPERATORS(KeyMod);

    //! Keyboard
    class PKZO_EXPORT Keyboard
    {
    public:
        //! Create keyboard against event router.
        Keyboard(EventRouter& router);
        ~Keyboard();

        //! Check if a given key is pressed.
        bool is_pressed(Key key) const noexcept;

        //! Signal emitted when a key is pressed.
        rsig::signal<KeyMod, Key>& get_key_press_signal() noexcept;

        //! Signal emitted when a key is relased.
        rsig::signal<KeyMod, Key>& get_key_release_signal() noexcept;

        //! Signal emitted when text is generated.
        //!
        //! All key strokes that generate text (generally single letters)
        //! this signal will emit with the text as string.
        rsig::signal<std::string>& get_text_signal() noexcept;

    private:
        EventRouter&     router;
        rsig::connection router_connection;

        rsig::signal<KeyMod, Key> key_press_signal;
        rsig::signal<KeyMod, Key> key_release_signal;
        rsig::signal<std::string> text_signal;

        void handle_events(const SDL_Event& event);
    };
}
