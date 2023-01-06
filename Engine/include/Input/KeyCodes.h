#pragma once
#include <Platform/PlatformDefined.h>

#ifdef _PLATFORM_WINDOWS
#include "KeyCodes_WIN.h"
#elif _PLATFORM_LINUX
#include "KeyCodes_LINUX.h"
#elif _PLATFORM_PSP
#include "KeyCodes_PSP.h"
#elif _PLATFORM_PSP2
#include "KeyCodes_PSP2.h"
#endif