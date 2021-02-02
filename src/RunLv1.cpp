#include "RunLv1.h"
#include "BasicEnemy.h"
#include "TieFighter.h"
#include "ForceRock.h"
#include "StarDestroyer.h"
#include "DSContainer.h"
#include "Player.h"

/*
Tie all from 1020,390
Tie1 to 600,50
Tie2 to 1120,150
Tie3 to 1000,550
Tie4 to 800,650
*/

RunLv1::RunLv1(Cw4Engine* game, invisDisplayableObj* objs[])
	:StateRunning(game)
{
	pGame = game;
	setupLvl(objs);
	
}

void RunLv1::setupLvl(invisDisplayableObj* objs[])
{
	//TIEs
	objs[0]->setDefaultPos(1020, 350);
	((TieFighter*)objs[0])->flyToPos(600,50);
	objs[1]->setDefaultPos(1020, 350);
	((TieFighter*)objs[1])->flyToPos(1100,150);
	objs[2]->setDefaultPos(1020, 350);
	((TieFighter*)objs[2])->flyToPos(1200,550);
	objs[3]->setDefaultPos(1020, 350);
	((TieFighter*)objs[3])->flyToPos(800,600);
	//Rocks
	objs[4]->setDefaultPos(700,-50); //c style cast
	objs[5]->setDefaultPos(500, 750);
	objs[6]->setDefaultPos(900, 750); // can't use getWindowHeight, changes for some reason
	//Star Destroyer
	objs[7]->setDefaultPos(1400, 300);


	//DeathStar
	objs[8]->setDefaultPos(0, 0);

	//Player
	objs[33]->setDefaultPos(150, 350);

	//Score
	objs[38]->setVisible(true);
}
