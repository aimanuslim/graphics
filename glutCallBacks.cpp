#include "glutCallBacks.h"

//Definition of static renderer instance pointer
tree_renderer * glutCallBacks::renderer = NULL;

glutCallBacks::glutCallBacks()
{
}

void glutCallBacks::displayTree()
{
	glutCallBacks::renderer->display();
}

void glutCallBacks::idle()
{
	glutCallBacks::renderer ->idle();
}

void glutCallBacks::keyboardHandler(unsigned char key, int x, int y)
{
	glutCallBacks::renderer->keyboard(key, x, y);
}

void glutCallBacks::mouseHandler(int, int, int, int)
{

}

glutCallBacks::~glutCallBacks()
{
}
