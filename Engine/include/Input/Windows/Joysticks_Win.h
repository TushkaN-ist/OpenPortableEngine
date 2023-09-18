#pragma once

#include <Platform/PlatformDefined.h>

#include <Platform/PlatformIncludes.h>
#include <Input/Input.h>
#include <string>
#include <vector>
#include <map>

#include <libenjoy.h>
#include <libenjoy_win32.h>

class WJoystick : public Joystick{
	private:
	uint32_t keys[1];
	libenjoy_joy_info *_info=NULL;
	libenjoy_joystick *_joy=NULL;
	uint8_t BitCheck(uint8_t keycode);

	public:
	WJoystick(int id);
	WJoystick(libenjoy_joy_info* info);
	static void Init();
	static void Free();
	static void Update();
	static Joystick* GetJoy(int id);
	void UpdateStates();
	void UpdateBTNS();
	void Reset();
	void PressKey(uint8_t keycode);
	void ReleaseKey(uint8_t keycode);
	void SetInfo(int id);
	void SetInfo(libenjoy_joy_info* info);
	
	~WJoystick() override ;
	const char* Name() override ;
	bool Down(unsigned char keycode) override ;
	bool Press(unsigned char keycode) override ;
	bool Up(unsigned char keycode) override ;
	float Axis01(unsigned char axis, float deadzone=0.05f) override ;
	float Axis(unsigned char axis, float deadzone=0.05f) override ;
	short AxisRaw(unsigned char axis, short deadzone=1638) override ;
	unsigned char AxisCount() override ;
	unsigned char BtnsCount() override ;
	void Open() override ;
	bool IsOpen() override ;
	void Close() override ;
};
extern std::vector<WJoystick*> joys;
extern std::map<int,Joystick*> joysMap;
extern libenjoy_context *ctx;