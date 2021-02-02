#include "StarDestroyer.h"
#include <string>
#include <iostream>

StarDestroyer::StarDestroyer(Cw4Engine* game, Explosion* expl, Shield* shld)
	:BasicEnemy(game, expl)
{
	setSize(220, 75);
	//setPosition(700, 100);
	//setVisible(true);
	hp = 10;
	pShield = shld;
	//timeLastShot = 0;
	SD1 = ImageManager::loadImage("images/StarDestroyer1.png", true);
	SD2 = ImageManager::loadImage("images/StarDestroyer2.png", true);
}

void StarDestroyer::virtDraw()
{
	if (isVisible()) {
		if (ticks % 20 > 10) {
			SD1.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
		}
		else {
			SD2.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
		}
	}
}

void StarDestroyer::virtDoUpdate(int iCurrentTime)
{
	if (!getActive() || !isVisible())
		return;

	if (hp <= 0 && lvl1) {
		pGame->endLvl1();
		pShield->setVisible(false);
	}

	if (hp <= 0 && !lvl1) {
		if (yStart == 301 && pGame->DS3)
			setDefaultPos(xStart, yStart);
		else if (yStart == 550 && pGame->DS4)
			setDefaultPos(xStart, yStart);
		else
			setDefaultPos(0, 0);
	}


	if (pGame->TIENum == 0) {
		timeShldDown++;
		pShield->setVisible(false);
	}

	if (timeShldDown > 500 && lvl1) {
		drawShield();
		pGame->TIENum = 8;
		timeShldDown = 0;
	}

	if (ticks == 0 && lvl1) {
		pGame->MainTheme.pause();
		pGame->ImpMarch.load("SFX/ImperialMarch.wav");
		pGame->ImpMarch.play();
	}

	srand(iCurrentTime);

	if (ticks < 500)
		setPosition(m_iCurrentScreenX - pGame->gameSpeed, m_iCurrentScreenY);

	if (ticks == 500 && lvl1)
		drawShield();

	if (ticks > 500 && ticks % 400 == 0) {
		pGame->shootAtPlayer(m_iCurrentScreenX-10, m_iCurrentScreenY + getDrawHeight() - 20);
	}

	if (
		checkRectangle(m_iCurrentScreenX + 155, m_iCurrentScreenY,
			m_iCurrentScreenX + 180, m_iCurrentScreenY + 30) ||
		checkTriangle(m_iCurrentScreenX, m_iCurrentScreenY + 65,
			m_iCurrentScreenX + 200, m_iCurrentScreenY + 75,
			m_iCurrentScreenX + 200, m_iCurrentScreenY + 40)
		)
	{
		if (ticks % 5 == 0) {
			doExplosion(expX, expY-25);
			hp--;
		}
	}

	ticks += pGame->gameSpeed;
}

void StarDestroyer::drawShield()
{
	pShield->setPosition(m_iCurrentScreenX, m_iCurrentScreenY);
	pShield->setSize(getDrawWidth(), getDrawHeight());
	pShield->setVisible(true);
}

void StarDestroyer::setDefaultPos(int x, int y)
{
	if (x == 0 && y == 0) {
		setActive(false);
		setVisible(false);
		pShield->setVisible(false);
		return;
	}
	if (x == 1401) {
		lvl1 = false;
	}
	xStart = x;
	yStart = y;
	setPosition(x, y);
	setActive(true);
	ticks = 0;
	if (y == 301)
		ticks = -100;
	thisX = 0;
	thisY = 0;
	setVisible(true);
	pShield->setVisible(false);
	hp = 10;
}
