#pragma once
#include "header.h"
#include "Bullet.h"
#include "Cw4Engine.h"
#include "CoordinateMapping.h"
#include "MappableImageObject.h"
#include "SimpleImage.h"

class Laser :
	public Bullet
{
public:
	Laser(Cw4Engine* game);
	//~Laser();
	virtual double virtSetXMoveAmt();
	virtual double virtSetYMoveAmt();
	void virtDraw();
	void setAngle(int x1, int y1, int x2, int y2);
	//void virtDoUpdate(int iCurrentTime);

protected:
	Cw4Engine* pGame;
	double angleFrom12 = 0;
	SimpleImage image;
};

