#include "Game.h"
#include "FallingPuyos.h"


Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::gameOver(){}

void Game::pause(){}


void Game::play(){
	world.draw();
}

void Game::run(){
	if(!(world.fallingPuyoPair.gameOver(world.worldMatrix))){
		world.fallingPuyoPair.moveDown(world.worldMatrix);
	}
}

void Game::control(int key){
	switch(key){
	case 0:
		world.fallingPuyoPair.moveDown(world.worldMatrix);
		break;

	case 1:
		world.fallingPuyoPair.change(world.worldMatrix);
		break;

	case 2://the left key
		world.fallingPuyoPair.moveLeft(world.worldMatrix);
		break;
	case 3://the right key
		world.fallingPuyoPair.moveRigth(world.worldMatrix);
		break;
	}






}

