#include "header.h"
#include "PpyajmaTileManager.h"

PpyajmaTileManager::PpyajmaTileManager()
	: TileManager (30,30,10,12)
{
}

void PpyajmaTileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	static int num = 0;
	int iMapValue = getMapValue(iMapX, iMapY); // which was set to result of rand()
	//unsigned int iColour = 0xFF0000;
	unsigned int iColour = (unsigned int)((iMapValue & 0xf00) << 12) // red
		+ (unsigned int)((iMapValue & 0xf0) << 8) // green
		+ (unsigned int)((iMapValue & 0xf) << 4); // blue
	if (num == 0) {
		pSurface->drawRectangle(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			iColour);
		num = rand() % 2;
		
	} 
	else {
		pSurface->drawOval(
			iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			iStartPositionScreenX + getTileWidth() - 1, // Right
			iStartPositionScreenY + getTileHeight() - 1, // Bottom
			iColour);
		num = rand() % 2;
	}
}

