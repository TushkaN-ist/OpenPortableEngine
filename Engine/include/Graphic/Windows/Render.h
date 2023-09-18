#pragma once

#include <Graphic/Render.h>
#include <Frame/Windows/Frame.h>


class WOGL: public Graphics
{
public:
	WOGL(Frame* frame,unsigned char color,unsigned char depth,unsigned char stencil,unsigned char version);
	~WOGL();
	bool InitIn(Frame* frame);
	void MakeCurrent(Frame* frame);
	void ViewPort(float x, float y, float width, float height) override;
	void ViewPort(short x, short y, short width, short height) override;
	//void Clear( Buffer::buffer_t buffers = Buffer::Color | Buffer::Depth );
	//void ClearColor( float R=.39f,float G=.40f,float B=.34f,float A=1.f );
	void SwapBuffers();
private:
	int pixel_format_attribs[17]={
        WGL_DRAW_TO_WINDOW_ARB,     GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB,     GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,      GL_TRUE,
        WGL_ACCELERATION_ARB,       WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,         WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,         32,
        WGL_DEPTH_BITS_ARB,         24,
        WGL_STENCIL_BITS_ARB,       8,
        0
    };
	HGLRC gl_context;
	FrameWindows* frameW;
};