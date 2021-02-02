#include "Laser.h"
#include "SimpleTrig.h"

Laser::Laser(Cw4Engine* game)
	:Bullet(game)
{
	//setPosition(0, 0);
	pGame = game;
	cycle = &(pGame->laserCycle);
	num = &(pGame->laserNum);
	MAX = 9;
	image = ImageManager::loadImage("Images/LaserImage1.png", true);
	setVisible(false);
}

double Laser::virtSetXMoveAmt()
{
	double x = 5 * (double)(pGame->gameSpeed) * sin(angleFrom12);
	if (angleFrom12 < 180)
		return x;
	return -x;
}

double Laser::virtSetYMoveAmt()
{
	double y = 5 * (double)(pGame->gameSpeed) * cos(angleFrom12);
	if (angleFrom12 > 90 && angleFrom12 < 270)
		return y;
	return -y;
}

void Laser::virtDraw()
{
	if (isVisible()) {
		image.renderImageApplyingMapping(getEngine(), getEngine()->getForegroundSurface(),
			m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, image.getWidth(), image.getHeight(),
			m_pMapping);
	}
}

void Laser::setAngle(int x1, int y1, int x2, int y2)
{
	double x = abs(x1 - x2);
	double y = abs(y1 - y2); 
	double angle = atan(x/y);
	
	if (x2 > x1 && y2 < y1)
		angleFrom12 = angle;
	else if (x2 > x1)
		angleFrom12 = M_PI - angle;
	else if (y2 > y1 && x1 > x2)
		angleFrom12 = angle + M_PI;
	else
		angleFrom12 = (2*M_PI) - angle;

	rotator.setRotation(1.5*M_PI-angleFrom12);
	SimpleImage& img = image;
	double x3 = (double)image.getWidth() - 1;
	double& xr = x3;
	double y3 = (double)image.getHeight() - 1;
	double& yr = y3;
	bool b = rotator.mapCoordinates(xr, yr, img); //only does this once to make it more efficient
}
