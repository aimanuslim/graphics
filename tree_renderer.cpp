/*
	File for rendering all objects and triangles
*/
#include "tree_renderer.h"
#include "glutCallBacks.h"
#include "part_model.h"
/*#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
*/
#include<fstream>

#define WINDOW_H 800
#define WINDOW_W 600

//bool tree_renderer::firstRender = true;

tree_renderer::tree_renderer(tree_generator * generator)
{
	/* Window information */
	treeVertexCount = 0;
	firstRender = false;
	this->simCounter = 0;
	this->generator = generator;
	yaw = 0.0;
	pitch = 0.0;
	translate_x = 0.0;
	translate_y = 0.0;
	translate_z = 0.0;
	//vertices = NULL;
	//colors = NULL;
	/*Parameters of tree*/
}

tree_renderer::~tree_renderer()
{
	delete vertices;
	delete colors;
}
/*
	Allocate and store information in color and vertext arrays 
*/
void tree_renderer::generateArrays()
{
	//vertices = new GLfloat(treeVertexCount * 3);
	//colors = new GLfloat(treeVertexCount * 3);
	/*vertices[0] = 100.0;
	vertices[1] = 120.00;
	vertices[2] = 680.0;
	vertices[3] = 500.0;
	*/
	ofstream file;
	file.open("points.txt");

	printf("Size of %d %d",treeVertexCount, this->vertices_list.size());
	//_sleep(1000);
	for (std::list<pos>::iterator iter = vertices_list.begin(); iter != vertices_list.end(); iter++)
	{
		auto index = std::distance(vertices_list.begin(), iter);
		vertices[index * 2] = iter->x;
		vertices[index * 2 + 1] = iter->y;
		//vertices[index * 3 + 2] = iter->z - 5;
		colors[index * 3] = 0.0;
		colors[index * 3 + 1] = 0.0;
		colors[index * 3 + 2] = 0.0;
		file << iter->x << ", " << iter->y<<", "<< endl;	
	}	
	file.close();

}

/**
*	Function invoked for drawing using OpenGL
*/
void tree_renderer::display()
{
	/* Clear the window */
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-0.552285, 0.552285, -0.414214, 0.414214, 1.0, 100.0);
	gluPerspective(45.0, 1.0, 3.0, 400.0);
	gluLookAt(0.0, 0.0, 50.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	/* Load the model view matrix */
	//glBegin(GL_LINES);
	//glEnable(GL_LINE_SMOOTH);

	/* Apply translation and rotation */
	float z_pos = translate_z;
	//printf("Z_translation is : %f\n", z_pos);
	glTranslatef(1.0 + translate_x, -20.0 + translate_y, translate_z);
	glRotatef(pitch, 1.0, 0.0, 0.0);
	glRotatef(yaw, 0.0, 1.0, 0.0);

	/*if (colors[1] != 0.0)
		generateArrays();
*/
	/**/
	if (this->simCounter < simThresh && simCounter % (int(simThresh / iterations)) == 0)
	{
		printf("Enters for new iteration \n");
		this->clearPartsList();
		this->generator->generateTree(1);
		//this->generator->printTree();
		this->generator->traverseGeneratedTree();
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	for (part_model * part : this->parts_list)
	{				
		tuple3d pos = part->getBasePos();
		tuple3d pcolors = part->getColor();
		glLineWidth(part->getWidth());
		//glVertex3f(pos.first + cos(part->getAngle()) * part->getLength(), pos.second + sin(part->getAngle()) * part->getLength(), 0.0);
		//glVertex3f(pos.first, pos.second, 0.0);
		vertices[0] = pos.first;
		vertices[1] = pos.second;
		vertices[2] = pos.first + cos(part->getAngle()) * part->getLength();
		vertices[3] = pos.second + sin(part->getAngle()) * part->getLength();
		colors[0] = pcolors.first; colors[1] = pcolors.second; colors[2] = pcolors.third;
		colors[3] = pcolors.first; colors[4] = pcolors.second; colors[5] = pcolors.third;
		/*GLUquadricObj *quadratic = gluNewQuadric();
		glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
		glTranslatef(pos.first, pos.second, pos.third);
		gluQuadricDrawStyle(quadratic, GLU_FILL);
		gluCylinder(quadratic, 0.05, 0.04, 10, 32, 32);*/
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glColorPointer(3, GL_FLOAT, 0, colors);
		glDrawArrays(GL_LINES, 0, 2);
		//glColor3f(std::get<0>(part->getColor()), std::get<1>(part->getColor()), std::get<2>(part->getColor()));
		if (!firstRender)
		{
			//printf("Supported line width : %f", glGet(GL_LINE_WIDTH_RANGE, GL_LINE_WIDTH_GRANULARITY));
			//printf("Line Vertices : (%f, %f) (%f, %f) (%f)\n", vertices[0], vertices[1], vertices[2], vertices[3], part->getAngle());
		}
		//glPopMatrix();
	}
	firstRender = true;
	//glEnd();
	if(simCounter <= simThresh)
		simCounter++;
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	/* Force execution of OpenGL commands */
	glFlush();

	/* Swap buffers for animation */
	glutSwapBuffers();
}

/**
*	Function invoked when window system events are not being received
*/
void tree_renderer::idle()
{
	/* Redraw the window */
	glutPostRedisplay();
}

/**
*	Function invoked when an event on regular keys occur
*/
void tree_renderer::keyboard(unsigned char k, int x, int y)
{
	/* Show which key was pressed */
	std::cout << "Pressed \"" << k << "\" ASCII: " << (int)k << std::endl;

	if (int(k) == 98)
		this->translate_z -= 5.0;
	else if (k == 102)
		translate_z +=5.0;
	else if (k == 'l')
		translate_x +=5.0;
	else if (k == 'r')
		translate_x -=5.0;
	else if (k == 'd')
		translate_y +=5.0;
	else if (k == 'u')
		translate_y -=5.0;
	else if (k == 27)
		exit(0);
}

/**
*	Function invoked when an event on a special keys occur
*/
void tree_renderer::special(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		pitch -= 10.0;
	else if (key == GLUT_KEY_DOWN)
		pitch += 10.0;
	else if (key == GLUT_KEY_RIGHT)
		yaw -= 10.0;
	else if (key == GLUT_KEY_LEFT)
		yaw += 10.0;
}

/**
*	Set OpenGL initial state
*/
void tree_renderer::init()
{
	/* Set clear color */
	glClearColor(1.0, 1.0, 1.0, 0.0);

	/* Set 2D orthogonal projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0.0,800,600, 0.0);
}

void tree_renderer::addVertex(float x, float y)
{
	//printf("Co-ordinate : %f  %f\n", x, y);
	vertices_list.push_back(pos{x, y + 0.2f, -2 });
	treeVertexCount++;
}
void tree_renderer::addModel(part_model* part)
{
	this->parts_list.push_back(part);
}

void tree_renderer::clearPartsList()
{
	for (part_model * model : this->parts_list)
	{
		delete model;
	}
	this->parts_list.clear();
}

/*void tree_renderer::renderScene(int argc, char ** argv )
{
	/* Initialize the GLUT window 
	glutInit(&argc, argv);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(30, 30);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	windowID = glutCreateWindow("OpenGL/FreeGLUT - Example 2: Hello Square");

	/* Set OpenGL initial state *
	init();

	/* Callback functions 
	glutDisplayFunc([](){display(); });
	glutIdleFunc(glutCallBacks.idle);
	glutKeyboardFunc(keyboard);
	//glutMouseFunc(mouse);

	/* Start the main GLUT loop *
	glutMainLoop();
}*/