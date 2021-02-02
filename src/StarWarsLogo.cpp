#include "StarWarsLogo.h"
#include "DrawingFilters.h"
#include "MyFilterPScaling.h"

StarWarsLogo::StarWarsLogo(Cw4Engine* game)
	:invisDisplayableObj(game)
{
	Logo = ImageManager::loadImage("images/Logo.png", true);
	Lvl1Crawl = ImageManager::loadImage("images/Lvl1Crawl.png", true);
	setSize(680, 700);
	setPosition(300, 200);
	setVisible(false);
}

StarWarsLogo::~StarWarsLogo()
{
	//delete fps;
}

void StarWarsLogo::virtDraw()
{
	if (isVisible()) {
		if (ticks == 40) {
			pGame->WinMusic.pause();
			pGame->MainTheme.load("SFX/MainTheme.wav");
			pGame->MainTheme.play();
		}

		if (ticks > 40 && ticks < 150) {
			int mv = 5;
			if (ticks > 70) {
				mv = 8;
			}
			if (ticks > 100) {
				mv = 11;
			}
			setPosition(m_iCurrentScreenX + mv, m_iCurrentScreenY - 8);
			Logo.renderImageWithMask(
				getEngine()->getForegroundSurface(),
				0, 0,
				m_iCurrentScreenX + m_iStartDrawPosX,
				m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			static double msx = 1;
			static double msy = 1;
			static double add = 0.005;
			
			MyFilterPScaling* fps = new MyFilterPScaling(msx, msy);
			for (sx = 0; sx < 1299; sx++) {
				for (sy = 0; sy < 749; sy++) {
					int& x = sx;
					int& y = sy;
					if (pGame->rawGetForegroundPixel(x, y) == 0xFFE3B201) {
						unsigned int col = pGame->rawGetForegroundPixel(x, y);
						unsigned int& rcol = col;
						pGame->lockForegroundForDrawing();
						fps->filter(pGame->getForegroundSurface(), x, y, rcol);
						pGame->rawSetForegroundPixel(x, y, 0x00000000);
						pGame->unlockForegroundForDrawing();
					}
				}
			}
			msx += add;
			msy += add;
			add += 0.0002;

			for (int i = 0; i < pGame->getWindowHeight(); i++)
				pGame->setForegroundPixel(pGame->getWindowWidth() - 1, i, 0x000000);
			
			delete fps;
		}

		if (ticks > 150 && ticks < 1450) {
			static int yPos = pGame->getWindowHeight();
			Lvl1Crawl.renderImageWithMask(
				getEngine()->getForegroundSurface(),
				0, 0,
				300 + m_iStartDrawPosX,
				yPos + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
			yPos--;
		}

		if (ticks > 1450) {
			//change state
			pGame->gameSpeed = 1;
			//press enter to start

			pGame->drawForegroundString(500, 400, "Press enter to start", 0xFFE3B201);
		}

	
	}
}


void StarWarsLogo::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible())
		return;

	ticks++;
	this->redrawDisplay();
}
