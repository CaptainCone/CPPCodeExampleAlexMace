#pragma once
#include "TileManager.h"
class PpyajmaTileManager :
	public TileManager
{
public:
	PpyajmaTileManager();
	virtual void virtDrawTileAt(
		BaseEngine* pEngine, 
		DrawingSurface* pSurface, 
		int iMapX, int iMapY, 
		int iStartPositionScreenX, int iStartPositionScreenY) const;

};

