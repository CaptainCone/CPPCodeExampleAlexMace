#pragma once
#include "BasicEnemy.h"
class ForceRock :
	public BasicEnemy
{
public:
	ForceRock(Cw4Engine* game, Explosion* expl);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	bool checkForExpl(int x, int y);
	bool checkForceRock();
	virtual void setDefaultPos(int x, int y);
	bool getGlow() { return glow; }
	void setGlow(bool b) { glow = b; }
	bool getForceThrow() { return forceThrow; }
	void setForceThrow(bool b) { forceThrow = b; }
protected:
	bool glow = false;
	bool forceThrow = false;
	double angleFrom12 = 0;
	double xMvAmt = 0, yMvAmt = 0;
	int randX = 0;
	int glowTick = 0, moveTick = 0;
	SimpleImage rock1, rock2, rock3, rock4, rock5, rock6;
	int imgNum = 0;
};

