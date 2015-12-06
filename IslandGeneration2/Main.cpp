/*
 * Main.cpp
 *
 *  Created on: Nov 24, 2015
 *      Author: aimanuslim
 */


#include <iostream>
#include "GL/glew.h"
#include "GL/glut.h"
#include <cstdlib>
#include <ctime>
#include <math.h>

#include <fstream>
#include <string>

#include "IslandGeneration.h"

// GLM stuffs
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

/* Circle buffers */
GLuint vertexVbo; // circles
GLuint colorVbo; // circles
GLuint circlesVao;

// Points buffers
GLuint pointsVbo;
GLuint pointsColorsVbo;
GLuint pointsVao;

// Voronoi buffers
GLuint voronoiVbo;
GLuint voronoiVao;
GLuint voronoiColorsVbo;

// Delaunay points buffer
GLuint delaunayVbo;
GLuint delaunayColorsVbo;
GLuint delaunayVao;


// Water buffers
GLuint waterVbo;
GLuint waterColorsVbo;
GLuint waterVao;


/* The source code of the vertex and fragment shaders */
std::string vertexShaderCode;
std::string fragmentShaderCode;

/* References for the vertex and fragment shaders and the shader program */
GLuint vertexShader = 0;
GLuint fragmentShader = 0;
GLuint shaderProgram = 0;

// Water
//double waterVertices[windowWidth * windowHeight * 3] = {0};
//double waterColors [windowWidth * windowHeight * 3] = {0};
double * waterVertices = NULL;
double * waterColors = NULL;
int waterPtCt;
double thres = 0.0005;

// Circle
double circleVertices[windowWidth * windowHeight * 3];
double circleColors[windowWidth * windowHeight * 3];
int circlePointCt;
double elevation[windowWidth][windowHeight] = {0};
Biome biomesInformation[windowWidth][windowHeight];

// Points
int * setPoints;
int numberofPoints = 1000;
double setPointsColors[1000 * 3];
Mode pointMode = Random; // Mode for points scattering

// ************************* Island Location *************************** //
double islandX = 0;
double islandY = 0;
double islandZ = -4.000000;
double islandDelta = 0.5;

/* #### Define variables for the camera here... */
float tz = 0;
float a = 0;
float xmove = 0, ymove = 0, zmove = 0;
float rotx = 0, roty = 0, rotz = 0;
float rotationAngleX = 0.0;
float rotationAngleY = 0.0;
float resultx, resulty, resultz, movebackx, movebacky, movebackz;


/* Field of view, aspect and near/far planes for the perspective projection */
float fovy = 45.0;
float aspect = windowWidth / windowHeight;
float zNear = 1.0;
float zFar = 100.0;
int orthomod = 0;
float dist = 0;


// Voronoi
//double voronoiPoints[windowWidth * windowHeight * 3] = {0};
//double voronoiColors[windowWidth * windowHeight * 3] = {0};
int *voronoiPoints;
double *voronoiColors;
double * voronoiVertices;
double delaunayPoints[windowWidth * windowHeight * 3 * 3];
double delaunayColors[windowWidth * windowHeight * 3 * 3];
int idx = 0; // idx for putting in points for voronoiPoints
int didx = 0; // index for drawing delaunay points

// Voronoi Object
VD vd;


// Elevation 2D Array
//terrain terrainInfo[windowHeight * windowWidth];

/* The transformation matrices */
glm::mat4 modelMatrix;
glm::mat4 viewMatrix;
glm::mat4 projMatrix;

/* The location of the transformation matrices */
GLint modelMatrixLocation;
GLint viewMatrixLocation;
GLint projMatrixLocation;

/* Information of the rotation */
float angle = 90.0f;
float angleStep = PI / 500.0f;
float rotate = 0.0f;



int loadFile(char* filename, std::string& text)
{
	std::ifstream ifs;
	ifs.open(filename, std::ios::in);

	std::string line;
	while (ifs.good()) {
        getline(ifs, line);
		text += line + "\n";
    }
	return 0;
}

double normalize(int pos, int max){
	return  2.0f * ((double) pos / (double) max) - 1.0f;
}

void initShadersVAOS(){

	// White color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	  glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
//		glEnable(GL_CULL_FACE);
//		glCullFace(GL_BACK);
//		glFrontFace(GL_CCW);


	/* Initialize the vertex shader (generate, load, compile and check errors) */
		loadFile("vertex.glsl", vertexShaderCode);
		const char* vertexSource = vertexShaderCode.c_str();
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSource, NULL);
		glCompileShader(vertexShader);
		GLint status = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
		if(status != GL_TRUE)
		{
			char buffer[512];
			glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
			std::cout << "Error while compiling the vertex shader: " << std::endl << buffer << std::endl;
		}

		/* Initialize the fragment shader (generate, load, compile and check errors) */
		loadFile("fragment.glsl", fragmentShaderCode);
		const char* fragmentSource = fragmentShaderCode.c_str();
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
		glCompileShader(fragmentShader);
		status = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
		if(status != GL_TRUE)
		{
			char buffer[512];
			glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
			std::cout << "Error while compiling the fragment shader: " << std::endl << buffer << std::endl;
		}

		/****************************************** Delaunay Data VAO*********************************************/

		glGenBuffers(1, &delaunayVbo);
		glBindBuffer(GL_ARRAY_BUFFER, delaunayVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(delaunayPoints), delaunayPoints, GL_STATIC_DRAW);

		/* Initialize the Vertex Buffer Object for the colors of the vertices */
		glGenBuffers(1, &delaunayColorsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, delaunayColorsVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(delaunayColors), delaunayColors, GL_STATIC_DRAW);

		/* Define the Vertex Array Object for the points */
		glGenVertexArrays(1, &delaunayVao);
		glBindVertexArray(delaunayVao);
		glBindBuffer(GL_ARRAY_BUFFER, delaunayVbo);
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, delaunayColorsVbo);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		/******************************************Points Data VAO*********************************************/
		glGenBuffers(1, &pointsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
		glBufferData(GL_ARRAY_BUFFER, numberofPoints * 3 * sizeof(double), setPoints, GL_STATIC_DRAW);

		/* Initialize the Vertex Buffer Object for the colors of the vertices */
		glGenBuffers(1, &pointsColorsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, pointsColorsVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(setPointsColors), setPointsColors, GL_STATIC_DRAW);

		/* Define the Vertex Array Object for the points */
		glGenVertexArrays(1, &pointsVao);
		glBindVertexArray(pointsVao);
		glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, pointsColorsVbo);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		/******************************************Water Data VAO*********************************************/
		glGenBuffers(1, &waterVbo);
		glBindBuffer(GL_ARRAY_BUFFER, waterVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * 3 * waterPtCt, waterVertices, GL_STATIC_DRAW);

		/* Initialize the Vertex Buffer Object for the colors of the vertices */
		glGenBuffers(1, &waterColorsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, waterColorsVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * 3 *  waterPtCt, waterColors, GL_STATIC_DRAW);

		/* Define the Vertex Array Object for the points */
		glGenVertexArrays(1, &waterVao);
		glBindVertexArray(waterVao);
		glBindBuffer(GL_ARRAY_BUFFER, waterVbo);
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, waterColorsVbo);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		/******************************************Circle Data VAO*********************************************/
		/* Initialize the Vertex Buffer Object for the location of the vertices */
		glGenBuffers(1, &vertexVbo);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * circlePointCt * 3, circleVertices, GL_STATIC_DRAW);

		/* Initialize the Vertex Buffer Object for the colors of the vertices */
		glGenBuffers(1, &colorVbo);
		glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * circlePointCt * 3, circleColors, GL_STATIC_DRAW);

		/* Define the Vertex Array Object for the circles */
		glGenVertexArrays(1, &circlesVao);
		glBindVertexArray(circlesVao);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);





		/******************************************Voronoi Data VAO*********************************************/
		glGenBuffers(1, &voronoiVbo);
		glBindBuffer(GL_ARRAY_BUFFER, voronoiVbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(voronoiPoints), voronoiPoints, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * idx, voronoiVertices, GL_STATIC_DRAW);

		/* Initialize the Vertex Buffer Object for the colors of the vertices */
		glGenBuffers(1, &voronoiColorsVbo);
		glBindBuffer(GL_ARRAY_BUFFER, voronoiColorsVbo);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(voronoiColors), voronoiColors, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(double) * idx, voronoiColors, GL_STATIC_DRAW);

		/* Define the Vertex Array Object for the voronoi */
		glGenVertexArrays(1, &voronoiVao);
		glBindVertexArray(voronoiVao);
		glBindBuffer(GL_ARRAY_BUFFER, voronoiVbo);
		glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, voronoiColorsVbo);
		glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);


		/* Initialize the shader program */
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glBindAttribLocation(shaderProgram, 0, "inPoint");
		glBindAttribLocation(shaderProgram, 1, "inColor");
		glLinkProgram(shaderProgram);

		// MVP Matrices
		/* Get the location of the uniform variables */
		modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
		viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
		projMatrixLocation = glGetUniformLocation(shaderProgram, "projMatrix");


//		glMatrixMode(GL_PROJECTION);
//		glLoadIdentity();
//		gluOrtho2D(0.0, windowWidth, windowHeight, 0.0);

}

void init(){



//    glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0, windowWidth, windowHeight, 0.0);

	// Call random point generator
	// numberofPoints = inputter(&pointMode);
	switch(pointMode){
		case Spiral:
			generateSpiralPoints(&setPoints, numberofPoints);
			break;
		case Random:
			generateRandomPoints(&setPoints, numberofPoints);
			break;
		case Grid:
			generateGridPoints(&setPoints, numberofPoints);
			break;
		default: break;
	}

	vd = generateVoronoi(&setPoints, numberofPoints);


	// Define elevation
	// * circleVertices arent drawn
	circlePointCt = terrainInput(elevation, biomesInformation, circleVertices, circleColors);
	idx = VoronoiVerticesColors(vd, &voronoiPoints, &voronoiColors);





	//fill in colors
//	i = 0;
//	while(i < numberofPoints * 3){
//		setPointsColors[i++] = 0.0f;
//		setPointsColors[i++] = 1.0f;
//		setPointsColors[i++] = 0.0f;
//	}

	// Adjust voronoi points
	voronoiVertices = adjustVoronoi(&voronoiPoints, &voronoiColors, elevation, circleColors, idx);

	// Initialize shaders
	initShadersVAOS();

}


void drawAll(int circlePointCt){
//	glBindVertexArray(circlesVao);
//	glDrawArrays(GL_POINTS, 0, circlePointCt);
//	glBindVertexArray(waterVao);
//	glDrawArrays(GL_POINTS, 0, waterPtCt);
//	glPointSize(2.0f);
//	glBindVertexArray(pointsVao);
//	glDrawArrays(GL_POINTS, 0, numberofPoints);
	glBindVertexArray(voronoiVao);
	glPointSize(5.0f);
//	glDrawArrays(GL_POLYGON, 0, idx / 3);
	glDrawArrays(GL_TRIANGLES, 0, idx / 3);

//	glDrawArrays(GL_LINES, 0, idx / 3);
//	glDrawArrays(GL_POINTS, 0, idx / 3);
//	glBindVertexArray(deaunayVao);
//	glDrawArrays(GL_POINTS, 0, didx / 3);


}

void display(){
	/* Clear the window */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// ------------------------- MATRICES STUFF ____________ //


	/* Draw the line */
	/* Step 1: Enable the clients for the vertex arrays */
	glEnableClientState(GL_VERTEX_ARRAY);

	/* Set the view matrix */
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(islandX, islandY, islandZ));
	viewMatrix = glm::rotate(translation, angle, glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
//	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
//	rotation = glm::rotate(rotation, roty, glm::vec3(0.0f, 1.0f, 0.0f));
//	viewMatrix = glm::translate(rotation, glm::vec3(islandX, islandY, islandZ));

	/* Set the model matrix */
	//modelMatrix = glm::scale(glm::mat4(1.0), glm::vec3(1.0));

	/* Set the projection matrix */
//	projMatrix = glm::perspective(glm::radians(45.0f), ( (float) windowWidth / windowHeight), 0.1f, 100.0f);
	projMatrix = glm::perspective(glm::radians(45.0f), ( (float) windowWidth / windowHeight), 0.1f, 100.0f);

	/* Send matrix to shader */
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projMatrixLocation, 1, GL_FALSE, glm::value_ptr(projMatrix));


	// Use vertex to draw intensity
	glUseProgram(shaderProgram);
	drawAll(circlePointCt);

	/* Step 3: Disable the clients */
	glDisableClientState(GL_VERTEX_ARRAY);

	// Spin
	rotate += angleStep;
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
	else if(k == 'd'){
		thres /= 2;
	}
	else if(k == 'u'){
		angle += angleStep;
	}
	else if(k == 'w'){
		islandZ += islandDelta;
	}
	else if(k == 's'){
		islandZ -= islandDelta;
	}
	printf("angle: %f z: %f\n", angle, islandZ);


}

void freeStuffs(){
	free(setPoints);
//	free(waterVertices);
//	free(waterColors);
	free(voronoiPoints);
	free(voronoiColors);
}

int main(int argc, char ** argv){
	/* Initialize the GLUT window */
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(500, 500);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("Points");

	/* Init GLEW */
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
	}
	std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;


	// Initialization
	init();

	/* Callback functions */
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);

	/* Start the main GLUT loop */
	/* NOTE: No code runs after this */
	glutMainLoop();
	freeStuffs();
}


