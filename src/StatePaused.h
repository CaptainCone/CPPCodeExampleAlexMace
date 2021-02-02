#pragma once
#include "Cw4State.h"
#include "PauseObj.h"

class StatePaused :
	public Cw4State
{
public: 
	StatePaused(Cw4Engine* game);
	~StatePaused();
	virtual void virtSetPause();
};

