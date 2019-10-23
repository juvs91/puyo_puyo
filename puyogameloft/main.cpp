#include "GlHeaders.h"
#include "Game.h"
#include <stdio.h>


World world;
Game game;

void init(){
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(5, -1,11, -1);
	//DEFINE EL COLOR DEL FONDO DE TU PANTALLA
   
    glutPostRedisplay();
}

void display(void){
	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClearColor(0,1,1,1);
	game.play(); 
	//glFlush();
	glutSwapBuffers();
}


void reshape(int w,int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
    gluOrtho2D(6, 0,11, -1);
    //glClearColor(0,1,1,1);
	//glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void keyboard(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_DOWN:
			game.control(0);
            break;
        case GLUT_KEY_UP:
			game.control(1);
            break;
        case GLUT_KEY_RIGHT:
			game.control(2);
            break;
        case GLUT_KEY_LEFT:
			game.control(3);
            break;
     
    }
    glutPostRedisplay();
}

void run(int val){
	game.run();
	glutTimerFunc(1000, run, 0);
    glutPostRedisplay();
}


int main(int argc, char** argv){ 

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB   );
	glutInitWindowSize(400,720);
    glutInitWindowPosition(10,10);
    glutCreateWindow("puyo puyo");
	glutReshapeFunc(reshape);
	glutTimerFunc(1000, run, 0);
    glutSpecialFunc(keyboard);
    glutDisplayFunc(display);
   
	init();//hay que checar el gride size , para escojer el tamaño del grid
   
    glutMainLoop();
    
    
    
    return 0;
  
}