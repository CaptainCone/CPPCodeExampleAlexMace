#pragma once
#include "invisDisplayableObj.h"
class PauseObj :
	public invisDisplayableObj
{
	public:
		PauseObj(Cw4Engine* game);
		void virtDraw();
		void virtDoUpdate();

	protected:
		Cw4Engine* pGame;
};

