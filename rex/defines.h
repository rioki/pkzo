// rioki's C++ extentions
// Copyright 2021-2024 Sean Farrell <sean.farrell@rioki.org>
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar. See
// http://www.wtfpl.net/ for more details.

#pragma once

#ifdef _WIN32
    #ifdef REX_BUILD_DLL
        #define REX_EXPORT __declspec(dllexport)
    #else
        #define REX_EXPORT __declspec(dllimport)
    #endif
#else
    #define REX_EXPORT
#endif

#ifdef _MSC_VER
    //disable silly warnings
    #pragma warning(disable: 4273) // 'object': inconsistent dll linkage
    #pragma warning(disable: 4251) // 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
#endif