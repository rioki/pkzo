
#ifndef _PKZO_DEFINES_H_
#define _PKZO_DEFINES_H_

/**
 * Current Version of pkzo
 **/
#define PZKO_VERSION "0.1.0"

#ifdef _WIN32
#ifdef PKZO_BUILD
#define PKZO_EXPORT __declspec(dllexport)
#else
#define PKZO_EXPORT __declspec(dllimport)
#endif
#else
#define PKZO_EXPORT  
#endif

// disable silly warnings
#ifndef _MSVC
#pragma warning(disable: 4251)
#endif

#endif
