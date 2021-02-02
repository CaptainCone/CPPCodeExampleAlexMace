#pragma once
#include "DisplayableObject.h"
#include "PpyajmaTileManager.h"
#include "AutoObject.h"
class Cw3Object :
	public DisplayableObject
{
public:
	Cw3Object(BaseEngine* pEngine, PpyajmaTileManager* pTileManager, AutoObject* myAuto);
	~Cw3Object();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
protected:
	PpyajmaTileManager* obTileManager;
	int m_iLastUpdatedTime;
	AutoObject* obMyAuto;
};

