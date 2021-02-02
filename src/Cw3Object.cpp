#include "header.h"
#include "Cw3Object.h"
#include "PpyajmaTileManager.h"
#include "PpyajmaEngine.h"
#include "CollisionDetection.h"
#include "AutoObject.h"


Cw3Object::Cw3Object(BaseEngine* pEngine, PpyajmaTileManager* pTileManager, AutoObject* myAuto)
	: DisplayableObject(500, 200, pEngine, 100, 100, true)
{
	obTileManager = pTileManager;
	obMyAuto = myAuto;
	m_iLastUpdatedTime = 0;
}

Cw3Object::~Cw3Object()
{
}


void Cw3Object::virtDraw()
{
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x5045AA);

	getEngine()->drawForegroundString(m_iCurrentScreenX, m_iCurrentScreenY + 20, "Moving", 0x000000);
	getEngine()->drawForegroundString(m_iCurrentScreenX + 5, m_iCurrentScreenY + 50, "test", 0x000000);

}


void Cw3Object::virtDoUpdate(int iCurrentTime)
{
	if (getEngine()->isKeyPressed(SDLK_UP))
		m_iCurrentScreenY -= 2;
	if (getEngine()->isKeyPressed(SDLK_DOWN))
		m_iCurrentScreenY += 4;
	if (getEngine()->isKeyPressed(SDLK_LEFT))
		m_iCurrentScreenX -= 2;
	if (getEngine()->isKeyPressed(SDLK_RIGHT))
		m_iCurrentScreenX += 4;
	if (getEngine()->isKeyPressed(SDLK_SPACE)) { //resets position
		m_iCurrentScreenX = 500;
		m_iCurrentScreenY = 200;
	}
	
	if (m_iCurrentScreenX < 0)
		m_iCurrentScreenX = 0;
	if (m_iCurrentScreenX >= getEngine()->getWindowWidth() - m_iDrawWidth)
		m_iCurrentScreenX = getEngine()->getWindowWidth() - m_iDrawWidth;
	if (m_iCurrentScreenY < 0)
		m_iCurrentScreenY = 0;
	if (m_iCurrentScreenY >= getEngine()->getWindowHeight() - m_iDrawHeight)
		m_iCurrentScreenY = getEngine()->getWindowHeight() - m_iDrawHeight;
	
	int i = m_iCurrentScreenX;
	int j = m_iCurrentScreenY;
	for (i = m_iCurrentScreenX; i < m_iCurrentScreenX + m_iDrawWidth; i=i+5) { //currently causes slowdown. Need to work on efficiency
		for (j = m_iCurrentScreenY; j < m_iCurrentScreenY + m_iDrawHeight; j=j+5) {
			//printf("%d%d\n", i, j);
			//if (iCurrentTime > m_iLastUpdatedTime + 1) {
				//printf("2");
				if (obTileManager->isValidTilePosition(i, j))
				{
					//printf("3");
					m_iLastUpdatedTime = iCurrentTime;
					int iTileX = obTileManager->getMapXForScreenX(i);
					int iTileY = obTileManager->getMapYForScreenY(j);
					int iCurrentTile = obTileManager->getMapValue(iTileX, iTileY);
					obTileManager->setAndRedrawMapValueAt(iTileX, iTileY, iCurrentTile + rand(), getEngine(), getEngine()->getBackgroundSurface());

				}
			//}
		}
	}

	if (CollisionDetection::checkCircles(this->getXCentre(), this->getYCentre(), (*obMyAuto).getXCentre(), (*obMyAuto).getYCentre(), 100)) {
		(*obMyAuto).move = false;
	}
	else {
		(*obMyAuto).move = true;
	}
	// Ensure that the objects get redrawn on the display
	this->redrawDisplay();
}
