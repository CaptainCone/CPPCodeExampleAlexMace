#include "Shield.h"

Shield::Shield(Cw4Engine* game)
	:invisDisplayableObj(game)
{
	setVisible(false);
}

void Shield::virtDraw()
{
	if(isVisible()) {
		int xZero = m_iCurrentScreenX;
		int yZero = m_iCurrentScreenY;
		int r = 140;

		double maxAngle = M_PI / 2.1;
		double stepSize = maxAngle / 300;

		for (double i = 0; i < maxAngle; i += stepSize) {
			int x = xZero + (int)(getDrawWidth() / 2 - r * cos(i));
			int y = yZero + (int)(getDrawHeight() / 2 - r * sin(i));
			pGame->setForegroundPixel(x, y, 0x9999FF);
			pGame->setForegroundPixel(x - 1, y, 0x9999FF);
			pGame->setForegroundPixel(x + 1, y, 0x9999FF);
			pGame->setForegroundPixel(x - 2, y, 0x9999FF);
			pGame->setForegroundPixel(x + 2, y, 0x9999FF);
			pGame->setForegroundPixel(x - 1, y - 1, 0x9999FF);
			pGame->setForegroundPixel(x + 1, y + 1, 0x9999FF);
			pGame->setForegroundPixel(x - 2, y - 1, 0x9999FF);
			pGame->setForegroundPixel(x + 2, y + 1, 0x9999FF);
		}
		for (double i = 0; i < maxAngle; i += stepSize) {
			int x = xZero + (int)(getDrawWidth() / 2 - r * cos(i));
			int y = yZero + (int)(getDrawHeight() / 2 + r * sin(i));
			pGame->setForegroundPixel(x, y, 0x9999FF);
			pGame->setForegroundPixel(x - 1, y, 0x9999FF);
			pGame->setForegroundPixel(x + 1, y, 0x9999FF);
			pGame->setForegroundPixel(x - 2, y, 0x9999FF);
			pGame->setForegroundPixel(x + 2, y, 0x9999FF);
			pGame->setForegroundPixel(x - 1, y - 1, 0x9999FF);
			pGame->setForegroundPixel(x + 1, y + 1, 0x9999FF);
			pGame->setForegroundPixel(x - 2, y - 2, 0x9999FF);
			pGame->setForegroundPixel(x + 2, y + 2, 0x9999FF);
		}
	}
}

void Shield::virtDoUpdate(int iCurrentTime)
{
	this->redrawDisplay();
}
