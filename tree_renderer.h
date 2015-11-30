#pragma once
#include<iostream>
#include<stdlib.h>
#include "GL/glut.h"
#include "part_model.h"
#include<list>
#include<vector>

using namespace std;
class tree_renderer
{
	private:
		static struct pos
		{
			float x;
			float y;
			float z;
		};
		
		list<pos> vertices_list;
		GLfloat vertices[1000];
		GLfloat colors[1000];
		vector<part_model *> parts_list;
		void generateArrays();
		float windowWidth, windowHeight;
		int windowID, treeVertexCount;
		 
	public:	
		tree_renderer();
		~tree_renderer();
		void init();
		void idle();
		void display();
		void addVertex(float x, float y);
		void addModel(part_model * part);
		void keyboard(unsigned char k, int x, int y);
		//void renderScene(int, char **);
};