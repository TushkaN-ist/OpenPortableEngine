#include <Graphic/Windows/Render.h>
#include <Frame/Windows/Frame.h>
#include <GL/Extensions.h>

	//#define APIENTRYP WINAPI *
	//typedef ptrdiff_t GLsizeiptr;
	//typedef ptrdiff_t GLintptr;
	typedef char GLchar;
	
	#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
	#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
	#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
	#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

	#define WGL_DRAW_TO_WINDOW_ARB 0x2001
	#define WGL_ACCELERATION_ARB 0x2003
	#define WGL_SUPPORT_OPENGL_ARB 0x2010
	#define WGL_DOUBLE_BUFFER_ARB 0x2011
	#define WGL_PIXEL_TYPE_ARB 0x2013
	#define WGL_COLOR_BITS_ARB 0x2014
	#define WGL_DEPTH_BITS_ARB 0x2022
	#define WGL_STENCIL_BITS_ARB 0x2023
	#define WGL_SAMPLE_BUFFERS_ARB 0x2041
	#define WGL_SAMPLES_ARB 0x2042
	#define WGL_TYPE_RGBA_ARB 0x202B
	#define WGL_FULL_ACCELERATION_ARB 0x2027
#ifndef WGL_WGLEXT_PROTOTYPES
	WGLCREATECONTEXTATTRIBSARB wglCreateContextAttribsARB;
	WGLCHOOSEPIXELFORMATARB wglChoosePixelFormatARB;
	PFNWGLSWAPINTERVALEXTPROC       wglSwapIntervalEXT = NULL;
	PFNWGLGETSWAPINTERVALEXTPROC    wglGetSwapIntervalEXT = NULL;
#endif

//#define LoadExt(extensionName) GL::LoadExt(extensionName,#extensionName)

bool Graphics::TestInit(unsigned char color,unsigned char depth,unsigned char stencil){
	WNDCLASSA window_class = {
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .lpfnWndProc = DefWindowProcA,
        .hInstance = GetModuleHandle(0),
        .lpszClassName = "Dummy_WGL_Portable Engine"
    };

    if (!RegisterClassA(&window_class)) {
        fatal_error("Failed to register dummy OpenGL window.");
    }

    HWND dummy_window = CreateWindowExA(
        0,
        window_class.lpszClassName,
        "Dummy OpenGL Window",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        window_class.hInstance,
        0);

    if (!dummy_window) {
        fatal_error("Failed to create dummy OpenGL window.");
    }
	
	HDC dummy_dc = GetDC(dummy_window);

    PIXELFORMATDESCRIPTOR pfd = {
        .nSize = sizeof(pfd),
        .nVersion = 1,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = color,
        .cAlphaBits = 8,
        .iLayerType = PFD_MAIN_PLANE
    };
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.cDepthBits = depth;
    pfd.cStencilBits = stencil;

    int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
    if (!pixel_format) {
        fatal_error("Failed to find a suitable pixel format.");
    }
    if (!SetPixelFormat(dummy_dc, pixel_format, &pfd)) {
        fatal_error("Failed to set the pixel format.");
    }

    HGLRC dummy_context = wglCreateContext(dummy_dc);
    if (!dummy_context) {
        fatal_error("Failed to create a dummy OpenGL rendering context.");
    }

    if (!wglMakeCurrent(dummy_dc, dummy_context)) {
        fatal_error("Failed to activate dummy OpenGL rendering context.");
    }

    GL::LoadExtensions();
	/*LoadExt(wglCreateContextAttribsARB);
	LoadExt(wglChoosePixelFormatARB);
	LoadExt(wglSwapIntervalEXT);*/

    wglMakeCurrent(dummy_dc, 0);
    wglDeleteContext(dummy_context);
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);
	return true;
}

Graphics* Graphics::Create(Frame* frame,unsigned char color,unsigned char depth,unsigned char stencil,unsigned char version){
	return new WOGL(frame,color,depth,stencil,version);
}

WOGL::WOGL(Frame* frame,unsigned char color,unsigned char depth,unsigned char stencil,unsigned char version){
	pixel_format_attribs[11] = color;
	pixel_format_attribs[13] = depth;
	pixel_format_attribs[15] = stencil;
	
	frameW = (FrameWindows*)frame;
	HDC real_dc = frameW->DC();
	
    int pixel_format;
    UINT num_formats;
    wglChoosePixelFormatARB(real_dc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
    if (!num_formats) {
        fatal_error("Failed to set the OpenGL pixel format.");
    }

    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(real_dc, pixel_format, sizeof(pfd), &pfd);
    if (!SetPixelFormat(real_dc, pixel_format, &pfd)) {
        fatal_error("Failed to set the OpenGL pixel format.");
    }
	
	int glMaj=(int)(version/10),glMin=(int)(version%10);
    // Specify that we want to create an OpenGL core profile context
    int gl_attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, glMaj,
        WGL_CONTEXT_MINOR_VERSION_ARB, glMin,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
    };

    gl_context = wglCreateContextAttribsARB(real_dc, 0, gl_attribs);
    if (!gl_context) {
        fatal_error("Failed to create OpenGL context.");
    }

    if (!wglMakeCurrent(real_dc, gl_context)) {
        fatal_error("Failed to activate OpenGL rendering context.");
    }
	
	printf("GL %i.%i Initialize Complete.\n",glMaj,glMin);
}

WOGL::~WOGL(){
	wglMakeCurrent(frameW->DC(), 0);
	wglDeleteContext(gl_context);
}

bool WOGL::InitIn(Frame* frame){
	
	frameW = (FrameWindows*)frame;
	HDC real_dc = frameW->DC();
	
    int pixel_format;
    UINT num_formats;
    wglChoosePixelFormatARB(real_dc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
    if (!num_formats) {
        fatal_error("Failed to set the OpenGL pixel format.");
    }

    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(real_dc, pixel_format, sizeof(pfd), &pfd);
    if (!SetPixelFormat(real_dc, pixel_format, &pfd)) {
        fatal_error("Failed to set the OpenGL pixel format.");
    }
	
	return true;
}

void WOGL::MakeCurrent(Frame* frame){
	frameW = (FrameWindows*)frame;
    if (frameW->IsAlive() && !wglMakeCurrent(frameW->DC(), gl_context)) {
        fatal_error("Failed to activate OpenGL rendering context.");
    }
	ViewPort(0.f,0.f,1.f,1.f);
}

void WOGL::ViewPort(float x, float y, float width, float height){
	u_short w,h;
	frameW->GetSize( w, h );
	ViewPort((short)(x * w), (short)(y * h), (short)((width-x)*w), (short)((height-y)*h));
}
void WOGL::ViewPort(short x, short y, short width, short height){
	glViewport(x, y, width - x, height - y);
}

void WOGL::SwapBuffers(){
	::SwapBuffers( frameW->DC() );
}

/*void WOGL::Clear( Buffer::buffer_t buffers){
	glClear(buffers);
}
void WOGL::ClearColor( float R,float G,float B,float A ){
	glClearColor(R,G,B,A);
}*/