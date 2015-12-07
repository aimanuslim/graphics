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
	firstRender = true;
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
		vertices[0] = -10.0;
		vertices[1] = 0.0;
		vertices[2] = 10.0;
		vertices[3] = -10.0;
		vertices[4] = 0.0;
		vertices[5] = -10.0;
		vertices[6] = 10.0;
			vertices[7] = 0.0;
		vertices[8] = -10.0;
			vertices[9] = 10.0;
			vertices[10] = 0.0;
		vertices[11] = 10.0;

		for (int i = 0; i < 12; i++)
		{
			if ((i) % 3 == 0)
				colors[i] = 1.0;
			else
				colors[i] = 0.0;
		}
	ofstream file;
	file.open("points.txt");

	//printf("Size of %d %d",treeVertexCount, this->vertices_list.size());
	//_sleep(1000);
	/*for (std::list<pos>::iterator iter = vertices_list.begin(); iter != vertices_list.end(); iter++)
	{
		auto index = std::distance(vertices_list.begin(), iter);
		vertices[index * 2] = iter->x;
		vertices[index * 2 + 1] = iter->y;
		//vertices[index * 3 + 2] = iter->z - 5;
		colors[index * 3] = 0.0;
		colors[index * 3 + 1] = 0.0;
		colors[index * 3 + 2] = 0.0;
		file << iter->x << ", " << iter->y<<", "<< endl;	
	}*/	
	file.close();

}

tuple3d tree_renderer::calculateAngles(vec3 dir)
{
	tuple3d angles;
	angles.first =  (180 * atan(dir.y / dir.z) / PI) /*180 * (atan(dir.y / dir.z) / PI + 1) : 180 * atan(dir.y / dir.z) / PI*/;
	angles.second = (180 * atan(dir.x / dir.z) / PI < 0)? 180 * (atan(dir.x / dir.z) / PI + 1) : 180 * atan(dir.x / dir.z) / PI;
	angles.third = (180 * atan(dir.y / dir.x) / PI < 0 )? 180 * (atan(dir.y / dir.x) / PI + 1) : 180 * atan(dir.y / dir.x) / PI;
	
	return angles;
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
	gluPerspective(45.0, 1.0, 3.0, 1000.0);
	gluLookAt(0.0, 0.0, 50.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	/* Load the model view matrix */
	//glBegin(GL_LINES);
	//glEnable(GL_LINE_SMOOTH);

	/* Apply translation and rotation */
	glTranslatef(1.0 + translate_x, -20.0 + translate_y, translate_z);
	glRotatef(pitch, 1.0, 0.0, 0.0);
	glRotatef(yaw, 0.0, 1.0, 0.0);
	
	/*
	if (this->simCounter < simThresh && simCounter % (int(simThresh / iterations)) == 0)
	{
		printf("Enters for new iteration \n");
		this->clearPartsList();
		this->generator->generateTree(1);
		this->generator->printTree();
		this->generator->traverseGeneratedTree();
	}*/

	if (firstRender)
		generateArrays();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH_HINT);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_DONT_CARE);
	
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glDrawArrays(GL_POLYGON, 0, 4);
	
	
	/*GLUquadricObj *quadratic = gluNewQuadric();
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	//glTranslatef((pos.first + pos.first + cos(part->getAngle()) * part->getLength())/ 2.0f , (pos.second +  pos.second + sin(part->getAngle()) * part->getLength()) / 2.0f, pos.third);
	glColor3f(1.0, 0.0, 0.0);*/
	/*gluQuadricDrawStyle(quadratic, GLU_FILL);
	gluCylinder(quadratic, 0.25 , 0.2, 3, 32, 32);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 3.0, 0.0);
	glRotatef(40, 0.0, 1.0f, 0.0f);
	glRotatef(45, 0.0,0.0, 1.0f);
	glRotatef(-90, 1.0f, 0.0, 0.0);
	gluCylinder(quadratic, 0.2, 0.12, 3, 100, 100);
	glPopMatrix();*/
	
	GLUquadricObj * tree_quad;

	for (part_model * part : this->parts_list)
	{	
		glPopMatrix();
		glPushMatrix();
		tree_quad = gluNewQuadric();
		tuple3d pos = part->getBasePos();
		tuple3d pcolors = part->getColor();
		tuple3d orient = this->calculateAngles(part->getDir().getVector());
		glLineWidth(part->getWidth());
			float width_b = part->getWidth() / 10.0,
			width_t = (part->getType() == LEAF)? 0 : width_b * generator->contract_w;
	/*	vertices[0] = pos.first;
		vertices[1] = pos.second;
		vertices[2] = pos.third;
		vertices[3] = pos.first + part->getDir().first * part->getLength();
		vertices[4] = pos.second + part->getDir().second  * part->getLength();
		vertices[5] = pos.third + part->getDir().third * part->getLength();
		colors[0] = pcolors.first; colors[1] = pcolors.second; colors[2] = pcolors.third;
		colors[3] = pcolors.first; colors[4] = pcolors.second; colors[5] = pcolors.third;
	*/
		glTranslatef(translate_x, translate_y, translate_z);
		glRotatef(pitch, 1.0f, 0.0f, 0.0f);
		glRotatef(yaw, 0.0, 1.0f, 0.0f);
		glTranslatef(pos.first, pos.second, pos.third);
		//glRotatef(part->getAngle() * 180 /PI - 90, 0.0, 0.0, 1.0f);
		glRotatef(90 - orient.third, 0.0f, 0.0f, 1.0f);
		//glRotatef(orient.second, 0.0f, 1.0f, 0.0f);
		glRotatef(-90.0f + orient.first - 90, 1.0f, 0.0f, 0.0f);
		//glTranslatef((pos.first + pos.first + cos(part->getAngle()) * part->getLength())/ 2.0f , (pos.second +  pos.second + sin(part->getAngle()) * part->getLength()) / 2.0f, pos.third);
		gluQuadricDrawStyle(tree_quad, GLU_FILL);
		glColor3f(pcolors.first, pcolors.second, pcolors.third);
		//gluQuadricOrientation(quadratic, GL_)
		gluCylinder(tree_quad, width_b, width_t, part->getLength(), 32, 32);
		gluDeleteQuadric(tree_quad);
		//glVertexPointer(2, GL_FLOAT, 0, vertices);
		//glColorPointer(3, GL_FLOAT, 0, colors);
		//glDrawArrays(GL_LINES, 0, 2);
		//glColor3f(part->getColor().first, part->getColor().second, part->getColor().third);
		if (firstRender)
		{
			char symbol = (part->getType() == BRANCH) ? 'F' : 'L';
			printf("Line Vertices : (%f, %f, %f) (%f, %f, %f)  %f\n", vertices[0], vertices[1], vertices[2], vertices[3], vertices[4], vertices[5], part->getLength());
			printf("Part : %c Angle with z axis : %f and Height : %f \n", symbol, orient.first, part->getLength());
		}
	}
	firstRender = false;
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
	//std::cout << "Pressed \"" << k << "\" ASCII: " << (int)k << std::endl;

	if (int(k) == 98)
		this->translate_z -= 2.0;
	else if (k == 102)
		translate_z +=2.0;
	else if (k == 'l')
		translate_x +=2.0;
	else if (k == 'r')
		translate_x -=2.0;
	else if (k == 'd')
		translate_y +=2.0;
	else if (k == 'u')
		translate_y -=2.0;
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
	glClearColor(1.0, 1.0, 1.0, 1.0);

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