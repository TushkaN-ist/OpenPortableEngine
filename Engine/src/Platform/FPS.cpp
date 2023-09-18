#include <Platform/PlatformDefined.h>
#include <Platform/PlatformApp.h>
#include <Platform/FPS.h>

#if defined(_PLATFORM_WINDOWS)
#include <windows.h>
#include <stdio.h>


class WFPS : public FPS{
	public:
	WFPS(unsigned short target);
	void Set(unsigned short fps);
	bool Update();
	private:
	LARGE_INTEGER currentTime, lastTime, secondTime, frequency;
	unsigned long _sleep;
	unsigned short _count;
};

WFPS::WFPS(unsigned short target){
	_count = 0;
	_last = 0;
	QueryPerformanceCounter(&currentTime);
	QueryPerformanceFrequency(&frequency);
	Set(target);
	lastTime = secondTime = currentTime;
}

FPS* FPS::Create(unsigned short target){
	return new WFPS(target);
}

void WFPS::Set(unsigned short fps){
	_target = fps;
	_sleep = frequency.LowPart / _target / 10 - 1000;
	//printf("%i %i\n",frequency.LowPart, _sleep);
	//_sleep = 1000000 / _target - 2000;
}

bool WFPS::Update(){
	lastTime = currentTime;
	QueryPerformanceCounter(&currentTime);

	DWORD td = (currentTime.LowPart - lastTime.LowPart) / 10;

	if (currentTime.LowPart - secondTime.LowPart > 10000000){
		secondTime = currentTime;
		_last = _count;
		_count = 0;
	}

	_delta = td / 1000000.0;

	if (_delta == 0)
		_delta = _target / 1000.0f;

	if (_delta > 1.5f)
		_delta = 1.5f;

	_deltaSmooth += (_deltaSmooth - _delta) * 0.5f;
	++_count;

	//printf("%i %i %i %i %i\n", td, _sleep,_sleep - td, GetFPSFast(), GetFPS());
	//printf("%f\n",GetDelta());
	APP::_Sleep(_sleep);
	return true;
}

#elif defined(_PLATFORM_LINUX) || defined (_PLATFORM_PSP)
#include <time.h>

class PSPFPS : public FPS{
	public:
	PSPFPS(unsigned short target);
	bool Update();
	private:
	long diff_micro(struct timespec *start, struct timespec *end);
	long diff_milli(struct timespec *start, struct timespec *end);
	timespec  currentTime,lastTime,secondTime;
	unsigned short _count;
};

PSPFPS::PSPFPS(unsigned short target){
	_count=0;
	_last=0;
	Set(target);
	clock_gettime(CLOCK_MONOTONIC, &currentTime);
	secondTime=currentTime;
}

FPS* FPS::Create(unsigned short target){
	return new PSPFPS(target);
}

long PSPFPS::diff_micro(struct timespec *start, struct timespec *end)
{
	/* us */
	return ((end->tv_sec * (1000000)) + (end->tv_nsec / 1000)) -
		((start->tv_sec * 1000000) + (start->tv_nsec / 1000));
}

long PSPFPS::diff_milli(struct timespec *start, struct timespec *end)
{
	/* ms */
	return ((end->tv_sec * 1000) + (end->tv_nsec / 1000000)) -
		((start->tv_sec * 1000) + (start->tv_nsec / 1000000));
}

bool PSPFPS::Update(){
	lastTime = currentTime;
	clock_gettime(CLOCK_MONOTONIC, &currentTime);
	long td = diff_milli(&lastTime,&currentTime);
	long _td = 1000/_target;
	if (diff_milli(&secondTime,&currentTime)>1000){
		secondTime = currentTime;
		_last=_count;
		_count=0;
	}
	_delta = td/1000.0f;
	if (_delta==0)
		_delta = _target/1000.0f;
	if (_delta>1.5f)
		_delta = 1.5f;
	_deltaSmooth += (_deltaSmooth-_delta)*0.5f;
	++_count;
	if (td<_td+_td)
		APP::_Sleep(_td-1);
	return true;
}

#endif

unsigned short FPS::GetFPS(){
	return _last;
}
unsigned short FPS::GetFPSFast(){
	return 1/_delta;
}
float FPS::GetDelta(){
	return _delta;
}
float FPS::GetDeltaSmooth(){
	return _deltaSmooth;
}