#pragma once
#include "header.h"
#include "invisDisplayableObj.h"
#include "Explosion.h"

class BasicEnemy :
	public invisDisplayableObj
{
public:
	BasicEnemy(Cw4Engine* game, Explosion* expl);
	bool checkPixel(int x, int y);
	bool checkRectangle(int x1, int y1, int x2, int y2);
	bool checkCircle(int x, int y, int r);
	bool checkTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
	bool checkLine(int x1, int y1, int x2, int y2);
	void doExplosion(int x, int y);
	void setDefaultPos(int x, int y);
	bool getActive() { return active; }
	void setActive(bool b) { active = b; }
	double setXMoveAmt();
	double setYMoveAmt();
	void setAngle(int x1, int y1, int x2, int y2);
protected:
	Cw4Engine* pGame;
	Explosion* exp;
	int hp;
	int timeLastShot = 0;
	int xStart = 0, yStart = 0;
	bool active = false;
	double angleFrom12 = 0;
	double thisX = 0, thisY = 0;
	int expX = 0, expY = 0;
};

