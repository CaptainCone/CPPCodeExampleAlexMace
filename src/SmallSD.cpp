#include "SmallSD.h"
#include "Shield.h"

SmallSD::SmallSD(Cw4Engine* game, Explosion* expl)
	:StarDestroyer(game, expl, new Shield(game))
{
	setSize(200, 150);
	//setPosition(700, 100);
	//setVisible(true);
	hp = 10;
	//pShield = shld;
	//timeLastShot = 0;
	smallSD1 = ImageManager::loadImage("images/SmallSD1.png", true);
	smallSD2 = ImageManager::loadImage("images/SmallSD2.png", true);
}

void SmallSD::virtDraw()
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

void SmallSD::virtDoUpdate(int iCurrentTime)
{
	if (!getActive() || !isVisible())
		return;

	srand(iCurrentTime);

	if (ticks < 500)
		setPosition(m_iCurrentScreenX - pGame->gameSpeed, m_iCurrentScreenY);

	if (ticks > 500 && ticks % 400 == 0) {
		pGame->shootAtPlayer(m_iCurrentScreenX, m_iCurrentScreenY + getDrawHeight());
	}

	if (
		checkRectangle(m_iCurrentScreenX + (int)(getDrawWidth() / 1.4), m_iCurrentScreenY,
			m_iCurrentScreenX + getDrawWidth(), m_iCurrentScreenY + (int)(getDrawHeight() / 4)) ||
		checkTriangle(m_iCurrentScreenX, m_iCurrentScreenY + getDrawHeight(),
			m_iCurrentScreenX + getDrawWidth(), m_iCurrentScreenY + getDrawHeight(),
			m_iCurrentScreenX + getDrawWidth(), m_iCurrentScreenY + (int)(getDrawHeight() / 4))
		)
	{
		if (ticks % 400 > 5) { // stops shooting self/ doesn't check for 5 ticks
			doExplosion(expX, expY);
			hp -= 1;
		}
	}

	ticks += pGame->gameSpeed;
}