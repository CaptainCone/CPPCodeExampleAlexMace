#include "StateRunning.h"
#include "StatePaused.h"
#include "RunLv1.h"
#include "RunLv2.h"

StateRunning::StateRunning(Cw4Engine* game)
	:Cw4State(game)
{
	currGame = game;
	currGame->gameSpeed = 1;
	//currGame->MainTheme.pause();
}

void StateRunning::virtSetPause()
{
	currGame->setCurrent(new StatePaused(currGame));
	delete this;
}

void StateRunning::virtSetLvl1(invisDisplayableObj* objs[])
{
	currGame->setCurrent(new RunLv1(currGame, objs));
	delete this;
}

void StateRunning::virtSetLvl2(invisDisplayableObj* objs[])
{
	currGame->setCurrent(new RunLv2(currGame, objs));
	delete this;
}

void StateRunning::setupLvl(invisDisplayableObj* objs[])
{
	return;
}

void StateRunning::startLvl2(invisDisplayableObj* objs[])
{
	return;
}
