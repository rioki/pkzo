// pkzo
// Copyright (c) 2014-2019 Sean Farrell
// See READNE.md for licensing details.

#ifndef _PKZO_DEFINES_H_
#define _PKZO_DEFINES_H_

/**
 * Current Version of pkzo
 **/
#define PZKO_VERSION "0.1.0"

#ifdef _WIN32
#define PKZO_EXPORT __declspec(dllexport)
#else
#define PKZO_EXPORT
#endif

// disable silly warnings
#ifndef _MSVC
#pragma warning(disable: 4251)
#pragma warning(disable: 4275)
#endif

#define GLM_FORCE_SWIZZLE

#endif
