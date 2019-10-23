#pragma once
#include "World.h"
class Game
{
public:
	Game(void);
	~Game(void);
	void gameOver();//when the gamer lose a message is dislayed
	void play();//when the game starts
	void pause();//when the game stops
	void run();
	void control(int);


private:
	World world;
};

