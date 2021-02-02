#include "currScore.h"

currScore::currScore(Cw4Engine* game)
	:invisDisplayableObj(game)
{
	setVisible(false);
}

void currScore::virtDraw()
{
	if (isVisible()) {
		char buf[128];
		sprintf(buf, "%d", pGame->score);
		pGame->drawForegroundRectangle(10, 10, 150, 50, 0x333333);
		pGame->drawForegroundString(20, 20, buf, 0xE3B201);
		pGame->drawForegroundRectangle(10, 50, hBar+5, 60, 0x00EE00);
		pGame->drawForegroundRectangle(hBar, 50, 150, 60, 0xEE0000);
	}
}

void currScore::virtDoUpdate(int iCurrentTime)
{
	health = pGame->playerHP;
	hBar = health;
}
