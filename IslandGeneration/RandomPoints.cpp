#include <iostream>
#include "GL/glut.h"
#include <cstdlib> 
#include <ctime> 

using namespace std;


/* Window information */
float windowWidth = 800;
float windowHeight = 600;

int numberofPoints;

float * generateRandomPoints();

float * randPointsPos;

float * generateRandomPoints(){
	

 	cout<< "Enter number of points: ";
 	cin >> numberofPoints;
 	cout << endl;



 	float * randPoints = (float *) malloc(sizeof(float) * numberofPoints * 2);

 	srand((unsigned)time(0)); 
     
    for(int i=0; i<numberofPoints * 2; i++){
    	
    	if((i + 1) % 2 == 0){
    		randPoints[i] = (rand() % (int) windowHeight) + 1;
    	} else{ 
        	randPoints[i] = (rand() % (int) windowWidth) + 1;
        }

        cout << randPoints[i] << " " ; 
 	} 

 	return randPoints;


}

void init(){
	// White color
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, windowHeight, 0.0);

	// Call random point generator
	randPointsPos = generateRandomPoints();

}

void display(){
	/* Clear the window */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Draw the line */
	/* Step 1: Enable the clients for the vertex arrays */
	glEnableClientState(GL_VERTEX_ARRAY);

	/* Step 2a: Set up the array for the line and draw it */
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(10.0);
	glVertexPointer(2, GL_FLOAT, 0, randPointsPos);
	glDrawArrays(GL_POINTS, 0, numberofPoints);

	/* Step 3: Disable the clients */
	glDisableClientState(GL_VERTEX_ARRAY);

	/* Force execution of OpenGL commands */
	glFlush();

	/* Swap buffers for animation */
	glutSwapBuffers();

}

void idle()
{
	/* Redraw the window */
	glutPostRedisplay();
}



void keyboard(unsigned char k, int x, int y)
{
	/* Show which key was pressed */
	std::cout << "Pressed \"" << k << "\" ASCII: " << (int)k << std::endl;

	/* Close application if ESC is pressed */
	if (k == 27)
	{
		exit(0);
	}
}

int main(int argc, char ** argv){
	/* Initialize the GLUT window */
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(30, 30);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Random Points");

	// Initialization
	init();

	/* Callback functions */
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	/* Start the main GLUT loop */
	/* NOTE: No code runs after this */
	glutMainLoop();	
}
