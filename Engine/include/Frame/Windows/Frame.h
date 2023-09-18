#pragma once
#include <Frame/Frame.h>
#include <Input/Windows/WInput.h>
extern void fatal_error(char *msg);
class FrameWindows : public Frame
{
public:
	FrameWindows(unsigned short width,unsigned short height,Style style);
	~FrameWindows() override;
	
	void SetStyle(Frame::Style style=(Style)(Style::Base|Style::Closing)) override ;
	void SetRect(short x,short y,unsigned short width,unsigned short height) override ;
	void SetPos(short x,short y) override ;
	void SetSize(unsigned short width,unsigned short height) override ;
	void SetTitle(const char* text) override ;
	
	void GetRect(short &x,short &y,unsigned short &width,unsigned short &height) override ;
	void GetPos(short &x,short &y) override ;
	void GetSize(unsigned short &width,unsigned short &height) override ;
	
	bool Update();
	Input* GetInput(){
		return input;
	}
	bool Close(bool force = false);
	
	inline HWND Handle(){
		return hWnd;
	}
	inline HDC DC(){
		return real_dc;
	}
	bool IsAlive() override{
		return hWnd!=nullptr;
	}
private:
	LRESULT CALLBACK WindowProc(Frame* frame, UINT msg, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK static_WindowProc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam);
	std::string className;
	WInput* input;
	HWND hWnd;
	HDC real_dc;
	DWORD window_style;
	int rect[8];
	WPARAM lastKey;
	Frame::Style style;
};