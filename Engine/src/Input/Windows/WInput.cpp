#include<Input/Windows/WInput.h>

WInput::WInput(){Reset();}
WInput::~WInput() {}

uint8_t WInput::BitUnpack(uint8_t keycode){
	return ((keys[keycode/16]>>((keycode%16)*2))&3);
}

bool WInput::Down(KEYCODE::keycode_t keycode) {
	//return BitCheckXOR(keycode,3);
	return !(BitUnpack(keycode)^3);
}
bool WInput::Press(KEYCODE::keycode_t keycode) {
	//return BitCheckXOR(keycode,2);
	return BitUnpack(keycode)&2;
}
bool WInput::Up(KEYCODE::keycode_t keycode) {
	//return BitCheckXOR(keycode,1);
	return !(BitUnpack(keycode)^1);
}
void WInput::MousePos(unsigned short &x,unsigned short &y) {
	x=mx;y=my;
}
void WInput::Update(){
	SetDelta(0,0);
	UpdateMouse();
	for(uint8_t i=0;i<16;++i){
		keys[i]&=0xAAAAAAAA;
	}
}
void WInput::Reset(){
	for(uint8_t i=0;i<16;++i){
		keys[i]=0;
	}
}
int WInput::KeyL(uint8_t keycode){
	return 3<<((keycode%16)*2);
}
void WInput::SetKey(uint8_t keycode){
	keys[keycode/16]^=KeyL(keycode);//3<<((keycode%16)*2);
}
void WInput::PressKey(uint8_t keycode){
	uint32_t ks=KeyL(keycode);//3<<((keycode%16)*2);
	uint32_t k = (keys[keycode/16]&~ks)|ks;
	keys[keycode/16]=k;//3<<((keycode%16)*2);
}
void WInput::ReleaseKey(uint8_t keycode){
	uint32_t ks=KeyL(keycode);//3<<((keycode%16)*2);
	uint32_t k = (keys[keycode/16]&~ks)|(1<<((keycode%16)*2));
	keys[keycode/16]=k;//3<<((keycode%16)*2);
}
void WInput::UpdateMousePos(uint16_t x,uint16_t y){
	SetDelta(x-fmx,y-fmy);
	mx=x;my=y;
}
void WInput::UpdateMouse(){
	fmx = mx;
	fmy = my;
}
void WInput::SetDelta(short x,short y){
	dx=x;dy=y;
}
void WInput::MouseDelta(short& x,short& y) {
	x=dx;y=dy;
}
