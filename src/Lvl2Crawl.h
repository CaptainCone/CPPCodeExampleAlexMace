#pragma once
#include "invisDisplayableObj.h"
class Lvl2Crawl :
	public invisDisplayableObj
{
public:
	Lvl2Crawl(Cw4Engine* game);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
protected:
	SimpleImage imgCrawl;
};

