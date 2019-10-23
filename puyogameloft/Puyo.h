#pragma once

#include <stdlib.h>
#include <math.h>

class Puyo
{
	int x;//the x pixel of the puyo that is falling
	int y;//the y pixel of the puyo that is falling

public:

	enum Color {RED,BLUE,GREEN,YELLOW};
		
	Color color;

	
	~Puyo(void);
	void setX(int);
	void setY(int);
	int getX();
	int getY();
	void setColor();
	void saveToWorldMatrix(int worldMatrix[][12]);
	void init(int,int);

};

