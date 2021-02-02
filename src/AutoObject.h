#pragma once
#include "DisplayableObject.h"
class AutoObject :
	public DisplayableObject
{
public: 
	AutoObject(BaseEngine* pEngine);
	~AutoObject();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
protected:
	bool bXBounce, bYBounce;
	int X=0, Y=0, speed = 0;
public:
	bool move = true;
};

