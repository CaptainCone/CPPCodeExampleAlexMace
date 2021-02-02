#pragma once
#include "header.h"
#include "Cw4State.h"
#include "Cw4Engine.h"
class StateRunning :
	public Cw4State
{
public:
	StateRunning(Cw4Engine* game);
	virtual void virtSetPause();
	void virtSetLvl1(invisDisplayableObj* objs[]);
	void virtSetLvl2(invisDisplayableObj* objs[]);
	void setupLvl(invisDisplayableObj* objs[]);
	void startLvl2(invisDisplayableObj* objs[]);
};

