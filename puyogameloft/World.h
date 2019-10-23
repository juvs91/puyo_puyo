#pragma once

#include "Puyo.h"
#include "Cell.h"
#include "FallingPuyos.h"
#include "GlHeaders.h"

#include <string>
#include <time.h>
#include <vector>
#include <sstream>


class World
{
public:
	World(void);
	~World(void);
	int worldMatrix[6][12];// define the matrix of positions to know where is each puyo to know how to break when there are 4 of them together 
    void final();
	int width,height;
	void draw();
	FallingPuyos fallingPuyoPair;
	bool isCellAvailable(int x,int y);
	void paintPuyo(Puyo);
	void paintPuyo(Puyo::Color, int, int);
	void Check4Together();

private: 
	std::string score;
	std::string numericalScore;
	int cellX;
	int cellY;
	void checkCollisions();
	
};

