#include "FallingPuyos.h"
#include <stdio.h>



FallingPuyos::FallingPuyos(void)
{
	init();
}

void FallingPuyos::init(){
	puyo1.init(2,0);
	puyo2.init(3,0);
	puyo1.setX(2);
	puyo1.setY(0);
	puyo2.setX(3);
	puyo2.setY(0);
	isHorizontal = true;
	hasChange = false;
	flip = false;
}


FallingPuyos::~FallingPuyos(void)
{
}

//moves 1 position of the matrix to the rigth
void FallingPuyos::moveRigth(int worldMatrix[][12]){
	if(!movementBloqued){
		puyo1.setX(puyo1.getX()+1);
		puyo2.setX(puyo2.getX()+1);
		if(checkForCollisions(worldMatrix, RIGHT_MOVEMENT) != NO_COLLISION){
		 puyo1.setX(puyo1.getX()-1);
		 puyo2.setX(puyo2.getX()-1); 
		}
	}
}

//moves 1 position of the matrix to the left
void FallingPuyos::moveLeft(int worldMatrix[][12]){
	if(!movementBloqued){
		puyo1.setX(puyo1.getX()-1);
		puyo2.setX(puyo2.getX()-1);
		if(checkForCollisions(worldMatrix, LEFT_MOVEMENT) != NO_COLLISION){
			puyo1.setX(puyo1.getX()+1);
			puyo2.setX(puyo2.getX()+1);
		}
	}
}

//move 15 pixels the puyo to the bottom
void FallingPuyos::moveDown(int  worldMatrix[][12]){
	//if(puyo1.getY()<12){
	if(!gameOver(worldMatrix)){
		puyo2.setY(puyo2.getY()+1);	
		puyo1.setY(puyo1.getY()+1);
	
	Collision collision = checkForCollisions(worldMatrix, DOWN_MOVEMENT);
	//check for collision when vertical
	if((collision == PUYO1_COLLISION && (puyo1.getX() == puyo2.getX())) || (collision == PUYO2_COLLISION && (puyo1.getX() == puyo2.getX()))){
		collision = BOTH_COLLISION;
	}
	switch (collision) {
		case BOTH_COLLISION:
			puyo2.setY(puyo2.getY()-1);	
			puyo1.setY(puyo1.getY()-1);
			puyo1.saveToWorldMatrix(worldMatrix);
			puyo2.saveToWorldMatrix(worldMatrix);
			check4Together(worldMatrix);
			movementBloqued = false;
			if(!(gameOver(worldMatrix))){
				init();
			}
			break;

		case PUYO1_COLLISION:
			puyo1.setY(puyo1.getY()-1);
			puyo1.saveToWorldMatrix(worldMatrix);
			movementBloqued = true;
			break;
		case PUYO2_COLLISION:
			puyo2.setY(puyo2.getY()-1);
			puyo2.saveToWorldMatrix(worldMatrix);
			movementBloqued = true;
			break;
	}
	}//checkGameOver(worldMatrix);
}

FallingPuyos::Collision FallingPuyos::checkForCollisions(int worldMatrix[][12],Movement movementType){
	switch(movementType){
		case DOWN_MOVEMENT:
			if((puyo1.getY()>=12 && puyo2.getY()>=12) || (worldMatrix[ puyo1.getX()][ puyo1.getY()]!= -1 && worldMatrix[ puyo2.getX()][ puyo2.getY()]!= -1) ||
				(puyo1.getY()>=12 && worldMatrix[ puyo2.getX()][ puyo2.getY()]!= -1) || (puyo2.getY()>=12 && worldMatrix[ puyo1.getX()][ puyo1.getY()]!= -1) ){
				return BOTH_COLLISION;
			} else if (puyo1.getY()>=12 || worldMatrix[ puyo1.getX()][ puyo1.getY()]!= -1 ) {
				return PUYO1_COLLISION;
			} else if (puyo2.getY()>=12 || worldMatrix[ puyo2.getX()][ puyo2.getY()]!= -1 ) {
				return PUYO2_COLLISION;
			}


			break;
		case LEFT_MOVEMENT:
			if(puyo1.getX()<0  || puyo2.getX()<0 || worldMatrix[ puyo1.getX()][ puyo1.getY()]!= -1 || worldMatrix[ puyo2.getX()][ puyo2.getY()]!= -1){
				return BOTH_COLLISION;
			}
			break;
		case RIGHT_MOVEMENT:
			if(puyo1.getX()>=6 || puyo2.getX()>=6 || worldMatrix[ puyo1.getX()][ puyo1.getY()]!= -1  || worldMatrix[ puyo2.getX()][ puyo2.getY()]!= -1){
				return BOTH_COLLISION;
			}
			break;
	}
	return NO_COLLISION;
}

void FallingPuyos::final(){

}
 

//when they want to rotate the puyos 
void FallingPuyos::change(int worldMatrix[][12]){
if(!gameOver(worldMatrix)){
	if(!movementBloqued){
		if(isHorizontal){
			if(flip){
				puyo2.setX(puyo1.getX());
				puyo2.setY(puyo1.getY()+11);
				isHorizontal = false;
				flip = true;
			}else{
				puyo2.setX(puyo1.getX());
				puyo2.setY(puyo1.getY()-1);
				isHorizontal = false;
				flip = false;
			}
		}else{
			if(hasChange){
				if((!(puyo1.getX()+1>=6)) && worldMatrix[ puyo1.getX()+1][ puyo1.getY()]== -1 ){
					puyo2.setX(puyo1.getX()+1);
					puyo2.setY(puyo1.getY());
					hasChange=false;
					isHorizontal = true;
				}	
	
			}else{
				if((!(puyo1.getX()-1<0))  &&  worldMatrix[ puyo1.getX()-1][ puyo1.getY()]== -1){
					puyo2.setX(puyo1.getX()-1);
					puyo2.setY(puyo1.getY());
					hasChange=true;
					isHorizontal = true;
				}
			}
		}
	}
  }
}

bool FallingPuyos::gameOver(int worldMatrix[][12]){
	std::string gameOver="game over";
	if(worldMatrix[2][0] != -1 || worldMatrix[3][0] != -1){//the player go to the top of the board 
		 glColor3f(0, 0, 0);//No esta funcionando para cambiar el color de las letras.
		 glRasterPos2f(4,4);
		 for (int i=0; i<gameOver.length(); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,gameOver[i]);
		 }
		return true;	
	}else{
		return false;//the player can continue playing 
	}
	
}

void FallingPuyos::check4Together(int worldMatrix[][12]){
	
	
	int matrixToPop[6][12];
	bool flagToCheckAgain = false;
	int sizeListOfPuyos=0;//it is initialized in 0 because there is no puyos in the list

	for(int i=0;i<6;i++){
		for(int j=0;j<12;j++){
			matrixToPop[i][j] = 0;
		}
	}


	for(int i=0;i<6;i++){
		for(int j=11;j>=0;j--){
			if(worldMatrix[i][j] == -1){
				break;
			}
			//string str = std::to_string((long long)j) + "," + std::to_string((long long)i);
			
		if(matrixToPop[i][j] == 0 && worldMatrix[i][j]!=-1){
				puyosMap = new map<string,int>;
				puyosList = new list<Puyo*>;
				puyosSearch(worldMatrix,puyosMap,puyosList,i,j,(Puyo::Color)worldMatrix[i][j]);
				delete puyosMap;
				sizeListOfPuyos = puyosList->size();
				if(sizeListOfPuyos>=4){
					score += sizeListOfPuyos;
					flagToCheckAgain = true;
					for(int k = 0;k < sizeListOfPuyos;k++){
						Puyo *puyo = puyosList->front();
						matrixToPop[puyo->getX()][puyo->getY()] = -1;
						puyosList->pop_front();
					}
				} else {
					for(int k = 0;k <sizeListOfPuyos;k++){
						Puyo *puyo = puyosList->front();
						matrixToPop[puyo->getX()][puyo->getY()] = 1;
						puyosList->pop_front();
					}
				}
				delete puyosList;
			}
		}
	}


	if(flagToCheckAgain){
		
		for(int i=0;i<6;i++){
			int cont = 0;
			int j;
			for(j=11;j>=0 && worldMatrix[i][j] != -1 ;j--){
				if(matrixToPop[i][j] == -1){
					cont++;
				}else{
					worldMatrix[i][j+cont] = worldMatrix[i][j];
				}
			}
			for(int k = j + cont; k >= j; k--){
				worldMatrix[i][k] = -1;
			}
		}

		check4Together(worldMatrix);
	}

}


void FallingPuyos::puyosSearch(int worldMatrix[][12],map<string,int> *puyosMap,list<Puyo*> *puyosList,int col,int ren,Puyo::Color color){
	Puyo *puyo = new Puyo;
	puyo->setX(col);
	puyo->setY(ren);
	puyo->color = color;
	puyosList->push_front(puyo);
	string str = std::to_string((long long)col)+","+std::to_string((long long)ren);
	puyosMap->insert ( std::pair<string,int>(str , 0) );
	if(col-1>= 0 && (worldMatrix[col-1][ren] == color) && puyosMap->find(std::to_string((long long)col-1)+","+std::to_string((long long)ren)) == puyosMap->end()){
		 
		puyosSearch(worldMatrix, puyosMap, puyosList, col-1, ren, color); 
	}
	if(col+1< 6 && (worldMatrix[col+1][ren] == color) && puyosMap->find(std::to_string((long long)col+1)+","+std::to_string((long long)ren)) == puyosMap->end()){
		
		puyosSearch(worldMatrix, puyosMap, puyosList, col+1, ren, color); 
	}
	if(ren-1>= 0 && (worldMatrix[col][ren-1] == color) && puyosMap->find(std::to_string((long long)col)+","+std::to_string((long long)ren-1)) == puyosMap->end()){
		
		puyosSearch(worldMatrix, puyosMap, puyosList, col, ren-1, color); 
	}
	if(ren+1< 12 && (worldMatrix[col][ren+1] == color) && puyosMap->find(std::to_string((long long)col)+","+std::to_string((long long)ren+1)) == puyosMap->end()){
		
		puyosSearch(worldMatrix, puyosMap, puyosList, col, ren+1, color); 
	}
}

