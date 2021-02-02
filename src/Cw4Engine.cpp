#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include "header.h"
#include "Cw4Engine.h"
#include "StateRunning.h"
#include "AutoObject.h"
#include "Cw3Object.h"
#include "PauseObj.h"
#include "Player.h"
#include "Laser.h"
#include "Rocket.h"
#include "Bullet.h"
#include "BasicEnemy.h"
#include "Explosion.h"
#include "TieFighter.h"
#include "StarDestroyer.h"
#include "ForceRock.h"
#include "RunLv1.h"
#include "RunLv2.h"
#include "Shield.h"
#include "SmallSD.h"
#include "StarWarsLogo.h"
#include "StartUpState.h"
#include "DSContainer.h"
#include "Lvl2StartState.h"
#include "Lvl2Crawl.h"
#include "currScore.h"
#include "LeaderBoard.h"
#include "ScoreState.h"

#define TIE_OFFSET 0
#define ROCK_OFFSET 4
#define SD_OFFSET 7
#define DS_OFFSET 8
#define SMALLSD_OFFSET 9
#define LASER_OFFSET 10
#define ROCKET_OFFSET 20
#define EXPLOSION_OFFSET 23
#define PLAYER_OFFSET 33
#define SHIELD_OFFSET 34
#define PAUSE_OFFSET 35
#define LOGO_OFFSET 36
#define CRAWL_OFFSET 37
#define SCORE_OFFSET 38
#define LEADERBOARD_OFFSET 39
#define EMPL2_OFFSET 40
#define NUM_OBJS 45

/*
i need
tie 0-3
rock 4-6
starDes 7
more 8-9
laser 10 10-19
rocket 3 20-22
explosion 10 23-32
player 1 33
pause obj 1 34
*/


Cw4Engine::Cw4Engine()
{
	offset = 10;
	rnd = rand();
	SDL_Init(SDL_INIT_AUDIO);

	//Stops SDL complaining
	LaserSFX.load("SFX/laser_sound.wav");
	LaserSFX.play();
	LaserSFX.pause();

	MainTheme.load("SFX/MainTheme.wav");
	MainTheme.play();
	MainTheme.pause();

	ImpMarch.load("SFX/ImperialMarch.wav");
	ImpMarch.play();
	ImpMarch.pause();

	WinMusic.load("SFX/WinMusic.wav");
	WinMusic.play();
	WinMusic.pause();

	loseMusic.load("SFX/CantinaMusic.wav");
	loseMusic.play();
	loseMusic.pause();
}

Cw4Engine::~Cw4Engine()
{
	delete current;
}

void Cw4Engine::virtSetupBackgroundBuffer()
{
	fillBackground(0x000000);
	srand(rnd);
	int windowWidth = getWindowWidth();
	int windowHeight = getWindowHeight();
	for (int num = 0; num < 200; num++) {
		int i = rand() % 5;
		int iX = rand() % windowWidth;
		int iY = rand() % windowHeight;
		i = (i + offset / 5) % 5 + 2;
		int j;
		if (iY % 3 == 2)
			j = iX - (offset * 2);
		else if (iY % 3 == 1)
			j = iX - (offset);
		else
			j = iX - (offset * 3);
		while (j < 0) {
			j += windowWidth;
		}
		drawBackgroundOval(j - 3, iY - 3, j + i + 3, iY + i + 3, 0x111111 * i);
		drawBackgroundOval(j, iY, j + i, iY + i, 0xFFFFFF);
	}
}

void Cw4Engine::setCurrent(Cw4State* s)
{
	current = s;
}

void Cw4Engine::virtKeyDown(int iKeyCode)
{
	if (typing) {
		handleTyping(iKeyCode);
		return;
	}

	switch (iKeyCode){
	case SDLK_u:
		endLvl1();
		break;
	case SDLK_RETURN:
		current->enterPress();
		break;
	case SDLK_1:
		if (gameSpeed != 0) //prevents change when paused
			current->virtSetLvl1(objs);
		break;
	case SDLK_2:
		if (gameSpeed != 0) //prevents change when paused
			current->virtSetLvl2(objs);
		break;
	case SDLK_ESCAPE:
		setExitWithCode(0);
		break;
	case SDLK_p:
		current->virtSetPause();
		break;
	case SDLK_SPACE:
		if (gameSpeed > 0) {
			if (rocketNum < 3) {
				Rocket* rocket = reinterpret_cast<Rocket*>(objs[rocketCycle + ROCKET_OFFSET]);
				if (rocket->thisX == 0 && rocket->thisY == 1) {
					rocket->setVisible(true);
					rocket->setPosition(getPlayerX(), getPlayerY());
					rocket->setShot(true);
					rocketNum++;
					rocketCycle++;
				}
			}
			if (rocketCycle > 2)
				rocketCycle = 0;
			break;
		}
	}
}

void Cw4Engine::virtMouseDown(int iButton, int iX, int iY)
{
	if (iButton == SDL_BUTTON_LEFT && gameSpeed > 0)
		if (iX > getPlayerX()) {
			shootFromPlayer(iX, iY);
			((Player*)pPlayer)->setTimeShot();
		}
}	

void Cw4Engine::virtMainLoopPreUpdate()
{
	int iCurrentTime = getModifiedTime();
	if (iCurrentTime > (lastUpdatedTime + 30)) {
		lockBackgroundForDrawing();
		offset = offset + gameSpeed;
		virtSetupBackgroundBuffer();
		unlockBackgroundForDrawing();
		redrawDisplay();
		lastUpdatedTime = iCurrentTime;
		playerHP = ((Player*)pPlayer)->health;
	}
}

int Cw4Engine::virtInitialiseObjects()
{
	drawableObjectsChanged();
	destroyOldObjects(true);
	createObjectArray(NUM_OBJS);

	for (int i = EXPLOSION_OFFSET; i < PLAYER_OFFSET; i++)
		objs[i] = DBG_NEW Explosion(this);

	for(int i = EMPL2_OFFSET; i < NUM_OBJS; i++)
		objs[i] = DBG_NEW Explosion(this);

	objs[SHIELD_OFFSET] = DBG_NEW Shield(this);


	for (int i = TIE_OFFSET; i < ROCK_OFFSET; i++) {
		Explosion* e = (Explosion*)objs[EXPLOSION_OFFSET + i]; //C style cast needs changing
		objs[i] = DBG_NEW TieFighter(this, e);
	}
	for (int i = ROCK_OFFSET; i < SD_OFFSET; i++) {
		Explosion* e = (Explosion*)objs[EXPLOSION_OFFSET + i]; //C style cast needs changing
		objs[i] = DBG_NEW ForceRock(this, e);
	}
	for (int i = SD_OFFSET; i < DS_OFFSET; i++) {
		Explosion* e = (Explosion*)objs[EXPLOSION_OFFSET + i];//C style cast needs changing
		Shield* s = (Shield*)objs[SHIELD_OFFSET];
		objs[i] = DBG_NEW StarDestroyer(this, e, s);
	}
	for (int i = DS_OFFSET; i < SMALLSD_OFFSET; i++) {
		Explosion* e = (Explosion*)objs[EXPLOSION_OFFSET + i];
		objs[i] = DBG_NEW DSContainer(this, e);
	}

	for (int i = SMALLSD_OFFSET; i < LASER_OFFSET; i++) {
		Explosion* e = (Explosion*)objs[EXPLOSION_OFFSET + i]; //C style cast needs changing
		Shield* s = (Shield*)objs[SHIELD_OFFSET];
		objs[i] = DBG_NEW StarDestroyer(this, e, s);
	}

	for(int i = LASER_OFFSET; i < ROCKET_OFFSET; i++)
		objs[i] = (invisDisplayableObj*)(DBG_NEW Laser(this));
	for (int i = ROCKET_OFFSET; i < EXPLOSION_OFFSET; i++)
		objs[i] = (invisDisplayableObj*)(DBG_NEW Rocket(this));
	
	for (int i = PLAYER_OFFSET; i < SHIELD_OFFSET; i++) {
		Explosion* e = (Explosion*)objs[EMPL2_OFFSET];
		objs[i] = DBG_NEW Player(this, e);
	}
	pPlayer = objs[PLAYER_OFFSET]; //needs to be set after player is created
	for (int i = PAUSE_OFFSET; i < LOGO_OFFSET; i++)
		objs[i] = DBG_NEW PauseObj(this);
	for (int i = LOGO_OFFSET; i < CRAWL_OFFSET; i++)
		objs[i] = DBG_NEW StarWarsLogo(this);
	for (int i = CRAWL_OFFSET; i < SCORE_OFFSET; i++)
		objs[i] = DBG_NEW Lvl2Crawl(this);
	for (int i = SCORE_OFFSET; i < LEADERBOARD_OFFSET; i++)
		objs[i] = DBG_NEW currScore(this);
	for (int i = LEADERBOARD_OFFSET; i < EMPL2_OFFSET; i++)
		objs[i] = DBG_NEW LeaderBoard(this);

	for(int i=0;i<NUM_OBJS;i++)	
		storeObjectInArray(i,objs[i]);

	current = DBG_NEW StartUpState(this);
	//current = DBG_NEW ScoreState(this);
	return 0; //isn't this a fail thing?
}

void Cw4Engine::changePlayerHP(int i)
{
	((Player*)pPlayer)->health += i;
	if (((Player*)pPlayer)->health > 145)
		((Player*)pPlayer)->health = 145;
}

void Cw4Engine::shootLaser(int fromX, int fromY, int toX, int toY)
{
	if (laserNum < 10) {
		LaserSFX.pause();
		LaserSFX.play();
		Laser* laser = reinterpret_cast<Laser*>(objs[laserCycle + LASER_OFFSET]);
		if (laser->thisX == 0 && laser->thisY == 1) {
			laser->setVisible(true);
			laser->setPosition(fromX, fromY);
			laser->setAngle(fromX, fromY, toX, toY);
			laser->setShot(true);
			laserNum++;
			laserCycle++;
		}
	}
	if (laserCycle > 9) { laserCycle = 0; }
}

void Cw4Engine::shootAtPlayer(int x, int y)
{
	shootLaser(x, y, getPlayerX(), getPlayerY() );
}

void Cw4Engine::shootFromPlayer(int x, int y)
{
	shootLaser(getPlayerX(), getPlayerY(), x, y);
}

void Cw4Engine::shootLeft(int x, int y)
{
	shootLaser(x, y, 0, y);
}

int Cw4Engine::getPlayerX()
{
	return pPlayer->getXCentre();
}

int Cw4Engine::getPlayerY()
{
	return pPlayer->getYCentre();
}

void Cw4Engine::endLvl1()
{
	setAllObjectsVisible(false);
	current->crawlLvl2();
}

void Cw4Engine::loadScoreBoard()
{
	current->scoreState();
}

void Cw4Engine::handleTyping(int k)
{
	if (k > 96 && k < 124) {
		((LeaderBoard*)objs[LEADERBOARD_OFFSET])->handleLetters(k);
	}
	if (k == 8) {
		((LeaderBoard*)objs[LEADERBOARD_OFFSET])->backspace();
	}
	if (k == SDLK_RETURN) {
		//typing = false;
		((LeaderBoard*)objs[LEADERBOARD_OFFSET])->enter();
	}
	else {
		//incorrect key noise
	}
}

