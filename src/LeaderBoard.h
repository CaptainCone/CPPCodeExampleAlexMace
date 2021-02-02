#pragma once
#include "invisDisplayableObj.h"
#include <fstream>

class LeaderBoard :
	public invisDisplayableObj
{
public:
	LeaderBoard(Cw4Engine* game);
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	void loadScores();
	void handleLetters(int k);
	void backspace();
	void enter();

	void changeName();

protected:
	int scores[5];
	char name[9] = { '-','-','-','-','-','-','-','-','\0' };
	char alpha[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	int char2enter = 0;
	int nameLen = 0;
	std::string names[5];
};

