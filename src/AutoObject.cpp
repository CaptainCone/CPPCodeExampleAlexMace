#include "header.h"
#include "AutoObject.h"
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "MovementPosition.h"

AutoObject::AutoObject(BaseEngine* pEngine)
	: DisplayableObject(900, 200, pEngine, 100, 100, true)
{
	bXBounce = false;
	bYBounce = false;
	//move = false;
}

AutoObject::~AutoObject()
{
}

void AutoObject::virtDraw()
{
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0x000000);
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX + 10, m_iCurrentScreenY+10,
		m_iCurrentScreenX + m_iDrawWidth - 10,
		m_iCurrentScreenY + m_iDrawHeight - 10,
		0xFFFFFF);
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX + abs(speed/3) + 20 , m_iCurrentScreenY + abs(speed/3) + 20,
		m_iCurrentScreenX + m_iDrawWidth - abs(speed/3) - 20,
		m_iCurrentScreenY + m_iDrawHeight - abs(speed/3) - 20,
		0x000000);
}

void AutoObject::virtDoUpdate(int iCurrentTime)
{
	//static int X=0, Y=0;
	if (move) {
		X = X + 2;// iCurrentTime % (getEngine()->getWindowWidth() * 10);
		Y = Y + (speed/3); 
		speed += 1;// iCurrentTime % (getEngine()->getWindowHeight() * 20);
	}
	if (X > getEngine()->getWindowWidth())
		X = -100;
	if (Y > getEngine()->getWindowHeight())
		speed = -speed-1;
	m_iCurrentScreenX =  X;
	m_iCurrentScreenY = Y;
	redrawDisplay();
}
