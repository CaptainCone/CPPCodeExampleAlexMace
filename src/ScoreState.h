#pragma once
#include "Cw4State.h"
class ScoreState :
	public Cw4State
{
public:
	ScoreState(Cw4Engine* game);
	~ScoreState();
	void enterPress();
};

