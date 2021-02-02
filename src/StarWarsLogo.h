#pragma once
#include "invisDisplayableObj.h"
#include "DrawingFilters.h"

class StarWarsLogo :
	public invisDisplayableObj
{
public:
	StarWarsLogo(Cw4Engine* game);
	~StarWarsLogo();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
protected:
	SimpleImage Logo, Lvl1Crawl;
	int sx = 701, sy = 501;
};

