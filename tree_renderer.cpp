/*
	File for rendering all objects and triangles
*/
#include "tree_renderer.h"
#include "glutCallBacks.h"
#include "part_model.h"
#include<fstream>

tree_renderer::tree_renderer()
{
	/* Window information */
	treeVertexCount = 0;
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

	if (colors[1] != 0.0)
		generateArrays();

	glBegin(GL_LINES);

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	for (part_model * part : this->parts_list)
	{		
		std::pair<float, float> pos = part->getBasePos();
		std::tuple<float, float, float>& pcolors = part->getColor();		glVertex2f(pos.first, pos.second);
		glVertex2f(pos.first + cos(part->getAngle()) * part->getLength(), pos.second - sin(part->getAngle()) * part->getLength());
		glColor3f(std::get<0>(part->getColor()), std::get<1>(part->getColor()), std::get<2>(part->getColor()));
		/*vertices[0] = pos.first; vertices[1] = pos.second;
		vertices[2] = pos.first + cos(part->getAngle() * part->getLength()); 
		vertices[3] = pos.second -  sin(part->getAngle()) *part->getLength()
		colors[0] = std::get<0>(pcolors); colors[1] = std::get<1>(pcolors); colors[2] = std::get<2>(pcolors);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glColorPointer(3, GL_FLOAT, 0, colors);
		glDrawArrays(GL_LINES, 0, 2);*/
	}
	glEnd();
	//glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);

	/* Draw Tree Lines in 2D */
	/* Step 1: Enable the clients for the vertex arrays */

	//printf("Size of color array : %d", colors[9]);
	/* Step 2a: Set up arrays for square and draw it */
	
	//glVertexPointer(2, GL_FLOAT, 0, vertices);
	//glColorPointer(3, GL_FLOAT, 0, colors);
	//glDrawArrays(GL_LINES, 0, treeVertexCount);
	
	/* Step 3: Disable the clients */

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

	/* Close application if ESC is pressed */
	if (k == 27)
	{
		exit(0);
	}
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
	gluOrtho2D(0.0,800,600, 0.0);
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