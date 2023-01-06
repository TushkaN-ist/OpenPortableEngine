#pragma once

class FPS
{
	protected:
	float _delta,_deltaSmooth;
	unsigned short _target,_last;
	public:
	static FPS* Create(unsigned short target=30);
	virtual void Set(unsigned short fps)=0;
	unsigned short GetFPS();
	unsigned short GetFPSFast();
	float GetDelta();
	float GetDeltaSmooth();
	virtual bool Update()=0;
	unsigned short GetTargetFPS(){
		return _target;
	}
};