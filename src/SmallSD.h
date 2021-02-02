#pragma once
#include "StarDestroyer.h"
class SmallSD :
	public StarDestroyer
{
public:
	SmallSD(Cw4Engine* game, Explosion* expl);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
protected:
	SimpleImage smallSD1, smallSD2;
};

