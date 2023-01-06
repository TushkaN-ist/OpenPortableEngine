
#include <Platform/PlatformIncludes.h>
#include <UserMain.h>

namespace UserBehaviour{
	int argc;
	char** argv;
}

#if defined( _PLATFORM_WINDOWS )
#include <stdio.h>

extern HINSTANCE inst;


extern "C"
{
#ifndef _WINFRAME_
int main(int argc, char **argv)
{
#else
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE prev, LPSTR cmd_line, int show)
{
	int argc;
	char** argv;
	inst=hinst;
	{
	LPWSTR* lpArgv = CommandLineToArgvW( GetCommandLineW(), &argc );
	argv = (char**)malloc( argc*sizeof(char*) );
	int size, i = 0;
	for( ; i < argc; ++i )
	{
	size = wcslen( lpArgv[i] ) + 1;
	argv[i] = (char*)malloc( size );
	wcstombs( argv[i], lpArgv[i], size );
	}
	LocalFree( lpArgv );
	}
#endif
	printf("Initialized %s\n",_APP_NAME);
	UserBehaviour::UserMain(argc,argv);
	return 0;
}
}
#elif defined( _PLATFORM_LINUX )

int main(int argc, char * argv[])
{
	UserBehaviour::UserMain(argc,argv);
	return 0;
}

#elif defined( _PLATFORM_PSP )

PSP_MODULE_INFO(_APP_NAME, 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER|THREAD_ATTR_VFPU);

int main(int argc, char * argv[])
{
    pspDebugScreenInit();
    pspDebugScreenClear();
	UserBehaviour::UserMain(argc,argv);
	return 0;
}

#endif