#pragma once

class Graphics;
class Input;


class Frame
{
public:

	enum Style
	{
		NoBorders = 0,
		Base = 1,
		Resize = 2,
		Closing = 4,
		Fullscreen = 8
	};
	enum Events
	{
		evClose,
		evResize,
		evFocusSet,
		evFocusLose
	};
	
	typedef void (* vEventFunc)(Frame::Events event,Frame* frame);
	
	//Frame(){};
	virtual ~Frame()=0;
	
	static Frame* Create( unsigned short width, unsigned short heigth, Frame::Style style);
	virtual void SetStyle( Frame::Style style=(Frame::Style)2)=0;
	virtual void SetRect( short x, short y, unsigned short width, unsigned short height)=0;
	virtual void SetPos( short x, short y)=0;
	virtual void SetSize( unsigned short width, unsigned short height)=0;
	virtual void SetTitle( const char* text)=0;
	
	virtual void GetRect( short &x, short &y, unsigned short &width, unsigned short &height)=0;
	virtual void GetPos( short &x, short &y)=0;
	virtual void GetSize( unsigned short &width, unsigned short &height)=0;
	
	void SetEventsCallBack(vEventFunc func){
		eventsCallBack = func;
	}
	virtual bool Update()=0;
	virtual Input* GetInput()=0;
	virtual bool Close(bool force=false)=0;
	virtual bool IsAlive()=0;
protected:
	vEventFunc eventsCallBack = nullptr;
};

inline Frame::Style operator|( Frame::Style lft, Frame::Style rht )
{
	return Frame::Style( lft | rht );
}