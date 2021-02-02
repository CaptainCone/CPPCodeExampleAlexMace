#pragma once
#include "header.h"
#include "BaseEngine.h"
#include "PpyajmaTileManager.h"

class PpyajmaEngine :
	public BaseEngine
{
public:
	PpyajmaEngine();
	~PpyajmaEngine();
	void virtSetupBackgroundBuffer();
	int virtInitialiseObjects();
	void virtMouseDown(int iButton, int iX, int iY);
	void virtDrawStringsUnderneath();
	void virtDrawStringsOnTop();
protected:
	int offset;
	PpyajmaTileManager tm;
	int mouseX = 0 , mouseY = 0;
};

