#pragma once
#include "Cw4State.h"
class Lvl2StartState :
	public Cw4State
{
public:
	Lvl2StartState(Cw4Engine* game);
	virtual void enterPress();
};

