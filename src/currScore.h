#pragma once
#include "invisDisplayableObj.h"
class currScore :
	public invisDisplayableObj
{
public:
	currScore(Cw4Engine* game);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
protected:
	int health = 0;
	int hBar = 0;

};

