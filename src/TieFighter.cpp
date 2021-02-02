#include "TieFighter.h"
#include <ctime>

TieFighter::TieFighter(Cw4Engine* game, Explosion* expl)
	:BasicEnemy(game, expl)
{
	setSize(50, 50);
	setPosition(0, 0);
	setVisible(false);
	srand(time(NULL));
	setDefaultColour(0x666666);
	TIE = ImageManager::loadImage("images/TIENormal.png", true);
	TieFire1 = ImageManager::loadImage("images/TieFire1.png", true);
	TieFire2 = ImageManager::loadImage("images/TieFire2.png", true);
	TieFire3 = ImageManager::loadImage("images/TieFire3.png", true);
	TieFire4 = ImageManager::loadImage("images/TieFire4.png", true);
	hp = 2;
}

void TieFighter::virtDraw()
{
	if (isVisible()) {
		switch (imgNum) {
		case 0:
			TIE.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0, 
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, 
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 1:
			TieFire1.renderImageWithMask(
				getEngine()->getForegroundSurface(), 0, 0, 
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, 
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 2:
			TieFire2.renderImageWithMask(
				getEngine()->getForegroundSurface(), 0, 0, 
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, 
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 3:
			TieFire3.renderImageWithMask(
				getEngine()->getForegroundSurface(), 0, 0, 
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, 
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 4:
			TieFire4.renderImageWithMask(
				getEngine()->getForegroundSurface(), 0, 0, 
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, 
				m_iDrawWidth, m_iDrawHeight);
			break;
		}
	}
}

void TieFighter::virtDoUpdate(int iCurrentTime)
{
	if (!getActive())// || !isVisible())
		return;

	srand(iCurrentTime + m_iCurrentScreenX);

	if (pGame->TIENum > 4) {
		ticks = 500;
		pGame->TIENum -= 1;
		imgNum = 0;
	}

	if (ticks == 550) {
		setAngle(m_iCurrentScreenX, m_iCurrentScreenY, destX, destY);
		xMvAmt = setXMoveAmt() * 2;
		yMvAmt = setYMoveAmt() * 2;
		setVisible(true);
		thisX = m_iCurrentScreenX;
		thisY = m_iCurrentScreenY;
	}

	if (ticks > 550) {
		thisX += xMvAmt * pGame->gameSpeed;
		thisY += yMvAmt * pGame->gameSpeed;
		setPosition((int)thisX, (int)thisY);
	}

	if (destY < 400) {
		if (m_iCurrentScreenY < destY) {
			xMvAmt = 0;
			yMvAmt = 0;
		}
	}
	else {
		if (m_iCurrentScreenY > destY) {
			xMvAmt = 0;
			yMvAmt = 0;
		}
	}

	if (ticks > 850 && pGame->gameSpeed > 0 && isVisible() && (rand() % 250) == 0) {
		pGame->shootLeft(m_iCurrentScreenX - 30, m_iCurrentScreenY + 25);
	}
	if (isVisible()) {
		if (
			checkRectangle(m_iCurrentScreenX, m_iCurrentScreenY,
				m_iCurrentScreenX + getDrawWidth(), m_iCurrentScreenY + getDrawHeight())
			)
		{
			if (ticks % 3 == 0) { //so make sure only 1 hp is lost
				doExplosion(m_iCurrentScreenX, m_iCurrentScreenY);
				hp--;
			}
		}
	}

	if (hp < 2) {
		if( ticks % 8 == 0 )
			imgNum++;
		if (imgNum > 4)
			imgNum = 1;
	}

	if (hp <= 0) {
		setPosition(xStart, yStart);
		hp = 2; //reset
		xMvAmt = 0;
		yMvAmt = 0;
		thisX = xStart;
		thisY = yStart;
		//setActive(false);
		setVisible(false);
		pGame->TIENum -= 1;
		int score;
		score = 1000 - (ticks / 2);
		if (score > 50)
			pGame->score += score;
		else
			pGame->score += 50;
	}

	ticks += pGame->gameSpeed;
}

void TieFighter::flyToPos(int x, int y)
{
	destX = x;
	destY = y;
}

void TieFighter::setDefaultPos(int x, int y)
{
	if (x == 0 && y == 0) {
		setActive(false);
		setVisible(false);
		return;
	}
	xStart = x;
	yStart = y;
	setPosition(x, y);
	setActive(true);
	ticks = 0;
	thisX = 0;
	thisY = 0;
	setVisible(false);
	hp = 2;
	imgNum = 0;
}