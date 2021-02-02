#include "Bullet.h"

Bullet::Bullet(Cw4Engine* game)
	:MappableImageObject(&rotator, 0, 0, game, "LaserImage.png", false), rotator(0.0)
{
	pGame = game;
	cycle = 0;
	num = 0;
	setPosition(0, 1);
}

void Bullet::virtDoUpdate(int iCurrentTime)
{
	currTime = iCurrentTime;

	if (shot) { //stops moving when off screen
		thisX += xMvAmt * pGame->gameSpeed;
		thisY += yMvAmt * pGame->gameSpeed;
		m_iCurrentScreenX = (int)thisX;
		m_iCurrentScreenY = (int)thisY;

		if (m_iCurrentScreenX > pGame->getWindowWidth()     || 
			m_iCurrentScreenY > pGame->getWindowHeight()    ||
			m_iCurrentScreenX < 0                           ||
			m_iCurrentScreenY < 0                           ||
			checkPixel(m_iCurrentScreenX,m_iCurrentScreenY))
		{
			(*num)--;
			if (*cycle > MAX) { *cycle = 0; }
			setPosition(0, 0);
			thisX = 0;
			thisY = 1;
			setShot(false);
			setVisible(false);
		}
	}
	this->redrawDisplay();
}


void Bullet::setShot(bool b)
{
	shot = b;
	if (b == true) {
		timeLastShot = currTime;
		thisX = m_iCurrentScreenX;
		thisY = m_iCurrentScreenY;
		xMvAmt = this->virtSetXMoveAmt();
		yMvAmt = this->virtSetYMoveAmt();
	}
}

bool Bullet::checkPixel(int x, int y)
{
	unsigned int explosionCol = 0xFFFF6F00; //explosion colour
	unsigned int shieldCol = 0xFF9999FF;
	unsigned int forg = pGame->rawGetForegroundPixel(x+1, y + getDrawHeight() /2);
	unsigned int forg2 = pGame->rawGetForegroundPixel(x + getDrawWidth()/2, y + getDrawHeight() / 2);
	if(currTime - timeLastShot > 300) // so star destroyer can shoot through own shield
		if (forg == shieldCol || forg2 == shieldCol)
			return true;
	
	for (int i = -30; i < getDrawHeight() + 30; i++) {
		for (int j = -30; j < getDrawWidth() + 30; j++) {
			unsigned int forg3 = pGame->rawGetForegroundPixel(x + j, y + i);
			if (forg3 == explosionCol)
				return true;
		}
	}

	return false;
}

