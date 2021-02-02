#pragma once
#include "header.h"
#include "BasicEnemy.h"
#include "SimpleImage.h"

class TieFighter :
	public BasicEnemy
{
public:
	TieFighter(Cw4Engine* game, Explosion* expl);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	void flyToPos(int x, int y);
	virtual void setDefaultPos(int x, int y);
protected:
	int destX = 0, destY = 0;
	double angleFrom12 = 0;
	double xMvAmt = 0, yMvAmt = 0;
	double thisX = 0, thisY = 0;
	SimpleImage TIE, TieFire1, TieFire2, TieFire3, TieFire4;
	int imgNum = 0;
};

