#pragma once
#include "header.h"
#include "invisDisplayableObj.h"
#include "Explosion.h"

//class invisDisplayableObj;

class Player :
	public invisDisplayableObj
{
public:
	Player(Cw4Engine* game, Explosion* exp);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	bool checkFalcon();
	void setTimeShot();
	bool checkPixel(int x, int y);
	bool checkRectangle(int x1, int y1, int x2, int y2);
	bool checkCircle(int x, int y, int r);
	bool checkTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
	bool checkLine(int x1, int y1, int x2, int y2);
	void doExplosion(int x, int y);
protected:
	Cw4Engine* pGame;
	SimpleImage falcon;
	Explosion* expl;
	int expX = 0, expY = 0;
	int timeLastShot = 0;
public:
	int health = 145;
};

