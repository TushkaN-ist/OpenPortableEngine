#include <Platform/PlatformApp.h>

#ifdef _PLATFORM_WINDOWS
//#include <synchapi.h>
#include <unistd.h>
#elif _PLATFORM_LINUX 
#include <unistd.h>
#elif _PLATFORM_PSP
#include <pspsdk.h>
#endif

#ifdef _PLATFORM_WINDOWS

    void APP::_Sleep(unsigned int t){
		  usleep(t);
    }
#elif _PLATFORM_LINUX
    void APP::_Sleep(float t){
		  usleep(t * 1000000);   // usleep takes sleep time in us (1 millionth of a second)
    }
    void APP::_Sleep(long t){
		  usleep(t);   // usleep takes sleep time in us (1 millionth of a second)
    }
    void APP::_Sleep(int t){
		  usleep(t * 1000);   // usleep takes sleep time in us (1 millionth of a second)
    }
#elif _PLATFORM_PSP
    void APP::_Sleep(float t){
		  sceKernelDelayThread( t * 1000000 );   // usleep takes sleep time in us (1 millionth of a second)
    }
    void APP::_Sleep(long t){
		  sceKernelDelayThread(t);   // usleep takes sleep time in us (1 millionth of a second)
    }
    void APP::_Sleep(int t){
		  sceKernelDelayThread(t * 1000);   // usleep takes sleep time in us (1 millionth of a second)
    }
#endif