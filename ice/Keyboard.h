// Ice Engine
// Copyright 2022 Sean Farrell
// All rights reserved.

#pragma once
#include "config.h"

#include <functional>
#include <glm/fwd.hpp>
#include <rsig/rsig.h>

#include "utils.h"

#ifdef DELETE
#undef DELETE
#endif
#ifdef OUT
#undef OUT
#endif

union SDL_Event;

namespace ice
{
    enum class Key
    {
        UNDEFINED          = 0,
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
        PERIOD             = 55,
        SLASH              = 56,
        CAPSLOCK           = 57,
        F1                 = 58,
        F2                 = 59,
        F3                 = 60,
        F4                 = 61,
        F5                 = 62,
        F6                 = 63,
        F7                 = 64,
        F8                 = 65,
        F9                 = 66,
        F10                = 67,
        F11                = 68,
        F12                = 69,
        PRINTSCREEN        = 70,
        SCROLLLOCK         = 71,
        PAUSE              = 72,
        INSERT             = 73,
        HOME               = 74,
        PAGEUP             = 75,
        DELETE             = 76,
        END                = 77,
        PAGEDOWN           = 78,
        RIGHT              = 79,
        LEFT               = 80,
        DOWN               = 81,
        UP                 = 82,
        NUMLOCKCLEAR       = 83,
        KPDIVIDE           = 84,
        KPMULTIPLY         = 85,
        KPMINUS            = 86,
        KPPLUS             = 87,
        KPENTER            = 88,
        KP1                = 89,
        KP2                = 90,
        KP3                = 91,
        KP4                = 92,
        KP5                = 93,
        KP6                = 94,
        KP7                = 95,
        KP8                = 96,
        KP9                = 97,
        KP0                = 98,
        KPPERIOD           = 99,
        NONUSBACKSLASH     = 100,
        APPLICATION        = 101,
        POWER              = 102,
        KPEQUALS           = 103,
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
        KPCOMMA            = 133,
        KPEQUALSAS400      = 134,
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
        OUT                = 160,
        OPER               = 161,
        CLEARAGAIN         = 162,
        CRSEL              = 163,
        EXSEL              = 164,
        KP00               = 176,
        KP000              = 177,
        THOUSANDSSEPARATOR = 178,
        DECIMALSEPARATOR   = 179,
        CURRENCYUNIT       = 180,
        CURRENCYSUBUNIT    = 181,
        KPLEFTPAREN        = 182,
        KPRIGHTPAREN       = 183,
        KPLEFTBRACE        = 184,
        KPRIGHTBRACE       = 185,
        KPTAB              = 186,
        KPBACKSPACE        = 187,
        KPA                = 188,
        KPB                = 189,
        KPC                = 190,
        KPD                = 191,
        KPE                = 192,
        KPF                = 193,
        KPXOR              = 194,
        KPPOWER            = 195,
        KPPERCENT          = 196,
        KPLESS             = 197,
        KPGREATER          = 198,
        KPAMPERSAND        = 199,
        KPDBLAMPERSAND     = 200,
        KPVERTICALBAR      = 201,
        KPDBLVERTICALBAR   = 202,
        KPCOLON            = 203,
        KPHASH             = 204,
        KPSPACE            = 205,
        KPAT               = 206,
        KPEXCLAM           = 207,
        KPMEMSTORE         = 208,
        KPMEMRECALL        = 209,
        KPMEMCLEAR         = 210,
        KPMEMADD           = 211,
        KPMEMSUBTRACT      = 212,
        KPMEMMULTIPLY      = 213,
        KPMEMDIVIDE        = 214,
        KPPLUSMINUS        = 215,
        KPCLEAR            = 216,
        KPCLEARENTRY       = 217,
        KPBINARY           = 218,
        KPOCTAL            = 219,
        KPDECIMAL          = 220,
        KPHEXADECIMAL      = 221,
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
        ACSEARCH           = 268,
        ACHOME             = 269,
        ACBACK             = 270,
        ACFORWARD          = 271,
        ACSTOP             = 272,
        ACREFRESH          = 273,
        ACBOOKMARKS        = 274,
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
        NONE  = 0,
        SHIFT = ICE_BIT(1),
        CTRL  = ICE_BIT(2),
        ALT   = ICE_BIT(3),
        META  = ICE_BIT(4)
    };
    ICE_ENUM_BIT_OPERATORS(KeyMod);

    class ICE_EXPORT Keyboard
    {
    public:
        Keyboard() noexcept;
        ~Keyboard();

        bool is_pressed(Key key) const noexcept;

        rsig::signal<KeyMod, Key>& get_key_down_signal() noexcept;
        rsig::connection on_key_down(const std::function<void (KeyMod, Key)>& cb) noexcept;

        rsig::signal<KeyMod, Key>& get_key_up_signal() noexcept;
        rsig::connection on_key_up(const std::function<void (KeyMod, Key)>& cb) noexcept;

        rsig::signal<const std::string_view>& get_text_signal() noexcept;
        rsig::connection on_text(const std::function<void (const std::string_view)>& cb) noexcept;

    private:
        rsig::signal<KeyMod, Key>            key_down_signal;
        rsig::signal<KeyMod, Key>            key_up_signal;
        rsig::signal<const std::string_view> text_signal;

        void handle_event(const SDL_Event& event) const;

        Keyboard(const Keyboard&) = delete;
        Keyboard& operator = (const Keyboard&) = delete;

    friend class InputSystem;
    };
}
