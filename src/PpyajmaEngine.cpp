#include "header.h"
#include "PpyajmaEngine.h"
#include "Cw3Object.h"
#include "AutoObject.h"


PpyajmaEngine::PpyajmaEngine()
{
	offset = 0;
}

PpyajmaEngine::~PpyajmaEngine()
{
}

void PpyajmaEngine::virtSetupBackgroundBuffer()
{

	fillBackground(0x000000); //in case some pixel doesn't set
	for (int iX = 0; iX < getWindowWidth(); iX++)
		for (int iY = 0; iY < this->getWindowHeight(); iY++) {
			int i = ((iX+offset) % 70);
			if (i < 10)
				setBackgroundPixel(iX, iY, 0xFF0000);//red
			else if (i < 20)
				setBackgroundPixel(iX, iY, 0xFF9900); //orange
			else if (i < 30)
				setBackgroundPixel(iX, iY, 0xFFFF00); //yellow
			else if (i < 40)
				setBackgroundPixel(iX, iY, 0x00FF00); //green
			else if (i < 50)
				setBackgroundPixel(iX, iY, 0x0000FF); //blue
			else if (i < 60)
				setBackgroundPixel(iX, iY, 0x990099); //indigo
			else
				setBackgroundPixel(iX, iY, 0x994499); //violet
		}

	drawBackgroundOval(580, 560, 850, 680, 0x123456);
	
	for (int i = 0; i < 10; i++) //could do with some consts for 10 and 12
		for (int j = 0; j < 12; j++)
			tm.setMapValue(i, j, rand());
	tm.setTopLeftPositionOnScreen(50, 50);
	tm.drawAllTiles(this, getBackgroundSurface());

	SimpleImage image = ImageManager::loadImage("key_thanksnhs.jpg", true);
	image.renderImage(getBackgroundSurface(), 0, 0, 700, 10, image.getWidth(), image.getHeight());
	
}


int PpyajmaEngine::virtInitialiseObjects()
{
	drawableObjectsChanged();
	destroyOldObjects(true);
	createObjectArray(2);
	AutoObject* myAuto = new AutoObject(this);
	storeObjectInArray(0, new Cw3Object(this,&tm,myAuto));
	storeObjectInArray(1, myAuto);
	setAllObjectsVisible(true);
	return 0;
}


void PpyajmaEngine::virtMouseDown(int iButton, int iX, int iY)
{
	if (iButton == SDL_BUTTON_LEFT) {
		lockBackgroundForDrawing();
		offset = offset + 10;
		virtSetupBackgroundBuffer();
		unlockBackgroundForDrawing();
		redrawDisplay();
	}
	mouseX = iX;
	mouseY = iY;
	
}

void PpyajmaEngine::virtDrawStringsUnderneath()
{
	drawForegroundString(300, 400, "Test text!", 0x112233, NULL);
}

void PpyajmaEngine::virtDrawStringsOnTop() {
	char str[64];
	sprintf(str, "Mouse is at %d,%d", mouseX, mouseY);
	drawForegroundString(600, 600, str, 0xBB77CC, NULL);
}


