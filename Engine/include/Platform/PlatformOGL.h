#pragma once

/*
	Platform identification
*/
#include "PlatformDefined.h"

#if defined( _PLATFORM_WINDOWS )
	#include <GL/gl.h>
#elif defined( _PLATFORM_LINUX )
	#include <GL/gl.h>
	#include <GL/glx.h>
#elif defined( _PLATFORM_OSX )
	#include <GL/gl.h>
	#include <GL/glx.h>
#elif defined( _PLATFORM_PSP )
	#include <GL/gl.h>
	//#include <GL/glext.h>
	#include <GLES/egl.h>
	void glActiveTexture (unsigned int texture);
//#define printf	pspDebugScreenPrintf
#elif defined( _PLATFORM_PSP2 )
	#include <GL/vitaGL.h>
	#include <GL/egl.h>
#elif defined( _PLATFORM_N3DS )
	#include <GL/gl3ds.h>
#elif defined( _PLATFORM_WII )
	#include <GL/gl.h>
#endif

/*
	Types
*/

/*namespace GL
{
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned long ulong;

//#ifndef  _PLATFORM_PSP 
//#endif
}*/