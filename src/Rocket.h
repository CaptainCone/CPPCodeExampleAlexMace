#pragma once
#include "header.h"
#include "Cw4Engine.h"
#include "Bullet.h"
class Rocket :
	public Bullet
{
public:
	Rocket(Cw4Engine* game);
	void virtDraw();
	virtual double virtSetXMoveAmt();
protected:
	Cw4Engine* pGame;
};

