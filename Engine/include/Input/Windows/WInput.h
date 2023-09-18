#pragma once
#include <Input/Input.h>
#include <stdint.h>

class WInput : public Input
{
public:
	WInput();
	~WInput() override;
	
	uint8_t BitUnpack(uint8_t keycode);
	
	bool Down(KEYCODE::keycode_t keycode) override;
	bool Press(KEYCODE::keycode_t keycode) override;
	bool Up(KEYCODE::keycode_t keycode) override;
	void MousePos(unsigned short &x,unsigned short &y) override;
	void Update();
	void Reset();
	int KeyL(uint8_t keycode);
	void SetKey(uint8_t keycode);
	void PressKey(uint8_t keycode);
	void ReleaseKey(uint8_t keycode);
	void UpdateMousePos(uint16_t x,uint16_t y);
	void UpdateMouse();
	void SetDelta(short x,short y);
	void MouseDelta(short& x,short& y) override;
private:
	uint16_t mx,my,fmx,fmy;
	uint16_t dx,dy;
	uint32_t keys[16];
};
