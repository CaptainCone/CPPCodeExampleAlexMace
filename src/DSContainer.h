#pragma once
#include "invisDisplayableObj.h"
#include "DeathStar.h"
#include "BasicEnemy.h"

class DSContainer :
	public BasicEnemy
{
public:
	DSContainer(Cw4Engine* game, Explosion* exp);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	virtual void setDefaultPos(int x, int y);
	void checkDS();
protected:
	DeathStar DS;
	int xPos = 0;
	int beamNum = 0;
	int playerX = 0, playerY = 0;
	int down = 1;
	int allhp = 4;
	int hp1 = 5, hp3 = 5, hp4 = 5, hp5 = 5;
};

