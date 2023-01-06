#include <Input/Input.h>
#include <stdio.h>

Joystick::Joystick(){
    //printf("Create\n");
}
Joystick::~Joystick(){
}
const char* Joystick::Name(){
    return "NULL";
}

bool Joystick::Down(unsigned char btn){return false;}
bool Joystick::Press(unsigned char btn){return false;}
bool Joystick::Up(unsigned char btn){return false;}

float Joystick::Axis01(unsigned char axis, float deadzone){return 0;}
float Joystick::Axis(unsigned char axis, float deadzone){return 0;}
short Joystick::AxisRaw(unsigned char axis, short deadzone){return 0;}
unsigned char Joystick::AxisCount(){return 0;}
unsigned char Joystick::BtnsCount(){return 0;}

void Joystick::Open(){}
bool Joystick::IsOpen(){return false;}
void Joystick::Close(){}