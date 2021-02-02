#pragma once
#include "Cw4State.h"
#include "SimpleImage.h"

class StartUpState :
	public Cw4State
{
public:
	StartUpState(Cw4Engine* game);
	virtual void enterPress();
};

