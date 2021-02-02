#pragma once
#include "StateRunning.h"
class RunLv1 :
	public StateRunning
{
public:
	RunLv1(Cw4Engine* game, invisDisplayableObj* objs[]);
	virtual void setupLvl(invisDisplayableObj* objs[]);
	//virtual void setupLvl(DisplayableObject* objs[]);
protected:
	Cw4Engine* pGame;
};

