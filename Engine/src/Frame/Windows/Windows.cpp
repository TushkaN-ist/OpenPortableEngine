//NEED REVIEW AND REFACTORIN!!! 
#include <Platform/PlatformDefined.h>
#ifdef _PLATFORM_WINDOWS

#include <Platform/PlatformIncludes.h>
#include <Input/Windows/WInput.h>
#include <Input/Windows/Joysticks_Win.h>
#include <Frame/Windows/Frame.h>

#include <string>
//#include <wchar.h>

#ifndef NDEBUG
#include <stdio.h>
#endif

HINSTANCE inst;

void fatal_error(char *msg)
{
    MessageBoxA(NULL, msg, "Error", MB_OK | MB_ICONEXCLAMATION);
    exit(EXIT_FAILURE);
}


Frame::~Frame(){}

Frame* Frame::Create(unsigned short width,unsigned short height,Style style){
	return new FrameWindows(width,height,style);
}

void DefaultEvent(Frame::Events ev, Frame* frame){
	if (ev == Frame::evClose){
		frame->Close(true);
	}
}

LRESULT CALLBACK FrameWindows::WindowProc(Frame* frame, UINT msg, WPARAM wparam, LPARAM lparam)
{
    LRESULT result = 0;

    switch (msg) {
		//case WM_NCCREATE:
		case WM_MOVE:
		case WM_SIZE:
			RECT grect;
			GetWindowRect( hWnd, &grect );
			rect[0]=grect.left;
			rect[1]=grect.top;
			GetClientRect( hWnd, &grect );
			rect[2]=grect.right;
			rect[3]=grect.bottom;
			if (eventsCallBack!=nullptr)
				eventsCallBack(Events::evResize,frame);
			//printf("Rect:%i,%i,%i,%i\n",rect[0],rect[1],rect[2],rect[3]);
		break;
		case WM_SETFOCUS:
			if (eventsCallBack!=nullptr)
				eventsCallBack(Events::evFocusSet,frame);
		break;
		case WM_KILLFOCUS:
			input->Reset();
			if (eventsCallBack!=nullptr)
				eventsCallBack(Events::evFocusLose,frame);
		break;
		case WM_CLOSE:
			if (eventsCallBack!=nullptr)
				eventsCallBack(Events::evClose,frame);
			return 0;
		break;
        case WM_DESTROY:
			return 0;
            break;
		case WM_MOUSEMOVE:
			input->UpdateMousePos(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
		break;
		case WM_LBUTTONDBLCLK:
		case WM_LBUTTONDOWN:
			input->UpdateMousePos(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			input->PressKey(KEYCODE::MB_LBUTTON);
		break;
		case WM_MBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
			input->UpdateMousePos(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			input->PressKey(KEYCODE::MB_MBUTTON);
		break;
		case WM_RBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
			//printf("%i\n",wparam);
			input->UpdateMousePos(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			input->PressKey(KEYCODE::MB_RBUTTON);
		break;
#if _WIN32_WINNT>=0x0500
		case WM_XBUTTONDBLCLK:
		case WM_XBUTTONDOWN:
			//printf("%i\n",wparam);
			input->UpdateMousePos(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			input->PressKey(wparam);
		break;
#endif
		case WM_LBUTTONUP:
			input->UpdateMousePos(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			input->ReleaseKey(KEYCODE::MB_LBUTTON);
		break;
		case WM_MBUTTONUP:
			input->UpdateMousePos(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			input->ReleaseKey(KEYCODE::MB_MBUTTON);
		break;
		case WM_RBUTTONUP:
			input->UpdateMousePos(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			input->ReleaseKey(KEYCODE::MB_RBUTTON);
		break;
#if _WIN32_WINNT>=0x0500
		case WM_XBUTTONUP:
			input->UpdateMousePos(GET_X_LPARAM(lparam),GET_Y_LPARAM(lparam));
			input->ReleaseKey(wparam);
		break;
#endif
		case WM_KEYDOWN:
			if (lastKey==wparam)
				break;
			lastKey = wparam;
			//printf("%i\n",wparam);
			input->PressKey(wparam);
		break;
		case WM_KEYUP:
			input->ReleaseKey(wparam);
			lastKey=0;
		break;
        default:
            result = DefWindowProcA(hWnd, msg, wparam, lparam);
            break;
    }

    return result;
}

bool FrameWindows::Close(bool force){
	if (force){
		if (IsAlive()){
			SetWindowLongPtr(hWnd, GWL_USERDATA, 0);
			DestroyWindow( hWnd );
			UnregisterClassA( className.c_str(), GetModuleHandle( NULL ) );
			ReleaseDC(Handle(), DC());
			delete input;
			input = NULL;
			hWnd = nullptr;
		}
	}else{
		return CloseWindow(hWnd);
	}
	return hWnd==nullptr;
}

LRESULT CALLBACK FrameWindows::static_WindowProc(HWND window, UINT msg, WPARAM wparam, LPARAM lparam){
	FrameWindows *view;
	
	view = (FrameWindows*) GetWindowLongPtr(window, GWL_USERDATA);

	if (view && window == view->Handle())
		return view->WindowProc(view, msg, wparam, lparam);

    return DefWindowProc(window, msg, wparam, lparam);
}

uint32_t windowID;

FrameWindows::FrameWindows(unsigned short width, unsigned short height, Frame::Style style){
    RECT rect;
	GetClientRect(GetDesktopWindow(), &rect);
	int xPos = (rect.right/2) - (width/2);
    int yPos = (rect.bottom/2) - (height/2);
	window_style = WS_POPUP | WS_VISIBLE | WS_SYSMENU;
	if ( style & Frame::Fullscreen ){
		xPos = 0;
		yPos = 0;
	}else{
		rect.right = width;
		rect.bottom = height;
		if (style){
			window_style = WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE;
			if ( style & Frame::Closing ) window_style |= WS_SYSMENU;
			if ( style & Frame::Resize ) window_style |= WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX;
		}
	}
	this->style = style;
    
	className = DEFNAME;
	className += std::to_string(windowID++);
	WNDCLASSA window_class = {
        .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
        .hInstance = inst,
        .hCursor = LoadCursor(0, IDC_ARROW),
        .hbrBackground = 0,
        .lpszClassName = className.c_str()
    };
    window_class.lpfnWndProc = static_WindowProc;
    if (!RegisterClassA(&window_class)) {
        fatal_error("Failed to register window.");
    }
    AdjustWindowRect(&rect, window_style, false);
    hWnd = CreateWindowExA(
        0,
        window_class.lpszClassName,
        _APP_NAME,
        window_style,
        xPos,
        yPos,
        rect.right - rect.left,
        rect.bottom - rect.top,
        0,
        0,
        inst,
        0);

    if (!hWnd) {
		fatal_error("Failed to create window.");
    }
#if _WIN32_WINNT>=0x0601
	RegisterTouchWindow(hWnd, 0);
#endif
	if (SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR) this) == 0)
	{
		if (GetLastError() != 0)
			fatal_error("Failed to set userdata.");
	}
	SetTitle(_APP_NAME);
	GetWindowRect( hWnd, &rect );
	this->rect[0]=rect.left;
	this->rect[1]=rect.top;
	GetClientRect( hWnd, &rect );
	this->rect[2]=rect.right;
	this->rect[3]=rect.bottom;
	real_dc = GetDC(hWnd);
	input = new WInput();
	eventsCallBack = DefaultEvent;
	//isAlive=true;
	
}
void FrameWindows::SetTitle(const char* text){
	SetWindowTextA(hWnd,text);
}

bool FrameWindows::Update(){
	if (IsAlive()){
		input->Update();
		WJoystick::Update();
		MSG msg;
		while (PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		return IsAlive();
	}else
		return false;
}


FrameWindows::~FrameWindows(){
	Close(true);
}

void FrameWindows::SetStyle(Frame::Style style){
	if (style==this->style)
		return;
    RECT rect;
	GetClientRect(GetDesktopWindow(), &rect);
	window_style = WS_POPUP | WS_VISIBLE | WS_SYSMENU;
	if ( style & Frame::Fullscreen ){
		this->rect[4] = this->rect[0];
		this->rect[5] = this->rect[1];
		this->rect[6] = this->rect[2];
		this->rect[7] = this->rect[3];
		MoveWindow(hWnd,0,0,rect.right,rect.bottom,false);
	}else{
		rect.right = this->rect[2];
		rect.bottom = this->rect[3];
		if (style){
			window_style = WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE;
			if ( style & Frame::Closing ) window_style |= WS_SYSMENU;
			if ( style & Frame::Resize ) window_style |= WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX;
		}
		if ( this->style & Frame::Fullscreen )
			MoveWindow(hWnd, this->rect[4], this->rect[5], this->rect[6], this->rect[7], false);
	}
	this->style = style;
	SetWindowLong(hWnd, GWL_STYLE, window_style);
}
void FrameWindows::SetRect(short x, short y, unsigned short width, unsigned short height){
		RECT crect = {
		.left = x,
		.top = y,
		.right = width+x,
		.bottom = height+y
	};
	AdjustWindowRectEx(&crect,window_style,false,WS_EX_APPWINDOW);
	MoveWindow(hWnd, rect[0]=crect.left, rect[1]=crect.top, rect[2]=crect.right-crect.left, rect[3]=crect.bottom-crect.top, false);
}
void FrameWindows::SetSize(unsigned short width,unsigned short height){
	SetRect(rect[0],rect[1],width,height);
}
void FrameWindows::SetPos(short x,short y){
	SetRect(x,y,rect[2],rect[3]);
}

void FrameWindows::GetRect(short &x,short &y,unsigned short &width,unsigned short &height){
	GetPos(x,y);
	GetSize(width,height);
}
void FrameWindows::GetSize(unsigned short &width,unsigned short &height){
	width = rect[2];
	height = rect[3];
}
void FrameWindows::GetPos(short &x,short &y){
	x = rect[0];
	y = rect[1];
}
#endif