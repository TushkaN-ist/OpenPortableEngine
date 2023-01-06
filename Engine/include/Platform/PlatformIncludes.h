#pragma once
/*
	Platform identification
*/
#include "PlatformDefined.h"

#if defined( _PLATFORM_WINDOWS )
	#include <Windows.h>
	#include <WindowsX.h>

	#ifdef _WIN64
		#define GWL_USERDATA GWLP_USERDATA
		#define GCL_HCURSOR GCLP_HCURSOR
	#endif

#elif defined( _PLATFORM_LINUX )
	#include <X11/Xlib.h>
	#include <sys/time.h>
#elif defined( _PLATFORM_OSX )

#elif defined( _PLATFORM_PSP )

	#include <pspkernel.h>
	#include <pspdisplay.h>
	#include <pspdebug.h>
	#include <psprtc.h>
	#include <pspctrl.h>
	#include <pspuser.h>

/* Define printf, just to make typing easier */
#define printf  pspDebugScreenPrintf
#endif
