#include "DSContainer.h"

DSContainer::DSContainer(Cw4Engine* game, Explosion* exp)
	:BasicEnemy(game, exp)
{
	setVisible(false);
}

void DSContainer::virtDraw()
{
	if (isVisible()) {
		if (ticks % 5 == 0 && pGame->gameSpeed > 0) {
			DS.imgNum++;
			if (DS.imgNum > 5)
				DS.imgNum = 1;
		}
		for (int i = 0; i < 5; i++)
			DS.setMapValue(0, i, i);
		DS.setBeamNum(beamNum);
		DS.setTopLeftPositionOnScreen(1300-xPos, 0);
		DS.drawAllTiles(pGame, pGame->getForegroundSurface());

		if (beamNum == 7) {
			pGame->drawForegroundThickLine(1158, 209, 
				playerX - (1158-playerX ), playerY - ( 209 - playerX ) + down, 
				0x00FF00, 7);
		}
	}
}

void DSContainer::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible())
		return;

	if (allhp <= 0)
		pGame->loadScoreBoard();

	if (ticks == 0) {
		pGame->MainTheme.pause();
		pGame->ImpMarch.pause();
		pGame->ImpMarch.load("SFX/ImperialMarch.wav");
		pGame->ImpMarch.play();
	}
	if(ticks % 3 == 0 )
		checkDS();
	if (ticks > 300 && ticks % 60 == 0)
		beamNum += pGame->gameSpeed;
	if ((ticks-300) % 360 == 0) {
		playerX = pGame->getPlayerX();
		playerY = pGame->getPlayerY();
		down = 0;
	}
	if (beamNum > 6) {
		if (pGame->getPlayerY() < playerY)
			down -= 2 * pGame->gameSpeed;
		else
			down += 2 * pGame->gameSpeed;
	}
	if (beamNum > 8)
		beamNum = 0;
	ticks += pGame->gameSpeed;
	if(xPos< 150 && ticks % 2 == 0)
		xPos += pGame->gameSpeed;
	redrawDisplay();
}

void DSContainer::setDefaultPos(int x, int y)
{
	if (x == 0 && y == 0) {
		//setActive(false);
		setVisible(false);
		return;
	}
	xPos = 0;
	ticks = 0;
	setVisible(true);
	beamNum = 0;
	pGame->DS3 = true;
	pGame->DS4 = true;
	DS.fire1 = false;
	DS.fire2 = false;
	DS.fire3 = false;
	DS.fire4 = false;
	DS.fire5 = false;
}

void DSContainer::checkDS()
{
	int score;
	if (checkLine(1260, 0, 1190, 140)) {
		doExplosion(expX - 25, expY - 25);

		hp1--;
		
		if (hp1 == 0) {
			score = 2000 - ticks;
			if (score > 100)
				pGame->score += score;
			else
				pGame->score += 100;
				DS.fire1 = true;
				allhp--;
		}

	}

	if (checkLine(1190, 140, 1150, 280)) {
		doExplosion(expX - 25, expY - 25);
	}

	if (checkLine(1150, 280, 1150, 420)) {
		hp3--;
		doExplosion(expX - 25, expY - 25);
		
		if (hp3 == 0) {
		score = 2000 - ticks;
		if (score > 100)
			pGame->score += score;
		else
			pGame->score += 100;
			DS.fire3 = true;
			allhp--;
			pGame->DS3 = false;
		}
	}

	if (checkLine(1180, 560, 1150, 420)) {
		hp4--;
		doExplosion(expX - 25, expY - 25);
		
		if (hp4 == 0) {
		score = 2000 - ticks;
		if (score > 100)
			pGame->score += score;
		else
			pGame->score += 100;
			DS.fire4 = true;
			allhp--;
			pGame->DS4 = false;
		}
	}

	if (checkLine(1180, 560, 1250, 700)) {
		hp5--;
		doExplosion(expX - 25, expY - 25);
		
		if (hp5 == 0) {
		score = 2000 - ticks;
		if (score > 100)
			pGame->score += score;
		else
			pGame->score += 100;
			DS.fire5 = true;
			allhp--;
		}
	}
}

