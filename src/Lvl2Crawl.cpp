#include "Lvl2Crawl.h"

Lvl2Crawl::Lvl2Crawl(Cw4Engine* game)
	:invisDisplayableObj(game)
{
	setSize(700, 700);
	setPosition(300, 700);
	imgCrawl = ImageManager::loadImage("images/Lvl2Crawl.png", true);
	setVisible(false);
	ticks = 0;
}

void Lvl2Crawl::virtDraw()
{
	if (isVisible()) {
		imgCrawl.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
			m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
			m_iDrawWidth, m_iDrawHeight);

		if (m_iCurrentScreenY == 699) {
			pGame->ImpMarch.pause();
			pGame->MainTheme.load("SFX/MainTheme.wav");
			pGame->MainTheme.play();
		}

		if (ticks > 1300) {
			//change state
			pGame->gameSpeed = 1;
			//press enter to start
			pGame->drawForegroundString(500, 400, "Press enter to start", 0xFFE3B201);
		}
	}
}

void Lvl2Crawl::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible())
		return;

	setPosition(m_iCurrentScreenX, m_iCurrentScreenY - 1);
	ticks++;
}
