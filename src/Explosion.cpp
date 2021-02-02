#include "Explosion.h"

Explosion::Explosion(Cw4Engine* game)
	:invisDisplayableObj(game)
{
	pGame = game;
	setSize(50, 50);
	setPosition(0, 0);
	setVisible(false);
	lastCurrTime = 0;
	expl1 = ImageManager::loadImage("images/Expl1.png", true);
	expl2 = ImageManager::loadImage("images/Expl2.png", true);
	expl3 = ImageManager::loadImage("images/Expl3.png", true);
	expl4 = ImageManager::loadImage("images/Expl4.png", true);
	expl5 = ImageManager::loadImage("images/Expl5.png", true);
}

void Explosion::virtDraw()
{
	if (isVisible()) {
		/*pGame->drawForegroundRectangle(
			m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + getDrawWidth() - 1,
			m_iCurrentScreenY + getDrawHeight() - 1,
			0x0FFA500);
		*/
		switch (imgNum) {
		case 0:
			expl1.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 1:
			expl2.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 3:
			expl4.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		case 4:
			expl5.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			break;
		}
	}
}

void Explosion::virtDoUpdate(int iCurrentTime)
{
	if (isVisible()) {
		if (ticks - lastCurrTime > 30) {
			setVisible(false);
			imgNum = 0;
		}
		if (ticks % 6 == 5)
			imgNum++;
		ticks += pGame->gameSpeed;
		this->redrawDisplay();
	}
	else
		lastCurrTime = ticks;

	

	
	
}

