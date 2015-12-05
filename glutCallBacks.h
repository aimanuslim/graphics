#pragma once
#include "tree_renderer.h"

class glutCallBacks
{
public:
	static tree_renderer * renderer;

	/* Callback functions */
	static void displayTree();
	static void idle();
	static void keyboardHandler(unsigned char, int, int);
	static void mouseHandler(int, int, int, int);
	static void specialFunc(int, int, int);
	glutCallBacks();
	~glutCallBacks();
};

