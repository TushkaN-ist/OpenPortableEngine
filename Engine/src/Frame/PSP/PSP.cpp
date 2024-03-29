#include <Platform/PlatformDefined.h>
#ifdef _PLATFORM_PSP

#include <Platform/PlatformIncludes.hpp>
#include <Platform/Input.hpp>
#include <Graphics/Render.hpp>
#include <Frame/Frame.h>

#define KEY_TYPE_ASCII	  1
#define KEY_TYPE_SPECIAL  2
#define KEY_TYPE_MOUSE	  3

#define KEY_ASCII(x)      ((KEY_TYPE_ASCII   << 24) | (x))
#define KEY_SPECIAL(x)    ((KEY_TYPE_SPECIAL << 24) | (x))
#define KEY_MOUSE(x)      ((KEY_TYPE_MOUSE   << 24) | (x))

#define KEY_TYPE(x)	  (x >> 24)

/* XXX IMPROVE: might get packed tighter in 16bit words */
static const
unsigned char keycode [] = {
	KEYCODE::KC_SHIFT,		/* PSP_CTRL_SELECT   = 0x000001 */
	0,				/*                     0x000002 */
	0,				/*                     0x000004 */
	KEYCODE::KC_RETURN,		/* PSP_CTRL_START    = 0x000008 */
	KEYCODE::KC_UP,			/* PSP_CTRL_UP	     = 0x000010 */
	KEYCODE::KC_RIGHT,		/* PSP_CTRL_RIGHT    = 0x000020 */
	KEYCODE::KC_DOWN,		/* PSP_CTRL_DOWN     = 0x000040 */
	KEYCODE::KC_LEFT,		/* PSP_CTRL_LEFT     = 0x000080 */
	KEYCODE::MB_LBUTTON,	/* PSP_CTRL_LTRIGGER = 0x000100 */
	KEYCODE::MB_RBUTTON,	/* PSP_CTRL_RTRIGGER = 0x000200 */
	0,				/*                     0x000400 */
	0,				/*                     0x000800 */
	KEYCODE::KC_S,			/* PSP_CTRL_TRIANGLE = 0x001000 */
	KEYCODE::KC_C,			/* PSP_CTRL_CIRCLE   = 0x002000 */
	KEYCODE::KC_X,			/* PSP_CTRL_CROSS    = 0x004000 */
	KEYCODE::KC_Z,			/* PSP_CTRL_SQUARE   = 0x008000 */
	KEYCODE::KC_HOME,		/* PSP_CTRL_HOME     = 0x010000 */
	KEYCODE::KC_DELETE,		/* PSP_CTRL_HOLD     = 0x020000 */
	0,						/* PSP_CTRL_SCREEN                    0x040000 */
	0,						/* PSP_CTRL_REMOTE                    0x080000 */
	0,						/* PSP_CTRL_VOLUP                    0x100000 */
	0,						/* PSP_CTRL_VOLDOWN                    0x200000 */
	0,						/* PSP_CTRL_WLAN_UP                    0x400000 */
	KEYCODE::KC_END,		/* PSP_CTRL_NOTE     = 0x800000 */
	0,						/* PSP_CTRL_DISC     = 0x800000 */
	0,						/* PSP_CTRL_MS     = 0x2000000 */
};

static __attribute__((destructor)) void back_to_kernel (void)
{
	sceKernelExitGame();
}
Frame::~Frame(){
}

class PSPInput : public Input
{
public:
	PSPInput(){Reset();mouseSentesivity=8;}
	~PSPInput(){}
	
	bool BitCheck( uint8_t keycode, uint8_t b){
		return (((keys[keycode/16]>>((keycode%16)*2))&3)^b)==0;
	}
	
	bool Down(KEYCODE::keycode_t keycode){
		return BitCheck(keycode,3);
	}
	bool Pres(KEYCODE::keycode_t keycode){
		return BitCheck(keycode,2);
	}
	bool Up(KEYCODE::keycode_t keycode){
		return BitCheck(keycode,1);
	}
	void MousePos(unsigned short &x,unsigned short &y){
		x=mx;
		y=my;
	}
	void Update(){
		for(uint8_t i=0;i<16;++i){
			keys[i]&=0xAAAAAAAA;
		}
		//printf("%u\n",keys[0]);

		int i;
		unsigned short mx,my;
		struct SceCtrlData pad;
		sceCtrlReadBufferPositive(&pad, 1);
		input->MousePos(mx,my);
		float f=(pad.Lx-128)/128.f;
		if (f*f>0.1f){
			i = mx+input->GetSentisivity()*f;
			mx=i>rect[2]?rect[2]:i<0?0:i;
		}
		f=(pad.Ly-128)/128.f;
		if (f*f>0.1f){
			i = my+input->GetSentisivity()*f;
			my=i>rect[3]?rect[3]:i<0?0:i;
		}
		input->SetMousePos(mx,my);

	}
	void Reset(){
		for(uint8_t i=0;i<16;++i){
			keys[i]=0;
		}
		//printf("%x\n",keys[0]);
	}
	void SetKey(uint8_t keycode){
		keys[keycode/16]^=3<<((keycode%16)*2);
	}
	void PressKey(uint8_t keycode){
		uint32_t ks=3<<((keycode%16)*2);
		uint32_t k = keys[keycode/16]&~ks|ks;
		keys[keycode/16]=k;//3<<((keycode%16)*2);
	}
	void ReleaseKey(uint8_t keycode){
		uint32_t ks=3<<((keycode%16)*2);
		uint32_t k = keys[keycode/16]&~ks|(1<<((keycode%16)*2));
		keys[keycode/16]=k;//3<<((keycode%16)*2);
	}
	void SetMousePos(uint16_t x,uint16_t y){
		dx=x-mx;dy=y-my;
		mx=x,my=y;
	}
	void MouseDelta(int16_t& x,int16_t& y){
		x=dx;y=dy;
	}
	inline unsigned short GetSentisivity(){return mouseSentesivity;}
private:
	uint16_t mx,my;
	uint16_t dx,dy;
	uint32_t keys[16];
};

class JoystickPSP : public Joystick
{
public:
	JoystickPSP(){
		
	}
	~JoystickPSP(){
		
	}
	char* Name() const{
		return "PSP GamePad";
	}
	bool Down(unsigned char btn){
		return false;
	}
	bool Pres(unsigned char btn){
		return false;
	}
	bool Up(unsigned char btn){
		return false;
	}
	float Axe(unsigned char axe){
		return axes[axe];
	}
private:
	float axes[2];
	uint32_t keys[2];
};
class FramePSP : public Frame
{
public:
	FramePSP(unsigned short width,unsigned short height);
	~FramePSP();
	
	void SetStyle(Frame::Style style=(Frame::Style)3){}
	void SetRect(short x,short y,unsigned short width,unsigned short height){}
	void SetPos(short x,short y){}
	void SetSize(unsigned short width,unsigned short height){}
	void SetTitle(const char* text){}
	
	void GetRect(short &x,short &y,unsigned short &width,unsigned short &height);
	void GetPos(short &x,short &y);
	void GetSize(unsigned short &width,unsigned short &height);
	
	bool Update();
	Input* GetInput(){
		return input;
	}
	bool Close();
private:
	unsigned short rect[4];
	PSPInput* input;
	bool isRun;
};
FramePSP* mainF=0;

int ExitCallback(int Arg1, int Arg2, void *Common) { //??????????????
	mainF->Close();
	return 0;
}
int CallbackThread(SceSize Args, void *Argp) {
	int CallbackId;
	CallbackId = sceKernelCreateCallback("Exit Callback", ExitCallback, NULL);
	sceKernelRegisterExitCallback(CallbackId);
	sceKernelSleepThreadCB();
	return 0;
}
int SetupCallbacks(void) {
	int ThreadId = 0;
	//pspKernelSetKernelPC(); 
	//pspDebugInstallErrorHandler((void *) 0);
	ThreadId = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if (ThreadId >= 0)
	{
		sceKernelStartThread(ThreadId, 0, 0);
	}
	return ThreadId;
}

bool FramePSP::Close(){
	back_to_kernel();
	isRun=false;
	return true;
}
void FramePSP::GetRect(short &x,short &y,unsigned short &width,unsigned short &height){
	GetPos(x,y);
	GetSize(width,height);
}
void FramePSP::GetSize(unsigned short &width,unsigned short &height){
	width=rect[2];
	height=rect[3];
}
void FramePSP::GetPos(short &x,short &y){
	x=rect[0];
	y=rect[1];
}

Frame* Frame::Create(unsigned short width,unsigned short height, Frame::Style style){
	if (mainF)
		return mainF;
	return new FramePSP(width,height);
}

FramePSP::FramePSP(unsigned short width,unsigned short height){
	mainF=this;
	input=new PSPInput();
	rect[0]=rect[1]=0;
	rect[2]=width>480?480:width;
	rect[3]=height>272?272:height;
	
	isRun = SetupCallbacks()>=0;
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
}
FramePSP::~FramePSP(){
	delete input;
	mainF=0;
}
bool FramePSP::Update(){
	input->Update();
	struct SceCtrlLatch latch;
	while (1) {
		sceCtrlReadLatch(&latch);
		if (latch.uiMake == 0 && latch.uiBreak == 0)
			break;
		for (i=0; i<sizeof(keycode)/sizeof(keycode[0]); i++) {
			if (latch.uiMake & (1 << i))
				input->PressKey(keycode[i]);
			if (latch.uiBreak & (1 << i))
				input->ReleaseKey(keycode[i]);
		}
	};
	return isRun;
}


////////////RENDER INIT///////////////
//
//
//
//

static EGLint attrib_list [] = {
	EGL_RED_SIZE, 8,	/* 0 */
	EGL_GREEN_SIZE, 8,	/* 2 */
	EGL_BLUE_SIZE, 8,	/* 4 */
	EGL_ALPHA_SIZE, 8,	/* 6 */
	EGL_STENCIL_SIZE, 0,	/* 8 */
	EGL_DEPTH_SIZE, 0,	/* 10 */
	EGL_NONE
};

class PSPEGL: public Graphics
{
public:
	PSPEGL(Frame* frame,unsigned char color,unsigned char depth,unsigned char stencil);
	~PSPEGL();
	bool InitIn(Frame* frame);
	void MakeCurrent(Frame* frame);
	void ViewPort(float x,float y,float width,float height);
	//void Clear( Buffer::buffer_t buffers = Buffer::Color | Buffer::Depth );
	//void ClearColor( float R=.39f,float G=.40f,float B=.34f,float A=1.f );
	void SwapBuffers();
private:
	EGLDisplay display;
	EGLint major,minor;
	EGLContext context;
	EGLSurface surface;
};

PSPEGL* egl=0;

PSPEGL::PSPEGL(Frame* frame,unsigned char color,unsigned char depth,unsigned char stencil){
	egl=this;
	EGLConfig config;
	EGLint num_configs;
	
	/*EGLint *attrib=new EGLint[12];
	attrib[0]=EGL_RED_SIZE;
	attrib[1]=8;
	attrib[2]=EGL_GREEN_SIZE;
	attrib[3]=8;
	attrib[4]=EGL_BLUE_SIZE;
	attrib[5]=8;
	attrib[6]=EGL_ALPHA_SIZE;
	attrib[7]=8;
	attrib[8]=EGL_STENCIL_SIZE;
	attrib[9]=stencil;
	attrib[10]=EGL_DEPTH_SIZE;
	attrib[11]=depth;
	attrib[12]=EGL_NONE;*/
	attrib_list[9]=stencil;
	attrib_list[11]=depth;
	
	display = eglGetDisplay(0);
	eglInitialize(display, NULL, NULL);
	eglChooseConfig(display, attrib_list, &config, 1, &num_configs);
	context = eglCreateContext(display, config, NULL, NULL);
	surface = eglCreateWindowSurface(display, config, 0, NULL);
	MakeCurrent(frame);
	
	unsigned short w,h;
	frame->GetSize(w,h);
	ViewPort(0,0,w,h);
}
PSPEGL::~PSPEGL(){
	eglDestroyContext(display,context);
	eglDestroySurface(display,surface);
	eglTerminate(display);
	egl=0;
}
bool PSPEGL::InitIn(Frame* frame){
	return true;
}
void PSPEGL::MakeCurrent(Frame* frame){
	eglMakeCurrent(display, surface, surface, context);
}

void PSPEGL::ViewPort(float x,float y,float width,float height){
	u_short w,h;
	mainF->GetSize( w, h );
	glViewport(x*w,y*h,(width-x)*w,(height-y)*h);
}

void PSPEGL::SwapBuffers(){
	eglSwapBuffers(display, surface);
}

Graphics* Graphics::Create(Frame* frame,unsigned char color,unsigned char depth,unsigned char stencil,unsigned char version){
	if (egl)
		return egl;
	return new PSPEGL(frame,color,depth,stencil);
}
bool Graphics::TestInit(unsigned char color,unsigned char depth,unsigned char stencil){
	return true;//Just cost we CAN
}

#endif