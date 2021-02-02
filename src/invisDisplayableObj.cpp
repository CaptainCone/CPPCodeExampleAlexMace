#include "invisDisplayableObj.h"

invisDisplayableObj::invisDisplayableObj(Cw4Engine* game)
	:DisplayableObject(game)
{
	pGame = game;
	lastCurrTime = 0;
}


void invisDisplayableObj::setExplode(bool b)
{
	explode = b;
}

bool invisDisplayableObj::getExplode()
{
	return explode;
}

void invisDisplayableObj::virtDoUpdate(int iCurrentTime)
{
	redrawDisplay();
}

void invisDisplayableObj::setDefaultPos(int x, int y)
{
	if (x == 0 && y == 0) {
		return;
	}

	ticks = 0;
	this->setVisible(true);
}
