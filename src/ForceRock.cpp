#include "ForceRock.h"
#include <ctime>

ForceRock::ForceRock(Cw4Engine* game,Explosion* expl)
	:BasicEnemy(game, expl)
{
	setSize(50, 50);
	randX = rand() % 500 + 300;
	hp = 10;

	rock1 = ImageManager::loadImage("images/Rock1.png", true);
	rock2 = ImageManager::loadImage("images/Rock2.png", true);
	rock3 = ImageManager::loadImage("images/Rock3.png", true);
	rock4 = ImageManager::loadImage("images/Rock4.png", true);
	rock5 = ImageManager::loadImage("images/Rock5.png", true);
	rock6 = ImageManager::loadImage("images/Rock6.png", true);

}

void ForceRock::virtDraw()
{
	if (isVisible()) {

		if (getGlow()) {
			pGame->drawForegroundOval(
				m_iCurrentScreenX-3 , m_iCurrentScreenY-2,
				m_iCurrentScreenX + getDrawWidth(),
				m_iCurrentScreenY + getDrawHeight(),
				0x0000FF);
			if (ticks % 5 == 0) {
				imgNum += pGame->gameSpeed;
				if (imgNum > 5)
					imgNum = 0;
			}
		}
		switch (imgNum) {
		case 0:
			rock1.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 1:
			rock2.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 2:
			rock3.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 3:
			rock4.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 4:
			rock5.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 5:
			rock6.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		}
		//pGame->drawForegroundOval(
			//m_iCurrentScreenX, m_iCurrentScreenY,
			//m_iCurrentScreenX + m_iDrawWidth,
			//m_iCurrentScreenY + m_iDrawHeight,
			//0xAAAAAA);
	}
}

void ForceRock::virtDoUpdate(int iCurrentTime)
{
	if (!getActive())// || !isVisible())
		return;

	if (checkForceRock()) {
		setPosition(xStart, yStart);
		thisX = xStart;
		thisY = yStart;
		setForceThrow(true);
	}

	srand(iCurrentTime + m_iCurrentScreenX);
	
	if (!getGlow() && ticks == 0) {
		moveTick = rand() % 700;
		glowTick = rand() % 200 + moveTick + 300;
		thisX = xStart;
		thisY = yStart;
	}

	if (ticks == moveTick) {
		setAngle(getXCentre(), getYCentre(), randX, 500);
		xMvAmt = setXMoveAmt() / 1.5;
		yMvAmt = setYMoveAmt() / 1.5;
	}

	if (ticks == glowTick) {
		setGlow(true);
		xMvAmt = 0;
		yMvAmt = 0;
	}

	if (ticks == glowTick + 150) {
		setForceThrow(true);
		setAngle(getXCentre(), getYCentre(), pGame->getPlayerX(), pGame->getPlayerY());
		xMvAmt = setXMoveAmt() * 5;
		yMvAmt = setYMoveAmt() * 5;
	}

	thisX += xMvAmt * pGame->gameSpeed;
	thisY += yMvAmt * pGame->gameSpeed;
	setPosition((int)thisX, (int)thisY);

	if (checkCircle(m_iCurrentScreenX + getDrawWidth() / 2, m_iCurrentScreenY + getDrawHeight() / 2, getDrawHeight() / 2))
	{
		doExplosion(m_iCurrentScreenX, m_iCurrentScreenY);
		setPosition(xStart, yStart);
		thisX = xStart;
		thisY = yStart;
		setForceThrow(true);
		pGame->changePlayerHP(3);
		//setGlow(false);//to let reset happen
	}

	if (getForceThrow()) {
		if (m_iCurrentScreenX < -49 ||
			m_iCurrentScreenY < -49 ||
			m_iCurrentScreenX >= pGame->getWindowWidth() ||
			m_iCurrentScreenY >= pGame->getWindowHeight()) {
			setPosition(xStart, yStart);
			setForceThrow(false);
			setGlow(false);
			randX = rand() % 700 + 300;
			setAngle(getXCentre(), getYCentre(), randX, 500);
			xMvAmt = 0;
			yMvAmt = 0;
			ticks = 0;
			imgNum = 0;
			return;
		}
	}

	ticks += pGame->gameSpeed;
}

bool ForceRock::checkForExpl(int x, int y)
{
	unsigned int explosionCol = 0xFFFF6F00;
	unsigned int forg = pGame->rawGetForegroundPixel(x, y);

	if (explosionCol == forg)
		return true;

	return false;
}

bool ForceRock::checkForceRock()
{
	int x = getXCentre();
	int y = getYCentre();
	int r = 25;
	double numSteps = 300;
	double stepSize = (2 * M_PI) / numSteps;
	for (int i = 0; i < numSteps; i++)
		if (checkForExpl((int)(x + r * sin(i * stepSize)), (int)(y + r * cos(i * stepSize))))
			return true;

	return false;
}

void ForceRock::setDefaultPos(int x, int y)
{
	if (x == 0 && y == 0) {
		setActive(false);
		setVisible(false);
		return;
	}
	xStart = x;
	yStart = y;
	setPosition(xStart, yStart);
	setActive(true);
	setVisible(true);
	ticks = 0;
	thisX = x;
	thisY = y;
	setGlow(false);
	setForceThrow(false);
	xMvAmt = 0;
	yMvAmt = 0;
}