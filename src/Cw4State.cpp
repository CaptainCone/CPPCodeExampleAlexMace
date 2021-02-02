#include "Cw4State.h"
#include "invisDisplayableObj.h"
#include "Lvl2StartState.h"
#include "ScoreState.h"

Cw4State::Cw4State(Cw4Engine* game)
{
	currGame = game;
}

void Cw4State::setSpeed(Cw4Engine* game, int i)
{
	game->gameSpeed = i;
}

void Cw4State::virtSetPause()
{
	return;
}

void Cw4State::virtSetLvl1(invisDisplayableObj* objs[])
{
	return;
}
void Cw4State::virtSetLvl2(invisDisplayableObj* objs[])
{
	return;
}

void Cw4State::setupLvl(invisDisplayableObj* objs[])
{
	return;
}

void Cw4State::enterPress()
{
	return;
}

void Cw4State::crawlLvl2()
{
	currGame->setCurrent(new Lvl2StartState(currGame));
	delete this;
}

void Cw4State::scoreState()
{
	currGame->setCurrent(new ScoreState(currGame));
	delete this;
}
