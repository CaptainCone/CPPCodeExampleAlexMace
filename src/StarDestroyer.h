#pragma once
#include "BasicEnemy.h"
#include "Shield.h"

class StarDestroyer :
	public BasicEnemy
{
public:
	StarDestroyer(Cw4Engine* game, Explosion* expl, Shield* shld);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	void drawShield();

	virtual void setDefaultPos(int x, int y);

protected:
	Shield* pShield;
	SimpleImage SD1, SD2;
	int timeShldDown = 0;
	bool lvl1 = true;
};

