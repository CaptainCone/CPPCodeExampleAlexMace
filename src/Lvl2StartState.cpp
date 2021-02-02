#include "Lvl2StartState.h"
#include "RunLv2.h"

Lvl2StartState::Lvl2StartState(Cw4Engine* game)
	:Cw4State(game)
{
	currGame = game;
	currGame->gameSpeed = 0;
	game->objs[37]->setVisible(true);
}

void Lvl2StartState::enterPress()
{
	currGame->setCurrent(new RunLv2(currGame, currGame->objs));
	currGame->objs[37]->setVisible(false);
	delete this;
}