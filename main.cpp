
#include <cstdlib>
#include <stdlib.h>
#include "grammar_parser.h"
#include "tree_generator.h"
#include "glutCallBacks.h"

#define WINDOW_W  800
#define WINDOW_H  600

int main(int argc, char **argv)
{
	//Test parser
	grammar_parser * parser(new grammar_parser(std::string("test_grammar.txt")));
	parser->parseFile();

	//Instantiate Renderer
	tree_renderer * rend_obj(new tree_renderer());
	//Defining renderer pointer
	glutCallBacks::renderer = rend_obj;

	//Test string generator
	tree_generator generator(parser, rend_obj);
	generator.generateTree();
	generator.printTree();
	generator.traverseGeneratedTree();
	_sleep(10000);

	//Initlaizing Glut Window
	/* Initialize the GLUT window */
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInitWindowPosition(30, 30);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	auto windowID = glutCreateWindow("Rendered Test Tree");

	/* Set OpenGL initial state */
	rend_obj->init();

	/* Callback functions */
	glutDisplayFunc(glutCallBacks::displayTree);
	glutIdleFunc(glutCallBacks::idle);
	glutKeyboardFunc(glutCallBacks::keyboardHandler);
	glutMouseFunc(glutCallBacks::mouseHandler);

	/* Start the main GLUT loop */
	/* NOTE: No code runs after this */
	glutMainLoop();
}