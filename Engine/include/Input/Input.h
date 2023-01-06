#pragma once
//#include "PlatformDefined.h"
#include "KeyCodes.h"

class Joystick{
public:
	Joystick();
	virtual ~Joystick();
	virtual const char* Name();
	virtual bool Down(unsigned char btn);
	virtual bool Press(unsigned char btn);
	virtual bool Up(unsigned char btn);
	virtual float Axis01(unsigned char axis, float deadzone=0.05f);
	virtual float Axis(unsigned char axis, float deadzone=0.05f);
	virtual short AxisRaw(unsigned char axis, short deadzone=1638);
	virtual unsigned char AxisCount();
	virtual unsigned char BtnsCount();
	virtual void Open();
	virtual bool IsOpen();
	virtual void Close();
	
	static Joystick* GetJoy(int id);
	static int GetConnected();
	static void Init();
	static void Free();
};

class Input{
public:
	virtual ~Input(){};
	virtual bool Down(KEYCODE::keycode_t keycode)=0;
	virtual bool Press(KEYCODE::keycode_t keycode)=0;
	virtual bool Up(KEYCODE::keycode_t keycode)=0;
	virtual void MousePos(unsigned short &x,unsigned short &y)=0;
	virtual void MouseDelta(short &x,short &y)=0;
	inline void MouseSentesivity(unsigned short sent){mouseSentesivity=sent;}
	
protected:
	unsigned short mouseSentesivity;
};
