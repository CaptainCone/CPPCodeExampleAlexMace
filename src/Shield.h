#pragma once
#include "header.h"
#include "invisDisplayableObj.h"
class Shield :
	public invisDisplayableObj
{
public:
	Shield(Cw4Engine* game);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
};

