#pragma once
#include "header.h"
#include "DisplayableObject.h"
#include "Cw4Engine.h"

class Cw4Engine;

class invisDisplayableObj :
	public DisplayableObject
{
public:
	invisDisplayableObj(Cw4Engine* game);
	//void setVisible(bool b);
	void setExplode(bool b);
	//bool getVisible();
	bool getExplode();
	void virtDoUpdate(int iCurrentTime);
	virtual void setDefaultPos(int x, int y);
	bool visible = false; // has to be public?
	bool explode = false;
	void setTicks(int i) { ticks = i; }
protected:
	Cw4Engine* pGame;
	int lastCurrTime;
	int ticks = 0;
};

