#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "Cw4State.h"
#include "DisplayableObject.h"
#include "AudioController.h"
//#include "Player.h"
#include "invisDisplayableObj.h"

class invisDisplayableObj;
class Cw4State; //Needed for circular dependancy 

class Cw4Engine :
	public BaseEngine
{
public:
	Cw4Engine();
	~Cw4Engine();
	int gameSpeed = 10;
	void virtSetupBackgroundBuffer();
	void setCurrent(Cw4State *s);
	virtual void virtKeyDown(int iKeyCode);
	void virtMouseDown(int iButton, int iX, int iY);
	virtual void virtMainLoopPreUpdate();
	int virtInitialiseObjects();
	void changePlayerHP(int i);
	void shootLaser(int fromX, int fromY, int toX, int toY);
	void shootAtPlayer(int x, int y);
	void shootFromPlayer(int x, int y);
	void shootLeft(int x, int y);
	int getPlayerX();
	int getPlayerY();
	void endLvl1();
	void loadScoreBoard();
	void handleTyping(int k);
protected: 
	Cw4State *current;
	int offset, lastUpdatedTime = 0, mouse_lastUpdatedTime = 0, rnd = 0;
	DisplayableObject* pPlayer = 0;// = NULL;
	//StarDestroyer* SD = 0;
public:
	int laserNum = 0;
	int laserCycle = 0;
	int rocketNum = 0;
	int rocketCycle = 0;
	int score = 0;
	int TIENum = 4;
	int typing = false;
	bool DS3 = true;
	bool DS4 = true;
	int playerHP = 0;
public:
	invisDisplayableObj* objs[45];// = { 0 };
	AudioController MainTheme, ImpMarch, LaserSFX, WinMusic, loseMusic;
};

