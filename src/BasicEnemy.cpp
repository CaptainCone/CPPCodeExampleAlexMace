#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(Cw4Engine* game, Explosion* expl)
	:invisDisplayableObj(game)
{
	pGame = game;
	setVisible(false);
	setExplode(false);
	exp = expl;
	hp = 10;
}

bool BasicEnemy::checkPixel(int x, int y)
{
	unsigned int col = 0xFFFF0000; //rocket colour
	unsigned int col2 = 0xFF41EB47; //laser colour
	unsigned int forg = pGame->rawGetForegroundPixel(x, y);

	if (forg == col || forg == col2) {
		expX = x;
		expY = y;
		return true;
	}
	return false;
}

bool BasicEnemy::checkRectangle(int x1, int y1, int x2, int y2)
{
	if (checkLine(x1, y1, x1, y2) ||
		checkLine(x1, y2, x2, y2) ||
		checkLine(x2, y2, x2, y1) ||
		checkLine(x2, y1, x1, y1))
		return true;

	return false;
}

bool BasicEnemy::checkCircle(int x, int y, int r)
{
	double numSteps = 300;
	double stepSize = (2 * M_PI) / numSteps;
	for(int i=0; i<numSteps; i++)
		if(checkPixel((int)(x + r*sin(i*stepSize)), (int)(y + r*cos(i*stepSize))))
			return true;

	return false;
}

bool BasicEnemy::checkTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (checkLine(x1, y1, x2, y2) ||
		checkLine(x2, y2, x3, y3) ||
		checkLine(x1, y1, x3, y3))
		return true;
	
	return false;
}

bool BasicEnemy::checkLine(int x1, int y1, int x2, int y2)
{
	int numSteps;

	int xDiff = abs(x1 - x2);
	int yDiff = abs(y1 - y2);

	if (xDiff > yDiff)
		numSteps = xDiff;
	else
		numSteps = yDiff;

	int xStep = (x1 - x2) / numSteps;
	int yStep = (y1 - y2) / numSteps;

	for (int i = 0; i < numSteps; i++)
		if (checkPixel(x2 + (i * xStep), y2 + (i * yStep)))
			return true;

	return false;
}

void BasicEnemy::doExplosion(int x, int y)
{
	exp->setPosition(x, y);
	//exp->setSize(getDrawWidth(), getDrawHeight());
	exp->setVisible(true);
}

void BasicEnemy::setDefaultPos(int x, int y)
{
	xStart = x;
	yStart = y;
	setPosition(x, y);
	setActive(true);
	ticks = 0;
	thisX = 0; 
	thisY = 0;
	setVisible(false);
}

double BasicEnemy::setXMoveAmt()
{
	double x = pGame->gameSpeed * sin(angleFrom12);
	if (angleFrom12 < 180)
		return x;
	return -x;
}

double BasicEnemy::setYMoveAmt()
{
	double y = pGame->gameSpeed * cos(angleFrom12);
	if (angleFrom12 > 90 && angleFrom12 < 270)
		return y;
	return -y;
}

void BasicEnemy::setAngle(int x1, int y1, int x2, int y2)
{
	double x = abs(x1 - x2);
	double y = abs(y1 - y2);
	double angle = atan(x / y);

	if (x2 > x1&& y2 < y1)
		angleFrom12 = angle;
	else if (x2 > x1)
		angleFrom12 = M_PI - angle;
	else if (y2 > y1&& x1 > x2)
		angleFrom12 = angle + M_PI;
	else
		angleFrom12 = (2 * M_PI) - angle;
}

