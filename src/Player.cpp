#include "Player.h"

Player::Player(Cw4Engine* game, Explosion* exp)
	:invisDisplayableObj(game)
{
	expl = exp;
	pGame = game;
	setSize(135, 100);
	setPosition(200, 400);
	setVisible(false);
	falcon = ImageManager::loadImage("images/Falcon.png", true);
}


void Player::virtDraw()
{
	if (isVisible()) {
		
	pGame->drawForegroundOval(m_iCurrentScreenX, m_iCurrentScreenY,
			m_iCurrentScreenX + 100, m_iCurrentScreenY + 100, 0x000000);

	falcon.renderImageWithMask(getEngine()->getForegroundSurface(), 0, 0,
		m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY,
		m_iDrawWidth, m_iDrawHeight);

	}
}


void Player::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible())
		return;

	int mvSpeed = pGame->gameSpeed * 2;
	if (pGame->isKeyPressed(SDLK_UP) || pGame->isKeyPressed(SDLK_w))
		setPosition(m_iCurrentScreenX, m_iCurrentScreenY - mvSpeed);
	if (pGame->isKeyPressed(SDLK_DOWN) || pGame->isKeyPressed(SDLK_s))
		setPosition(m_iCurrentScreenX, m_iCurrentScreenY + mvSpeed);
	if (pGame->isKeyPressed(SDLK_LEFT) || pGame->isKeyPressed(SDLK_a))
		setPosition(m_iCurrentScreenX - mvSpeed, m_iCurrentScreenY);
	if (pGame->isKeyPressed(SDLK_RIGHT)|| pGame->isKeyPressed(SDLK_d))
		setPosition(m_iCurrentScreenX + mvSpeed, m_iCurrentScreenY);

	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= 400)
		m_iCurrentScreenX = 400;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= pGame->getWindowHeight() - getDrawHeight())
		m_iCurrentScreenY = pGame->getWindowHeight() - getDrawHeight();

	//check for explosion
	if (checkFalcon()) {
		doExplosion(expX - 25, expY - 25);
		health -= 10;
	}

	if (health <= 0 && isVisible()) {
		pGame->loadScoreBoard();
		pGame->playerHP = 0;
	}

	this->redrawDisplay();
	ticks += pGame->gameSpeed;
}

bool Player::checkFalcon()
{
	if (checkCircle(m_iCurrentScreenX + 50, m_iCurrentScreenY + 50, 50))
		return true;
	if (checkTriangle(
		m_iCurrentScreenX + 85, m_iCurrentScreenY + 15,
		m_iCurrentScreenX + 135, m_iCurrentScreenY + 42,
		m_iCurrentScreenX + 85, m_iCurrentScreenY + 42))
		return true;
	if (checkTriangle(
		m_iCurrentScreenX + 85, m_iCurrentScreenY + 55,
		m_iCurrentScreenX + 135, m_iCurrentScreenY + 55,
		m_iCurrentScreenX + 85, m_iCurrentScreenY + 78))
		return true;
	if (checkRectangle(
		m_iCurrentScreenX + 80, m_iCurrentScreenY + 82,
		m_iCurrentScreenX + 115, m_iCurrentScreenY + 95))
		return true;

	return false;
}

void Player::setTimeShot()
{
	timeLastShot = ticks;
}

bool Player::checkPixel(int x, int y)
{
	unsigned int col = 0xFF0000FF;
	unsigned int col3 = 0xFF00FF00;
	unsigned int col2 = 0xFF41EB47; //laser colour
	unsigned int forg = pGame->rawGetForegroundPixel(x, y);
	//std::cout << ticks << " " << timeLastShot;
	if ((ticks - timeLastShot) > 20) {
		
		if (forg == col2) {
			expX = x;
			expY = y;
			return true;
		}
	}
	static int timeLastLaser = 0;
	if (ticks - timeLastLaser > 20) {
		if (forg == col3) {
			expX = x;
			expY = y;
			timeLastLaser = ticks;
			return true;
		}
	}

	if (forg == col) {
		expX = x;
		expY = y;
		return true;
	}
	return false;
}

bool Player::checkRectangle(int x1, int y1, int x2, int y2)
{
	if (checkLine(x1, y1, x1, y2) ||
		checkLine(x1, y2, x2, y2) ||
		checkLine(x2, y2, x2, y1) ||
		checkLine(x2, y1, x1, y1))
		return true;

	return false;
}

bool Player::checkCircle(int x, int y, int r)
{
	double numSteps = 300;
	double stepSize = (2 * M_PI) / numSteps;
	for (int i = 0; i < numSteps; i++)
		if (checkPixel((int)(x + r * sin(i * stepSize)), (int)(y + r * cos(i * stepSize))))
			return true;

	return false;
}

bool Player::checkTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (checkLine(x1, y1, x2, y2) ||
		checkLine(x2, y2, x3, y3) ||
		checkLine(x1, y1, x3, y3))
		return true;

	return false;
}

bool Player::checkLine(int x1, int y1, int x2, int y2)
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

void Player::doExplosion(int x, int y)
{
	expl->setPosition(x, y);
	expl->setVisible(true);
}
