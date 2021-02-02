#include "StartUpState.h"
#include "RunLv1.h"

StartUpState::StartUpState(Cw4Engine* game)
	:Cw4State(game)
{
	currGame = game;
	currGame->gameSpeed = 0;
	game->objs[36]->setVisible(true);
	game->objs[36]->setTicks(0);
}

void StartUpState::enterPress()
{
	currGame->setCurrent(new RunLv1(currGame, currGame->objs));
	currGame->objs[36]->setVisible(false);
	delete this;
}
