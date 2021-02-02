#include "PauseObj.h"

PauseObj::PauseObj(Cw4Engine* game)
	:invisDisplayableObj(game)
{
	pGame = game;
	setVisible(false);
}

void PauseObj::virtDraw()
{
	if (m_bVisible) {
		pGame->drawForegroundRectangle(575, 300, 625, 500, 0xFFFFFF);
		pGame->drawForegroundRectangle(675, 300, 725, 500, 0xFFFFFF);
	}
}

void PauseObj::virtDoUpdate()
{
	redrawDisplay();
}