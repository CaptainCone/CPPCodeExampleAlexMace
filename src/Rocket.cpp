#include "Rocket.h"

Rocket::Rocket(Cw4Engine* game)
	:Bullet(game)
{
	pGame = game;
	setSize(30, 30);
	cycle = &(pGame->rocketCycle);
	num = &(pGame->rocketNum);
	MAX = 2;
	setVisible(false);
}

void Rocket::virtDraw()
{
	if (isVisible()) {
		pGame->drawForegroundOval(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + getDrawWidth() - 1,
			m_iCurrentScreenY + getDrawHeight() - 1,
			0xFF0000);
	}
}

double Rocket::virtSetXMoveAmt()
{
	return (pGame->gameSpeed) * 3;
}
