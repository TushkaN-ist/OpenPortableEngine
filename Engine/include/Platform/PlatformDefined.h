#pragma once

extern const char* _APP_NAME;

#if defined( _WIN32 ) || defined( _WIN64 )
	#define _PLATFORM_WINDOWS
#elif defined( __linux__ )
	#define _PLATFORM_LINUX
#elif defined( __APPLE__ )
	#define _PLATFORM_OSX
#elif defined( _PSP )
	#define _PLATFORM_PSP
#endif

#define ENGINE_VERSION "0.5a"

#define DEFNAME "'PORTABLE ENGINE' " ENGINE_VERSION ""

#ifndef _PLATFORM_PSP
#ifndef GL_VERSION_TARGET
#define GL_VERSION_TARGET 30
#endif
#endif