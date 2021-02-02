#include "StatePaused.h"
#include "StateRunning.h"

StatePaused::StatePaused(Cw4Engine* game)
	:Cw4State(game)
{
	currGame = game;
	currGame->gameSpeed = 0;
	game->objs[35]->setVisible(true);
}

StatePaused::~StatePaused() 
{
	currGame->objs[35]->setVisible(false);
}

void StatePaused::virtSetPause()
{
	currGame->setCurrent(new StateRunning(currGame));
	delete this;
}

