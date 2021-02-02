#include "DeathStar.h"

DeathStar::DeathStar()
	:TileManager(140,150,1,5)
{
	DS1 = ImageManager::loadImage("images/DS1.png", true);
	DS2 = ImageManager::loadImage("images/DS2.png", true);
	DS3 = ImageManager::loadImage("images/DS3.png", true);
	DS4 = ImageManager::loadImage("images/DS4.png", true);
	DS5 = ImageManager::loadImage("images/DS5.png", true);

	Laser1 = ImageManager::loadImage("images/DSLaser1.png", true);
	Laser2 = ImageManager::loadImage("images/DSLaser2.png", true);
	Laser3 = ImageManager::loadImage("images/DSLaser3.png", true);
	Laser4 = ImageManager::loadImage("images/DSLaser4.png", true);
	Laser5 = ImageManager::loadImage("images/DSLaser5.png", true);
	Laser6 = ImageManager::loadImage("images/DSLaser6.png", true);
	
	DS1fire1 = ImageManager::loadImage("images/DS1Fire1.png", true);
	DS1fire2 = ImageManager::loadImage("images/DS1Fire2.png", true);
	DS1fire3 = ImageManager::loadImage("images/DS1Fire3.png", true);
	DS1fire4 = ImageManager::loadImage("images/DS1Fire4.png", true);
	DS1fire5 = ImageManager::loadImage("images/DS1Fire5.png", true);
	
	DS3fire1 = ImageManager::loadImage("images/DS3Fire1.png", true);
	DS3fire2 = ImageManager::loadImage("images/DS3Fire2.png", true);
	DS3fire3 = ImageManager::loadImage("images/DS3Fire3.png", true);
	DS3fire4 = ImageManager::loadImage("images/DS3Fire4.png", true);
	DS3fire5 = ImageManager::loadImage("images/DS3Fire5.png", true);
	
	DS4fire1 = ImageManager::loadImage("images/DS4Fire1.png", true);
	DS4fire2 = ImageManager::loadImage("images/DS4Fire2.png", true);
	DS4fire3 = ImageManager::loadImage("images/DS4Fire3.png", true);
	DS4fire4 = ImageManager::loadImage("images/DS4Fire4.png", true);
	DS4fire5 = ImageManager::loadImage("images/DS4Fire5.png", true);
	
	DS5fire1 = ImageManager::loadImage("images/DS5Fire1.png", true);
	DS5fire2 = ImageManager::loadImage("images/DS5Fire2.png", true);
	DS5fire3 = ImageManager::loadImage("images/DS5Fire3.png", true);
	DS5fire4 = ImageManager::loadImage("images/DS5Fire4.png", true);
	DS5fire5 = ImageManager::loadImage("images/DS5Fire5.png", true);
	
}

void DeathStar::virtDrawTileAt(
	BaseEngine* pEngine, DrawingSurface* pSurface, 
	int iMapX, int iMapY, 
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int mapVal = getMapValue(iMapX, iMapY);
	switch (mapVal) {
	case 0:
		pEngine->drawForegroundTriangle(iStartPositionScreenX+47, iStartPositionScreenY+140,
			iStartPositionScreenX + 150, iStartPositionScreenY,
			iStartPositionScreenX + 150, iStartPositionScreenY + 140, 0x4B4B4B);
		if (!fire1) {
			DS1.renderImageWithMask(pSurface, 0, 0,
				iStartPositionScreenX, // Left
				iStartPositionScreenY, // Top
				(149), // Right
				(139));
		}
		else {
			switch (imgNum) {
			case 1:
				DS1fire1.renderImageWithMask(pSurface, 0, 0,
					iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(149), // Right
					(139));
				break;
			case 2:
				DS1fire2.renderImageWithMask(pSurface, 0, 0,
					iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(149), // Right
					(139));
				break;
			case 3:
				DS1fire3.renderImageWithMask(pSurface, 0, 0,
					iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(149), // Right
					(139));
				break;
			case 4:
				DS1fire4.renderImageWithMask(pSurface, 0, 0,
					iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(149), // Right
					(139));
				break;
			case 5:
				DS1fire5.renderImageWithMask(pSurface, 0, 0,
					iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(149), // Right
					(139));
				break;
			}
			
		}
		break;

	case 1:
		pEngine->drawForegroundRectangle(iStartPositionScreenX, iStartPositionScreenY,
			iStartPositionScreenX + 150, iStartPositionScreenY + 140, 0x4B4B4B);
		switch (localBeamNum) {
		case 0:
			DS2.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, 150, 140);
			break;
		case 1:
			Laser1.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, 150, 140);
			break;
		case 2:
			Laser2.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, 150, 140);
			break;
		case 3:
			Laser3.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, 150, 140);
			break;
		case 4:
			Laser4.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, 150, 140);
			break;
		case 5:
			Laser5.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, 150, 140);
			break;
		default:
			Laser6.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, 150, 140);
			break;
		}
		break;
		
	case 2:
		pEngine->drawForegroundRectangle(iStartPositionScreenX, iStartPositionScreenY,
			iStartPositionScreenX + 150, iStartPositionScreenY + 140, 0x898989);
		if (!fire3) {
			DS3.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
				iStartPositionScreenY, // Top
				(150), // Right
				(140));
		}
		else {
			switch (imgNum) {
			case 1:
				DS3fire1.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
				iStartPositionScreenY, // Top
				(150), // Right
				(140));
				break;
			case 2:
				DS3fire2.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 3:
				DS3fire3.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 4:
				DS3fire4.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 5:
				DS3fire5.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			}
			
		}
		break;

	case 3:
		pEngine->drawForegroundRectangle(iStartPositionScreenX, iStartPositionScreenY,
			iStartPositionScreenX + 150, iStartPositionScreenY + 139, 0x898989);
		if (!fire4) {
			DS4.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
				iStartPositionScreenY, // Top
				(150), // Right
				(140));
		}
		else {
			switch (imgNum) {
			case 1:
				DS4fire1.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 2:
				DS4fire2.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 3:
				DS4fire3.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 4:
				DS4fire4.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 5:
				DS4fire5.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			}
		}
		break;
	
	case 4:
		if (!fire5) {
			DS5.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
			iStartPositionScreenY, // Top
			(150), // Right
			(140));
		}
		else {
			switch (imgNum) {
			case 1:
				DS5fire1.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 2:
				DS5fire2.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 3:
				DS5fire3.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 4:
				DS5fire4.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			case 5:
				DS5fire5.renderImageWithMask(pSurface, 0, 0, iStartPositionScreenX, // Left
					iStartPositionScreenY, // Top
					(150), // Right
					(140));
				break;
			}
		}
		
		break;
	}
}

void DeathStar::setBeamNum(int i)
{
	localBeamNum = i;
}
