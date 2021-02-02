#pragma once
#include "StateRunning.h"
#include "DeathStar.h"

class RunLv2 :
	public StateRunning
{
public:
	RunLv2(Cw4Engine* game, invisDisplayableObj* objs[]);
	virtual void setupLvl(invisDisplayableObj* objs[]);
protected:
	Cw4Engine* pGame;
};

