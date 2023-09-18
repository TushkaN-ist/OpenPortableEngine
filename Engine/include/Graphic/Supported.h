#pragma once

#include <Platform/PlatformDefined.h>

#if defined(_PLATFORM_WINDOWS)
namespace Graphics{
    enum GFXDevicesSupport{
        OpenGL = 1
    };
}
#elif defined(_PLATFORM_LINUX)
    enum GFXDevicesSupport{
        OpenGL = 1
    };
#elif defined(_PLATFORM_OSX)
    enum GFXDevicesSupport{
        OpenGL = 1
    };
elif defined(_PLATFORM_PSP)
    enum GFXDevicesSupport{
        OpenGL = 1
    };
#endif