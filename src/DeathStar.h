#pragma once
#include "TileManager.h"
#include "invisDisplayableObj.h"
class DeathStar :
	public TileManager//, public invisDisplayableObj
{
public:
	DeathStar();
	virtual void virtDrawTileAt(
		BaseEngine* pEngine,
		DrawingSurface* pSurface,
		int iMapX, int iMapY,
		int iStartPositionScreenX, int iStartPositionScreenY) const;
	void setBeamNum(int i);
protected:
	//Cw4Engine* pGame;
	unsigned int TileCol = 0xFFFFFF;
	SimpleImage DS1, DS2, DS3, DS4, DS5;
	SimpleImage DS1fire1, DS1fire2, DS1fire3, DS1fire4, DS1fire5;
	SimpleImage DS3fire1, DS3fire2, DS3fire3, DS3fire4, DS3fire5;
	SimpleImage DS4fire1, DS4fire2, DS4fire3, DS4fire4, DS4fire5;
	SimpleImage DS5fire1, DS5fire2, DS5fire3, DS5fire4, DS5fire5;
	SimpleImage Laser1, Laser2, Laser3, Laser4, Laser5, Laser6;
	int localBeamNum = 0;
	
public:
	bool fire1 = false, fire2 = false, fire3 = false, fire4 = false, fire5 = false;
	int imgNum = 1;
};

