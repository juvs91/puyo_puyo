#include "Puyo.h"
#include <stdlib.h>





Puyo::~Puyo(void)
{
}

void Puyo::init(int x, int y){
	setColor();
	Puyo::x = x;
	Puyo::y = y;
}

void Puyo::saveToWorldMatrix(int worldMatrix[][12]){
	worldMatrix[x][y]=color;
	//Check4Together(worldMatrix);

}

int Puyo::getX(){return x;}//get the x position

int Puyo::getY(){return y;}//get the y position

//set the x position of the puyo in the matrix
void Puyo::setX(int xIn){x = xIn;}


//we set the y position of the puyo in the matrix
void Puyo::setY(int yIn){y = yIn;}

//we set the color of the puyo depending on a random number 
void Puyo::setColor(){
	color = (Color)(rand()%4);
	
}


