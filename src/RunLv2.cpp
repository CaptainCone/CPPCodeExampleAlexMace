#include "RunLv2.h"
#include "TieFighter.h"
#include "ForceRock.h"
#include "StarDestroyer.h"
#include "DSContainer.h"

RunLv2::RunLv2(Cw4Engine* game, invisDisplayableObj* objs[])
	:StateRunning(game)
{
	pGame = game;
	setupLvl(objs);
	//DS = new DeathStar(game);
}

void RunLv2::setupLvl(invisDisplayableObj* objs[])
{
	//Make lvl1 not show
	for (int i = 0; i < 4; i++) {
		objs[i]->setDefaultPos(0, 0);
	}

	objs[4]->setDefaultPos(700, -50); //c style cast
	objs[5]->setDefaultPos(500, 750);
	objs[6]->setDefaultPos(900, 750);
	
	objs[7]->setDefaultPos(1401, 301);

	//DeathStar
	objs[8]->setDefaultPos(1, 0); //just to activate it

	//smallSD
	objs[9]->setDefaultPos(1401, 550);

	//Player
	objs[33]->setDefaultPos(150, 350);

	//Score
	objs[38]->setVisible(true);
}