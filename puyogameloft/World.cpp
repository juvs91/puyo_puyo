#include "World.h"


World::World(void)
{
	srand(time(NULL));
	width = 870;
	height = 720;
	score = "score";

	for (int i=0; i<6; i++){
        for (int j=0; j<12; j++) {
			worldMatrix[i][j] = -1;//there is not puyos in the matrix
        }
    }

	
}

//function that initialize falling puyos


World::~World(void)
{
}



//check if the cell is avaliable 
bool World::isCellAvailable(int x,int y){
	if(worldMatrix[x][y] == 0){
		return true;
	}
	return false;
}




void World::draw(){
	//paint the screen
	glClearColor(0,1,1,1);

	//paint puyos in matrix
	for(int i=0;i<6;i++){
		for(int j=0;j<12;j++){
			paintPuyo((Puyo::Color)worldMatrix[i][j],i,j);
		}
	}

	//paint falling puyos
	paintPuyo(fallingPuyoPair.puyo1);
	paintPuyo(fallingPuyoPair.puyo2);
}

void World::paintPuyo(Puyo puyo){
	switch(puyo.color){
		case Puyo::RED:
			glColor3f(1.0,0,0);
			break;
		case Puyo::BLUE:
			glColor3f(0,0,1);
			break;
		case Puyo::GREEN:
			glColor3f(0,1,0);
			break;
		case Puyo::YELLOW:
			glColor3f(1.0,1,0);
			break;
	
	}
	glPushMatrix();
		glTranslatef(puyo.getX()+0.5,puyo.getY()-0.5, 0);
		glutSolidSphere(0.5f,30,30);
	glPopMatrix();

	float centerOfScreen= 200/2;
	float halfOfText= (score.length()/2)*.13;
	glColor3f(0, 0, 0);//No esta funcionando para cambiar el color de las letras.
	glRasterPos2f(6,10);//it prints the word score
	for (int i=0; i<score.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,score[i]);
	}
	numericalScore = std::to_string((long long)(fallingPuyoPair.score));
	
	glRasterPos2f(5,10);//it prints the numeric score
	for (int i=0; i<numericalScore.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,numericalScore[i]);
	}
	fallingPuyoPair.gameOver(worldMatrix);


}

void World::paintPuyo(Puyo::Color color, int x, int y){
	switch(color){
		case Puyo::RED:
			glColor3f(1.0,0,0);
			break;
		case Puyo::BLUE:
			glColor3f(0,0,1);
			break;
		case Puyo::GREEN:
			glColor3f(0,1,0);
			break;
		case Puyo::YELLOW:
			glColor3f(1.0,1,0);
			break;
		default:
			return;
	}
	glPushMatrix();
		glTranslatef(x+0.5,y-0.5, 0);
		glutSolidSphere(0.5f,30,30);
	glPopMatrix();
	
}




