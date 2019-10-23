#pragma once

#include "Puyo.h"
#include "GlHeaders.h"

#include <map>
#include <string>
#include <list>

using namespace std;

class FallingPuyos
{
	

	bool movementBloqued;
	bool isHorizontal;
	bool hasChange;
	map<string,int> *puyosMap;
	list<Puyo*> *puyosList;
	bool flip;

	

public:

	enum Collision{
		NO_COLLISION,
		PUYO1_COLLISION,
		PUYO2_COLLISION,
		BOTH_COLLISION
	};

	enum Movement{
		LEFT_MOVEMENT,
		RIGHT_MOVEMENT,
		DOWN_MOVEMENT
	};

	int score;

	FallingPuyos(void);
	~FallingPuyos(void);
	bool gameOver(int worldMatrix[][12]);
	void init();
	void moveRigth(int worldMatrix[][12]);
    void moveLeft(int worldMatrix[][12]);
    void moveDown(int [][12]);
	void change(int worldMatrix[][12]);//change the form of the puyo puyo
	void final();
	void check4Together(int worldMatrix[][12]);
	void puyosSearch(int worldMatrix[][12],map<string,int> *puyosMap,list<Puyo*> *puyosList,int x,int y,Puyo::Color color);


	Collision checkForCollisions(int worldMatrix[][12] , Movement movementType);
	//bool isHorizontal;
	
	//bool canFall,ending,canMove;

	Puyo puyo1;
	Puyo puyo2;
};

