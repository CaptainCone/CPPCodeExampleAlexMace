#pragma once 
#include "header.h"
#include "invisDisplayableObj.h"
class Explosion :
	public invisDisplayableObj
{
public:
	Explosion(Cw4Engine* game);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
protected:
	Cw4Engine* pGame;
	SimpleImage expl1, expl2, expl3, expl4, expl5;
	int imgNum = 0;
};

