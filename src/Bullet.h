#pragma once
#include "header.h"
#include "MappableImageObject.h"
#include "CoordinateMapping.h"
#include "Cw4Engine.h"

class Bullet :
	public MappableImageObject
{
public:
	Bullet(Cw4Engine* game);
	void virtDoUpdate(int iCurrentTime);
	virtual double virtSetXMoveAmt() { return 0; }
	virtual double virtSetYMoveAmt() { return 0; }
	void setShot(bool b);
	bool checkPixel(int x, int y);
	void setTicks(int i) { ticks = i; }
protected:
	Cw4Engine* pGame;
	bool shot = false;
	int speed = 0;
	int* cycle, * num;
	int MAX = 0;
	CoordinateMappingRotate rotator;
	int timeLastShot = 0;
	int currTime = 0;
	double xMvAmt = 0, yMvAmt = 0;
	int ticks = 0;
public:
	double thisX = 0, thisY = 1;
};

