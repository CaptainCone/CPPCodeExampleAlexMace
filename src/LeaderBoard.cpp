#include "LeaderBoard.h"
#include <fstream>

using namespace std;

LeaderBoard::LeaderBoard(Cw4Engine* game)
	:invisDisplayableObj(game)
{
	setVisible(false);
}

void LeaderBoard::virtDraw()
{

	if (isVisible()) {

		if (!pGame->typing) {
			pGame->drawForegroundString(950, 350, "Please press [esc]", 0xE3B201);
			pGame->drawForegroundString(950, 400, "to quit the game", 0xE3B201);
		}

		pGame->drawForegroundThickLine(400, 50, 900, 50, 0xE3B201, 4);
		pGame->drawForegroundThickLine(900, 650, 900, 50, 0xE3B201, 4);
		pGame->drawForegroundThickLine(900, 650, 400, 650, 0xE3B201, 4);
		pGame->drawForegroundThickLine(400, 50, 400, 650, 0xE3B201, 4);

		
		pGame->drawForegroundString(550, 100, "Leaderboard", 0xE3B201);
		char buf[128];
		sprintf(buf, "Please type your name: %s", name);
		pGame->drawForegroundString(450, 150, buf, 0xE3B201);
		//char buf[128];
		sprintf(buf, "Your score: %d", pGame->score);
		pGame->drawForegroundString(500, 200, buf, 0xE3B201);

		sprintf(buf, "1: %s -- %d", names[0].c_str(), scores[0]);
		pGame->drawForegroundString(500, 300, buf, 0xE3B201);
		sprintf(buf, "2: %s -- %d", names[1].c_str(), scores[1]);
		pGame->drawForegroundString(500, 350, buf, 0xE3B201);
		sprintf(buf, "3: %s -- %d", names[2].c_str(), scores[2]);
		pGame->drawForegroundString(500, 400, buf, 0xE3B201);
		sprintf(buf, "4: %s -- %d", names[3].c_str(), scores[3]);
		pGame->drawForegroundString(500, 450, buf, 0xE3B201);
		sprintf(buf, "5: %s -- %d", names[4].c_str(), scores[4]);
		pGame->drawForegroundString(500, 500, buf, 0xE3B201);
	}
}

void LeaderBoard::virtDoUpdate(int iCurrentTime)
{
	if (!isVisible())
		return;
	
	if (ticks == 0) {
		pGame->ImpMarch.pause();
		pGame->MainTheme.pause();
		if (pGame->playerHP > 0) {
			pGame->WinMusic.load("SFX/WinMusic.wav");
			pGame->WinMusic.play();
		}
		else {
			pGame->loseMusic.load("SFX/CantinaMusic.wav");
			pGame->loseMusic.play();
		}
		loadScores();
	}
	ticks++;
	redrawDisplay();
}

void LeaderBoard::loadScores()
{
	int x;
	ifstream inFile;
	inFile.open("resources/scoreboard.txt");
	if (!inFile) {
		cerr << "Unable to open file leaderboard.txt";
		exit(1);   // call system to stop
	}
	int j = 0;
	while (inFile >> x) {
		scores[j] = x;
		j++;
	}

	inFile.close();
	ofstream outFile;
	outFile.open("resources/scoreboard.txt");
	if (!outFile) {
		cerr << "Unable to open file leaderboard.txt";
		exit(1);   // call system to stop
	}
	

	if (pGame->score > scores[0]) {
		outFile << pGame->score << "\n";
		outFile << scores[0] << "\n";
		outFile << scores[1] << "\n";
		outFile << scores[2] << "\n";
		outFile << scores[3] << "\n";
	}
	else if (pGame->score > scores[1]) {
		outFile << scores[0] << "\n";
		outFile << pGame->score << "\n";
		outFile << scores[1] << "\n";
		outFile << scores[2] << "\n";
		outFile << scores[3] << "\n";
	}
	else if (pGame->score > scores[2]) {
		outFile << scores[0] << "\n";
		outFile << scores[1] << "\n";
		outFile << pGame->score << "\n";
		outFile << scores[2] << "\n";
		outFile << scores[3] << "\n";
	}
	else if (pGame->score > scores[3]) {
		outFile << scores[0] << "\n";
		outFile << scores[1] << "\n";
		outFile << scores[2] << "\n";
		outFile << pGame->score << "\n";
		outFile << scores[3] << "\n";
	}
	else if (pGame->score > scores[4]) {
		outFile << scores[0] << "\n";
		outFile << scores[1] << "\n";
		outFile << scores[2] << "\n";
		outFile << scores[3] << "\n";
		outFile << pGame->score << "\n";
	}
	else {
		outFile << scores[0] << "\n";
		outFile << scores[1] << "\n";
		outFile << scores[2] << "\n";
		outFile << scores[3] << "\n";	
		outFile << scores[4] << "\n";
	}

	outFile.close();


	inFile.open("resources/names.txt");
	if (!inFile) {
		cerr << "Unable to open file names.txt";
		exit(1);   // call system to stop
	}
	j = 0;
	string y;
	while (getline(inFile,y)) {
		names[j] = y;
		j++;
	}
	
	inFile.close();

}

void LeaderBoard::handleLetters(int k)
{
	if (char2enter < 8) {
		name[char2enter] = alpha[k-97];
		char2enter++;
	}
}

void LeaderBoard::backspace()
{
	if(char2enter > 0) {
		name[char2enter-1] = '-';
		char2enter--;
	}
}

void LeaderBoard::enter()
{
	pGame->typing = false;
	for(nameLen = 7; nameLen >= 0; nameLen--) {
		if (name[nameLen] != '-')
			break;
	}
	name[nameLen + 1] = '\0';
	changeName();
}

void LeaderBoard::changeName()
{
	ofstream outFile;
	outFile.open("resources/names.txt");
	if (!outFile) {
		cerr << "Unable to open file names.txt";
		exit(1);   // call system to stop
	}


	if (pGame->score > scores[0]) {
		outFile << name << "\n";
		outFile << names[0] << "\n";
		outFile << names[1] << "\n";
		outFile << names[2] << "\n";
		outFile << names[3] << "\n";
		for (int i = 4; i > 0; i--) {
			scores[i] = scores[i - 1];
			names[i] = names[i - 1];
		}
		scores[0] = pGame->score;
		names[0] = name;
	}
	else if (pGame->score > scores[1]) {
		outFile << names[0] << "\n";
		outFile << name << "\n";
		outFile << names[1] << "\n";
		outFile << names[2] << "\n";
		outFile << names[3] << "\n";
		for (int i = 4; i > 1; i--) {
			scores[i] = scores[i - 1];
			names[i] = names[i - 1];
		}
		scores[1] = pGame->score;
		names[1] = name;
	}
	else if (pGame->score > scores[2]) {
		outFile << names[0] << "\n";
		outFile << names[1] << "\n";
		outFile << name << "\n";
		outFile << names[2] << "\n";
		outFile << names[3] << "\n";
		for (int i = 4; i > 2; i--) {
			scores[i] = scores[i - 1];
			names[i] = names[i - 1];
		}
		scores[2] = pGame->score;
		names[2] = name;
	}
	else if (pGame->score > scores[3]) {
		outFile << names[0] << "\n";
		outFile << names[1] << "\n";
		outFile << names[2] << "\n";
		outFile << name << "\n";
		outFile << names[3] << "\n";
		scores[4] = scores[3];
		names[4] = names[3];
		scores[3] = pGame->score;
		names[3] = name;
	}
	else if (pGame->score > scores[4]) {
		outFile << names[0] << "\n";
		outFile << names[1] << "\n";
		outFile << names[2] << "\n";
		outFile << names[3] << "\n";
		outFile << name << "\n";
		scores[4] = pGame->score;
		names[4] = name;
	}
	else {
		outFile << names[0] << "\n";
		outFile << names[1] << "\n";
		outFile << names[2] << "\n";
		outFile << names[3] << "\n";
		outFile << names[4] << "\n";
	}
	outFile.close();
}
