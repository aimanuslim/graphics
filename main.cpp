
#include <cstdlib>
#include <stdlib.h>
#include "grammar_parser.h"
#include "tree_generator.h"
#include "glutCallBacks.h"

#define WINDOW_W  800
#define WINDOW_H  600

int main(int argc, char **argv)
{

	/**********************Data Input from Island Map**************/
	/*float elevation[WINDOW_H][WINDOW_W];
	float tree_count;
	float colors[WINDOW_H][WINDOW_W], surface_normals[WINDOW_H][WINDOW_W];
	*/
	//Test parser
	grammar_parser * parser(new grammar_parser(std::string("test_grammar.txt")));
	parser->parseFile();

	//Test string generator
	tree_generator generator(parser);
	tuple3d base_location = tuple3d(0.0, -10.0, -5.0f);
	
	/*for (tuple3d base_loc : surface_normals)
	{

	}*/
	generator.setTreeBaseLocation(base_location);
	//generator.generateTree(parser->model_data->find(std::string("iterations"))->second));
	_sleep(10000);

	//Instantiate Renderer
	tree_renderer * rend_obj(new tree_renderer(&generator));
	generator.setRenderer(rend_obj);
	//generator.printTree();
	//generator.traverseGeneratedTree();
	rend_obj->simThresh = 10000;
	rend_obj->iterations = parser->iterations;
	
	//Defining renderer pointer
	glutCallBacks::renderer = rend_obj;

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
	glutSpecialFunc(glutCallBacks::specialFunc);
	/* Start the main GLUT loop */
	/* NOTE: No code runs after this */
	glutMainLoop();
}