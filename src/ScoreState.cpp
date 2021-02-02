#include "ScoreState.h"
#include "StartUpState.h"

ScoreState::ScoreState(Cw4Engine* game)
	:Cw4State(game)
{
	game->gameSpeed = 0;
	game->setAllObjectsVisible(false);
	game->objs[39]->setVisible(true);
	game->typing = true;
}

ScoreState::~ScoreState()
{
	currGame->typing = false;
	currGame->objs[39]->setVisible(false);
}

void ScoreState::enterPress()
{
	return;
}