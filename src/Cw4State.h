#pragma once
#include "header.h"
#include "Cw4Engine.h"
#include "invisDisplayableObj.h"

class invisDisplayableObj;
class Cw4Engine; //Needed for circular dependancy 

class Cw4State
{
public:
	Cw4State(Cw4Engine* game);
	void setSpeed(Cw4Engine* game, int i);
	virtual void virtSetPause();
	virtual void virtSetLvl1(invisDisplayableObj* objs[]);
	virtual void virtSetLvl2(invisDisplayableObj* objs[]);
	virtual void setupLvl(invisDisplayableObj* objs[]);
	//virtual void virtSetLvl1(DisplayableObject* objs[]);
	//virtual void virtSetLvl2(DisplayableObject* objs[]);
	//virtual void setupLvl(DisplayableObject* objs[]);
	virtual void enterPress();
	void crawlLvl2();
	void scoreState();
protected: 
	Cw4Engine* currGame;
	int ticks = 0;
};

